#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <cstdlib>
#include <strings.h>
#include <cstring>
#include <cmath>

#define NUM_TRIALS 10

void setup(int &sockfd);
void _register(int port, int this_sockfd);
void serve(int serverfd);

int main(int argc, char** argv)
{
  int client_fd;
  struct sockaddr_in client_addr;

  if(argc != 2)
  { std::cerr << "usage: ./app-server <port>" << std::endl; exit(0); }

  int serverfd;
  setup(serverfd);

  _register(atoi(argv[1]), serverfd);

  while(1)
  {
    socklen_t clilen = sizeof(client_addr);
    client_fd = accept(serverfd, (struct sockaddr *)&client_addr, &clilen);
    serve(client_fd);
    close(client_fd);
  }
}

void setup(int &sockfd)
{
  struct sockaddr_in serveraddr;
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(0);
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) { std::cerr << "ERROR: socket!" << std::endl; exit(0); }

  int error = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  if(error < 0) { std::cerr << "ERROR: bind!" << std::endl; exit(0); }

  error = listen(sockfd, 10);
  if(error < 0) { std::cerr << "ERROR: listen!" << std::endl; exit(0); }
}

void _register(int port, int this_sockfd)
{
  int sockfd;
  struct sockaddr_in dir_serveraddr;
  struct hostent *dir_server;
  std::string host = "apollo.cselabs.umn.edu";
  std::string message;
  std::string ip_address;

  //connect to dir-server
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) { std::cerr << "ERROR: Socket!" << std::endl; exit(0); }

  dir_server = gethostbyname(host.c_str());
  if(dir_server == NULL)
  { std::cerr << "ERROR: Server " << host << " does not exist!" << std::endl; exit(0); }

  bzero((char *)&dir_serveraddr, sizeof(dir_serveraddr));
  dir_serveraddr.sin_family = AF_INET;
  bcopy((char *)dir_server->h_addr,
      (char *)&dir_serveraddr.sin_addr.s_addr, dir_server->h_length);
  dir_serveraddr.sin_port = htons(port);

  if(connect(sockfd, (const sockaddr*)&dir_serveraddr, sizeof(dir_serveraddr)) < 0)
  { std::cerr << "ERROR: Connect!" << std::endl; exit(0); }

  struct sockaddr_in me;
  socklen_t len = sizeof(sockaddr);
  //get ip address from open connection
  getsockname(sockfd, (struct sockaddr *)&me, &len);
  ip_address = inet_ntoa(me.sin_addr);
  //get port from setup socket
  getsockname(this_sockfd, (struct sockaddr *)&me, &len);
  message = "register " + ip_address + " " + std::to_string(me.sin_port) + "\r\n";
  char send_message[100];
  strcpy(send_message, message.c_str());

  std::cout << ip_address << " " << std::to_string(me.sin_port) << std::endl;

  //send register message
  int num = write(sockfd, (const void*)&send_message, (size_t)strlen(send_message));
  if(num < 0) { std::cerr << "ERROR: Write!" << std::endl; exit(0); }

  char receive_mes[100];
  num = read(sockfd, receive_mes, 100);
  std::cout << receive_mes;
  if(!strcmp(receive_mes, "failure\r\n"))
    exit(0);

  close(sockfd);
}

void serve(int client_fd)
{
  //read 10KB, 100KB, 1000KB, and 10000KB
  char *buffer = new char[10240000]; //10000KB
  char ack[2] = "a";
  for(int i = 0; i < 4; i++)
  {
    for(int j = 0; j < NUM_TRIALS; j++)
    {
      int bytes_read = recv(client_fd, buffer, 10240*pow(10,i), MSG_WAITALL);
      if(bytes_read < 0) { std::cerr << "ERROR: read!" << std::endl; return; }
      int bytes_sent = write(client_fd, ack, 1);
      if(bytes_sent < 0) { std::cerr << "ERROR: send!" << std::endl; return; }
    }
    std::cout << "Read " << static_cast<int>(10*pow(10,i)) << " KB " 
              << NUM_TRIALS << " times" << std::endl;
  }
}
