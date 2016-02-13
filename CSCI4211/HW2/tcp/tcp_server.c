#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#include "message.h"

#define NUM_THREADS 5
pthread_t threads[NUM_THREADS];
struct handle_arg
{
  struct sockaddr_in clientaddr;
  int clientfd;
};

//function called for each client connection
void *handle_client(void* arg);

int main(int argc, char **argv) {
  int serverfd;
  int *clientfd = malloc(NUM_THREADS*sizeof(int));
  int port;
  int clientlen = sizeof(struct sockaddr_in);
  struct sockaddr_in serveraddr;
  struct sockaddr_in clientaddr[NUM_THREADS];
  struct handle_arg args[NUM_THREADS];
  int n = 0;

  //process command line arguments
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }
  port = atoi(argv[1]);

  //set up socket
  serverfd = socket(AF_INET, SOCK_STREAM, 0);
  if (serverfd < 0) 
    perror("ERROR opening socket"), exit(1);

  bzero((char *) &serveraddr, sizeof(serveraddr));

  serveraddr.sin_family = AF_INET;
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  serveraddr.sin_port = htons((unsigned short)port);

  if (bind(serverfd, (struct sockaddr *) &serveraddr, sizeof(serveraddr)) < 0) 
    perror("ERROR on binding"), exit(1);

  if (listen(serverfd, NUM_THREADS) < 0)
    perror("ERROR on listen"), exit(1);

  //server continually serves clients that connect.
  while (1) {
    int i;
    for(i = 0; i < NUM_THREADS; i++)
    {
      clientfd[i] = accept(serverfd, (struct sockaddr *) &clientaddr[i], &clientlen);
      if (clientfd[i] < 0) 
        perror("ERROR on accept"), exit(1);
      else
      {
        args[i].clientfd = clientfd[i];
        args[i].clientaddr = clientaddr[i];
        pthread_create(&threads[i], NULL, (void *)handle_client, (void *)&args[i]);
      }
    }
    for(i = 0; i < NUM_THREADS; i++)
      pthread_join(threads[i], NULL);
  }
}

void *handle_client(void* arg)
{
  struct handle_arg *args = (struct handle_arg*)arg;
  struct hostent *hostp;
  char *hostaddrp;
  int bytes = 0;
  int clientfd = args->clientfd;
  struct sockaddr_in clientaddr = args->clientaddr;
  struct msg_t receive_msg;
  struct msg_t send_msg;
  size_t msg_tLEN = sizeof(struct msg_t);
  int i = 1;
  //print out address of connected client
  hostp = gethostbyaddr((const char *)&clientaddr.sin_addr.s_addr, sizeof(clientaddr.sin_addr.s_addr), AF_INET);
  if (hostp == NULL)
    perror("ERROR: gethostbyaddr"), exit(1);
  hostaddrp = inet_ntoa(clientaddr.sin_addr);
  if (hostaddrp == NULL)
    perror("ERROR: inet_ntoa\n"), exit(1);
  printf("Connection established with %s (%s)\n", hostp->h_name, hostaddrp);

  //read first packet to determine file to send
  bytes = read(clientfd, (void *)&receive_msg, msg_tLEN);
  fprintf(stdout, "server: RX %s %d %d %d\n", 
      receive_msg.msg_type == 0 ? "MSG_TYPE_GET" :
      receive_msg.msg_type == 1 ? "MSG_TYPE_GET_ERR" :
      receive_msg.msg_type == 2 ? "MSG_TYPE_GET_RESP" :
      receive_msg.msg_type == 3 ? "MSG_TYPE_GET_ACK" :
      receive_msg.msg_type == 4 ? "MSG_TYPE_FINISH" : "Error",
      receive_msg.cur_seq, receive_msg.max_seq, receive_msg.payload_len);
  if (bytes < 0) 
    perror("ERROR reading from socket"), exit(1);
  if(receive_msg.msg_type == MSG_TYPE_GET)
  {
    FILE* file;
    file = fopen(receive_msg.payload, "r");
    if(file == NULL)
    {
      printf("ERROR: file %s does not exist.  Sending MSG_TYPE_GET_ERR\n", receive_msg.payload);
      send_msg.msg_type = MSG_TYPE_GET_ERR;
      write(clientfd, (void *)&send_msg, msg_tLEN);
    }
    else
    {
      printf("Sending file %s\n", receive_msg.payload);
      int size;
      int bytes_sent;
      fseek(file, 0L, SEEK_END);
      size = ftell(file);
      fseek(file, 0L, SEEK_SET);

      //break file into chunks of BUF_SZ bytes and send to client
      int how_many = size / BUF_SZ;
      if(size % BUF_SZ)
        how_many++;
      while(1)
      {
        if(i <= how_many)
        {
          int bytes_read = fread(send_msg.payload, 1, BUF_SZ, file);
          if(bytes_read == 0)
            perror("ERROR reading file\n"), exit(1);
          send_msg.cur_seq = i;
          send_msg.max_seq = how_many;
          send_msg.payload_len = bytes_read;
          send_msg.msg_type = MSG_TYPE_GET_RESP;
          fprintf(stdout, "sending %d bytes\n", bytes_read);
          write(clientfd, (void *)&send_msg, msg_tLEN);
        }

        read(clientfd, (void *)&receive_msg, msg_tLEN);
        fprintf(stdout, "server: RX %s %d %d %d\n", 
            receive_msg.msg_type == 0 ? "MSG_TYPE_GET" :
            receive_msg.msg_type == 1 ? "MSG_TYPE_GET_ERR" :
            receive_msg.msg_type == 2 ? "MSG_TYPE_GET_RESP" :
            receive_msg.msg_type == 3 ? "MSG_TYPE_GET_ACK" :
            receive_msg.msg_type == 4 ? "MSG_TYPE_FINISH" : "Error",
            receive_msg.cur_seq, receive_msg.max_seq, receive_msg.payload_len);
        if(receive_msg.msg_type == MSG_TYPE_GET_ACK)
        {
          i++;
          continue;
        }
        else if(receive_msg.msg_type == MSG_TYPE_FINISH)
        {
          send_msg.cur_seq = 1;
          send_msg.max_seq = 1;
          send_msg.payload_len = 0;
          send_msg.msg_type = MSG_TYPE_FINISH;
          write(clientfd, (void *)&send_msg, msg_tLEN);
          break;
        }
        else
        {
          perror("ERROR ACK\n");
          send_msg.msg_type = MSG_TYPE_GET_ERR;
          write(clientfd, (void *)&send_msg, msg_tLEN);
          break;
        }
      }

    }

    printf("Terminating connection to %s (%s)\n", hostp->h_name, hostaddrp);
    close(clientfd);
  }
}
