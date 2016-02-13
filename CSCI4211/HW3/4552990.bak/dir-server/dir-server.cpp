#include <iostream>
#include <sstream>
#include <fstream>
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
#include <vector>

void setup(int &sockfd, int port);
void serve(int client_fd);

//struct to hold the list of ip/port pairs
struct ipport
{
  std::string ip_address;
  std::string port;
  ipport(std::string ip_, std::string port_){ip_address = ip_; port = port_;};
};

//list to hold the registered ip/port pairs
std::vector<struct ipport> register_list;

int main(int argc, char** argv)
{
  int client_fd;
  struct sockaddr_in client_addr;

  if(argc != 2)
  { std::cerr << "usage: ./app-server <port>" << std::endl; exit(0); }

  int serverfd;
  setup(serverfd, atoi(argv[1]));
  
  while(1)
  {
    socklen_t clilen = sizeof(client_addr);
    client_fd = accept(serverfd, (struct sockaddr *)&client_addr, &clilen);
    serve(client_fd);
  }
}

void setup(int &sockfd, int port)
{
  struct sockaddr_in serveraddr;
  serveraddr.sin_family = AF_INET;
  serveraddr.sin_port = htons(port);
  serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) { std::cerr << "ERROR: socket!" << std::endl; exit(0); }

  int error = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
  if(error < 0) { std::cerr << "ERROR: bind!" << std::endl; exit(0); }
  
  error = listen(sockfd, 10);
  if(error < 0) { std::cerr << "ERROR: listen!" << std::endl; exit(0); }
}

void serve(int client_fd)
{
  char buffer[100];
  bzero(buffer, 100);
  int bytes = read(client_fd, buffer, 100);
  if(bytes < 0) { std::cerr << "ERROR: read!" << std::endl; close(client_fd); return; }
  std::cout << buffer;

  //I really wanted to use regex for this, but gcc 4.8.4 doesn't support [0-9]
  std::string receive_msg(buffer);
  std::string ip_address;
  std::string port;
  struct sockaddr_in throwaway;
  if(receive_msg.substr(0,8) == "register" && 
      inet_pton(AF_INET, receive_msg.substr(9,receive_msg.find(' ', 10) - 9).c_str(),
        &(throwaway.sin_addr)))
  {
    //get ip/port pairs from register message and place into register list
    ip_address = receive_msg.substr(9,receive_msg.find(' ', 10) - 9);
    port = receive_msg.substr(receive_msg.find(' ', 10) + 1,
                              receive_msg.find('\r') - receive_msg.find(' ', 10) - 1);
    register_list.emplace_back(ipport(ip_address,port));
    strcpy(buffer,"success\r\n");
    send(client_fd, buffer, 100, 0);
  }
  else if(strcmp(receive_msg.c_str(), "list-servers\r\n") == 0)
  {
    //send list of ip/port pairs to client
    bzero(buffer, 100);
    strcpy(buffer, "success\r");
    bytes = send(client_fd, buffer, 100, 0);
    if(bytes < 0) { std::cerr << "ERROR: send!" << std::endl; return; }

    for(auto i : register_list)
    {
      bzero(buffer, 100);
      strcpy(buffer, i.ip_address.c_str());
      strcat(buffer, " ");
      strcat(buffer, i.port.c_str());
      strcat(buffer, "\r");
      bytes = send(client_fd, buffer, 100, 0);
      if(bytes < 0) { std::cerr << "ERROR: send!" << std::endl; return; }
    }
    strcpy(buffer, "\n");
    bytes = send(client_fd, buffer, 1, 0);
    if(bytes < 0) { std::cerr << "ERROR: send!" << std::endl; return; }
  }
  else
  {
    bzero(buffer, 100);
    strcpy(buffer, "failure\r\n");
    bytes = send(client_fd, buffer, 100, 0);
    if(bytes < 0) { std::cerr << "ERROR: send!" << std::endl; return; }
  }
}
