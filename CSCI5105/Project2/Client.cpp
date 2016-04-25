#include "./gen-cpp/FileServerInterface.h"

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int display_menu();

int main(int argc, char** argv) {
  srand(time(NULL));
  std::string coordinator_ip;
  int coordinator_port;

  if(argc != 3) {
    std::cout << "Usage: ./client coordinator_ip coordinator_port read_write_flag" << std::endl;
    return 1;
  }

  coordinator_ip = argv[1];
  coordinator_port = atoi(argv[2]);

  boost::shared_ptr<TSocket> socket(new TSocket(coordinator_ip, coordinator_port));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  FileServerInterfaceClient Coordinator(protocol);
  std::vector<ServerInfo> servers;

  transport->open();
  Coordinator.getAllServers(servers);
  transport->close();

  if(servers.size() == 0) {
    std::cout << "No fileservers available" << std::endl;
    return 1;
  }

  int choice;
  std::string filename;
  std::ifstream fin;
  WriteFile wFile;
  ReadFile rFile;
  std::vector<FileInfo> file_list;
  struct timeval tv1, tv2;

  while(true)
  {
    //Get a random server (including coordinator)
    ServerInfo contact = servers[rand()%servers.size()];

    boost::shared_ptr<TSocket> socket_node(new TSocket(contact.ipAddress, contact.port));
    boost::shared_ptr<TTransport> transport_node(new TBufferedTransport(socket_node));
    boost::shared_ptr<TProtocol> protocol_node(new TBinaryProtocol(transport_node));

    FileServerInterfaceClient FileServer(protocol_node);

    choice = display_menu();

    switch(choice)
    {
      case 1:
        std::cout << "Which file would you like to write?" << std::endl;
        std::cin >> filename;
        filename.insert(0, "./FILES/");
        fin.open(filename.c_str());
        if(fin.fail())
        {
          std::cout << "Invalid filename!" << std::endl;
          continue;
        }

        wFile.filename = filename.substr(filename.find_last_of("/\\")+1);

        //preallocate memory for the string
        fin.seekg(0, std::ios::end);
        wFile.file.reserve(fin.tellg());
        fin.seekg(0, std::ios::beg);

        //read entire file into string
        wFile.file.assign((std::istreambuf_iterator<char>(fin)),
            std::istreambuf_iterator<char>());

        //write file to network
        transport_node->open();
        gettimeofday(&tv1, NULL);
        FileServer.Write(wFile, 0);
        gettimeofday(&tv2, NULL);
        transport_node->close();
        fin.close();

        std::cout << "Write," << (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec) << std::endl;
        break;
      case 2:
        std::cout << "Which file would you like to read?" << std::endl;
        std::cin >> filename;
        transport_node->open();
        gettimeofday(&tv1, NULL);
        FileServer.Read(rFile, filename, 0);
        gettimeofday(&tv2, NULL);
        transport_node->close();

        if(rFile.error)
        {
          std::cout << rFile.errorMessage << std::endl;
          continue;
        }
        else
        {
          std::cout << "File content: " << rFile.file;
          std::cout << "File version: " << rFile.version << std::endl;
        }

        std::cout << "Read," << (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec) << std::endl;
        break;
      case 3:
        transport_node->open();
        FileServer.listFiles(file_list);
        transport_node->close();

        std::cout << "Outputting file list:" << std::endl;
        for(unsigned int i = 0; i < file_list.size(); i++)
        {
          std::cout << "\t" << file_list[i].filename << ":" << file_list[i].version << std::endl;
        }
        break;
      case 4:
        return 0;
        break;
      default:
        break;
    }
  }


  return 0;
}

int display_menu()
{
  int choice = 0;
  std::cout << "CHOOSE AN OPTION FROM THE MENU\n"
            << "  [1] Write a file to the network\n"
            << "  [2] Read a file from the network\n"
            << "  [3] Print out the network\n"
            << "  [4] Quit\n";

  while(choice == 0)
  {
    std::cin  >> choice;
    if(choice > 4 || choice <= 0)
    {
      std::cout << "Invalid choice\n";
      choice = 0;
    }
  }
  return choice;
}
