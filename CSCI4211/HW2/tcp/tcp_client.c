#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <sys/time.h>

#include "message.h"

int main(int argc, char **argv) {
  int total_bytes = 0;
  struct timeval t1, t2;
  double elapsedtime = 0;
  int sockfd, port, n;
  struct sockaddr_in serveraddr;
  struct hostent *server;
  char *hostname;
  struct msg_t receive_msg;
  struct msg_t send_msg;
  size_t msg_tLEN = sizeof(struct msg_t);
  int i = 0;
  size_t size;
  size_t length;

  if (argc != 4) {
    fprintf(stderr,"usage: %s <hostname> <port> <filename>\n", argv[0]);
    exit(0);
  }

  //process command line arguments
  hostname = argv[1];
  port = atoi(argv[2]);
  strcpy(send_msg.payload, argv[3]);
  send_msg.msg_type = MSG_TYPE_GET;
  send_msg.payload_len = strlen(argv[3]);

  //set up socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    perror("ERROR opening socket"), exit(1);

  server = gethostbyname(hostname);
  if (server == NULL) {
    fprintf(stderr,"ERROR, no such host as %s\n", hostname);
    exit(0);
  }

  bzero((char *) &serveraddr, sizeof(serveraddr));
  serveraddr.sin_family = AF_INET;
  bcopy((char *)server->h_addr, 
      (char *)&serveraddr.sin_addr.s_addr, server->h_length);
  serveraddr.sin_port = htons(port);

  //connect to server
  if (connect(sockfd, (const struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) 
    perror("ERROR connecting"), exit(1);

  //ask for file
  n = write(sockfd, (void *)&send_msg, msg_tLEN);
  if (n < 0) 
    perror("ERROR writing to socket"), exit(1);
  FILE *file;
  file = fopen(argv[3],"w");
  if(file == NULL)
    perror("ERROR: opening file\n"), exit(1);
  while(1)
  {
    //read data from server, if packet type is MSG_TYPE_GET_RESP, write to file
    //once we have read all packets in the sequence, send MSG_TYPE_FINISH packet
    //and close the connection.
    gettimeofday(&t1, NULL);
    n = read(sockfd, (void *)&receive_msg, msg_tLEN);
    gettimeofday(&t2,NULL);
    elapsedtime += (t2.tv_sec - t1.tv_sec) * 1000;
    elapsedtime += (double)(t2.tv_usec - t1.tv_usec) / 1000;
    printf("Download time: %f microseconds\n", elapsedtime);
    total_bytes += n;
    fprintf(stdout, "client: RX %s %d %d %d\n", 
        receive_msg.msg_type == 0 ? "MSG_TYPE_GET" :
        receive_msg.msg_type == 1 ? "MSG_TYPE_GET_ERR" :
        receive_msg.msg_type == 2 ? "MSG_TYPE_GET_RESP" :
        receive_msg.msg_type == 3 ? "MSG_TYPE_GET_ACK" :
        receive_msg.msg_type == 4 ? "MSG_TYPE_FINISH" : "Error",
        receive_msg.cur_seq, receive_msg.max_seq, receive_msg.payload_len);
    send_msg.cur_seq = receive_msg.cur_seq;
    send_msg.max_seq = receive_msg.max_seq;
    if(receive_msg.cur_seq == receive_msg.max_seq)
    {
      send_msg.cur_seq = 1;
      send_msg.max_seq = 1;
      send_msg.msg_type = MSG_TYPE_FINISH;
      write(sockfd, (void *)&send_msg, msg_tLEN);
    }
    if(receive_msg.msg_type == MSG_TYPE_GET_RESP)
    {
      fwrite(receive_msg.payload, sizeof(char), receive_msg.payload_len, file);
      fprintf(stdout, "read %d bytes\n", receive_msg.payload_len);
      send_msg.msg_type = MSG_TYPE_GET_ACK;
      write(sockfd, (void *)&send_msg, msg_tLEN);
    }
    else if(receive_msg.msg_type == MSG_TYPE_FINISH)
      break;
    else if(receive_msg.msg_type == MSG_TYPE_GET_ERR)
    {
      perror("ERROR RECEIVE\n");
      break;
    }
    else
    {
      perror("UNKNOWN ERROR\n");
      break;
    }
  }
  printf("Download time: %f microseconds\n", elapsedtime);
  printf("Total bytes sent: %d\n", total_bytes);
  fclose(file);
  close(sockfd);
  return 0;
}

