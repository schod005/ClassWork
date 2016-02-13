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
#include <vector>
#include <chrono>

#define NUM_TRIALS 10

void get_list(int port);
void test_servers(int db_port);
void get_records(int db_port);

//struct to hold ip/port pairs
struct ipport
{
  std::string ip_address;
  std::string port;
  ipport(std::string ip_, std::string port_){ip_address = ip_; port = port_;};
};

//list to hold registered ip/port pairs from dir-server
std::vector<struct ipport> register_list;

int main(int argc, char **argv)
{
  int server_fd;
  struct sockaddr_in server_addr;

  if(argc != 3)
  { std::cerr << "usage: ./app-client <ds-port> <db-port>" << std::endl; exit(0); }

  get_list(atoi(argv[1]));
  test_servers(atoi(argv[2]));
  get_records(atoi(argv[2]));
}

void get_list(int port)
{
  std::cout << "Receiving host list: \n";
  char buffer[100];
  std::string data;
  std::string ip_address;
  std::string port_str;

  int sockfd;
  struct sockaddr_in dir_serveraddr;
  struct hostent *dir_server;
  std::string host = "apollo.cselabs.umn.edu";
  std::string message = "list-servers\r\n";

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
  { std::cerr << "ERROR: Connect dir!" << std::endl; exit(0); }

  int bytes = write(sockfd, message.c_str(), message.length());
  if(bytes < 0) { std::cerr << "ERROR: Write!" << std::endl; exit(0); }

  //download list of ip/port pairs
  bytes = read(sockfd, buffer, 100);
  if(strcmp(buffer, "success\r") == 0)
  {
    while(true)
    {
      bytes = read(sockfd, buffer, 100);

      data = std::string(buffer);
      if(data[0] == '\n') break;

      ip_address = data.substr(0,data.find(' '));
      port_str = data.substr(data.find(' ') + 1,
          data.find('\r') - data.find(' ') - 1);
      register_list.emplace_back(ipport(ip_address,port_str));
      std::cout << ip_address << " " << port_str << std::endl;
    }
  }
}

void test_servers(int db_port)
{
  int server_fd;
  int db_server_fd;
  struct sockaddr_in serveraddr;
  struct sockaddr_in db_serveraddr;

  //connect to db server
  struct hostent *db_server;
  std::string host = "atlas.cselabs.umn.edu";
  std::string my_ip_address;
  std::string message;
  char db_buffer[1000];

  db_server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(db_server_fd < 0) { std::cerr << "ERROR: Socket!" << std::endl; exit(0); }

  db_server = gethostbyname(host.c_str());
  if(db_server == NULL)
  { std::cerr << "ERROR: Server " << host << " does not exist!" << std::endl; exit(0); }

  bzero((char *)&db_serveraddr, sizeof(db_serveraddr));
  db_serveraddr.sin_family = AF_INET;
  bcopy((char *)db_server->h_addr,
      (char *)&db_serveraddr.sin_addr.s_addr, db_server->h_length);
  db_serveraddr.sin_port = htons(db_port);

  if(connect(db_server_fd, (const sockaddr*)&db_serveraddr, sizeof(db_serveraddr)) < 0)
  { std::cerr << "ERROR: Connect!" << std::endl; exit(0); }

  struct sockaddr_in me;
  socklen_t len = sizeof(sockaddr);
  //get ip address from open connection
  getsockname(db_server_fd, (struct sockaddr *)&me, &len);
  my_ip_address = inet_ntoa(me.sin_addr);

  char *buffer = new char[10240000]; //10000KB
  memset(buffer, ~0, 10240000);
  char ack[2];

  int64_t nano_seconds = 0;
  double time_seconds;

  //for some reason, the db server only accepts 1 message per connection
  close(db_server_fd);

  //test the servers
  for(auto i : register_list)
  {
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) { std::cerr << "ERROR: Socket!" << std::endl; exit(0); }

    bzero((char *)&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = atoi(i.port.c_str());
    serveraddr.sin_addr.s_addr = inet_addr(i.ip_address.c_str());
    std::cout << "\nConnecting to " << i.ip_address << ":" << i.port << std::endl;

    if(connect(server_fd, (const sockaddr*)&serveraddr, sizeof(serveraddr)) < 0)
    { std::cerr << "ERROR: Connect test server!" << std::endl; exit(0); }

    //send 10KB, 100KB, 1000KB, 10000KB
    for(int k = 0; k < 4; k++)
    {
      for(int j = 0; j < NUM_TRIALS; j++)
      {
        auto start = std::chrono::high_resolution_clock::now();

        int bytes_sent = send(server_fd, buffer, 10240*pow(10,k), 0);
        if(bytes_sent < 0) { std::cerr << "ERROR: send!" << std::endl; return; }

        int bytes_read = read(server_fd, ack, 1);
        if(bytes_read < 0) { std::cerr << "ERROR: read!" << std::endl; return; }

        auto end = std::chrono::high_resolution_clock::now();
        nano_seconds += std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
        //std::cout << "sent " << bytes_sent << " bytes." << std::endl;
      }
      time_seconds = (double)(nano_seconds / NUM_TRIALS) / 1000000000;
      std::cout << "Sent " << static_cast<int>(10*pow(10,k)) << " KB " 
                << NUM_TRIALS << " times" << std::endl;
      std::cout << "Average time: " << time_seconds << " seconds" << std::endl;
      nano_seconds = 0;

      //reopen connection to db-server and upload result
      db_server_fd = socket(AF_INET, SOCK_STREAM, 0);
      if(db_server_fd < 0) { std::cerr << "ERROR: Socket!" << std::endl; exit(0); }

      if(connect(db_server_fd, (const sockaddr*)&db_serveraddr, sizeof(db_serveraddr)) < 0)
      { std::cerr << "ERROR: Connect!" << std::endl; exit(0); }

      std::cout << "Uploading to db-server\n";
      message = "set-record " + my_ip_address + " " + i.ip_address + " " + i.port +
                " " + std::to_string(static_cast<int>(10*pow(10,k))) + " " +
                std::to_string(time_seconds) + "\r\n";
      bzero(db_buffer, 1000);
      strcpy(db_buffer, message.c_str());

      int bytes_sent = send(db_server_fd, db_buffer, 1000, 0);
      if(bytes_sent < 0) { std::cerr << "ERROR: send!" << std::endl; return; }

      bzero(db_buffer, 1000);
      int bytes_read = read(db_server_fd, db_buffer, 1000);
      if(bytes_read < 0) { std::cerr << "ERROR: read!" << std::endl; return; }

      std::cout << db_buffer;
      close(db_server_fd);
      if(strcmp(db_buffer, "failure\r\n") == 0) { return; }
    }
  }
}

void get_records(int db_port)
{
  std::cout << "\nGetting records from db-server\n";
  int db_server_fd;
  struct sockaddr_in db_serveraddr;

  //connect to db server
  struct hostent *db_server;
  std::string host = "atlas.cselabs.umn.edu";
  std::string message;

  //arbitrarily large buffer to download the data
  char db_buffer[1000000];

  db_server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if(db_server_fd < 0) { std::cerr << "ERROR: Socket!" << std::endl; exit(0); }

  db_server = gethostbyname(host.c_str());
  if(db_server == NULL)
  { std::cerr << "ERROR: Server " << host << " does not exist!" << std::endl; exit(0); }

  bzero((char *)&db_serveraddr, sizeof(db_serveraddr));
  db_serveraddr.sin_family = AF_INET;
  bcopy((char *)db_server->h_addr,
      (char *)&db_serveraddr.sin_addr.s_addr, db_server->h_length);
  db_serveraddr.sin_port = htons(db_port);

  if(connect(db_server_fd, (const sockaddr*)&db_serveraddr, sizeof(db_serveraddr)) < 0)
  { std::cerr << "ERROR: Connect!" << std::endl; exit(0); }

  message = "get-records\r\n";
  bzero(db_buffer, 1000000);
  strcpy(db_buffer, message.c_str());

  int bytes_sent = send(db_server_fd, db_buffer, 1000000, 0);
  if(bytes_sent < 0) { std::cerr << "ERROR: send!" << std::endl; return; }

  bzero(db_buffer, 1000000);
  int bytes_read = read(db_server_fd, db_buffer, 1000000);
  if(bytes_read < 0) { std::cerr << "ERROR: read!" << std::endl; return; }

  //output the data
  for(int i = 0; i < 1000000; i++)
  {
    if(db_buffer[i] == '\0')
      break;
    if(db_buffer[i] == '\r')
      std::cout << '\n';
    else
      std::cout << db_buffer[i];
  }
  close(db_server_fd);
  if(strcmp(db_buffer, "failure\r\n") == 0) {  } //do nothing

}
