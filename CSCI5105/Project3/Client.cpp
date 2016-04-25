#include "gen-cpp-server/MR_ServerInterface.h"

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

  int choice;

  if(argc != 3) {
    std::cout << "Usage: ./client <ip-address> <port>" << std::endl;
    return 1;
  }

  std::string server_ip_address = argv[1];
  int server_port = atoi(argv[2]);

  boost::shared_ptr<TSocket> socket_node(new TSocket(server_ip_address, server_port));
  boost::shared_ptr<TTransport> transport_node(new TBufferedTransport(socket_node));
  boost::shared_ptr<TProtocol> protocol_node(new TBinaryProtocol(transport_node));


  MR_ServerInterfaceClient MRServer(protocol_node);
  std::string temp;
  std::string filename;
  std::ifstream fin;
  while(true)
  {
    choice = display_menu();

    switch(choice)
    {
      case 1:
        std::cout << "Enter a filename" << std::endl;
        std::cin >> filename;
        filename = filename;
        fin.open(("./input_files/" + filename).c_str());
        if(fin.fail())
        {
          std::cerr << "Cannot open file " << filename << std::endl;
          break;
        }
        fin.close();

        struct timeval tv1, tv2;
        gettimeofday(&tv1, NULL);
        transport_node->open();
        MRServer.getSorted(temp, filename); //<---- just for testing purposes. Havent implemented this logic.
        transport_node->close();
        gettimeofday(&tv2, NULL); //set heartbeat to current time
        std::cout << "Here is sorted output filename: " << temp << std::endl;
        std::cout << "Computation time: " << ((double)tv2.tv_sec + (double)tv2.tv_usec*.000001) - ((double)tv1.tv_sec + (double)tv1.tv_usec*.000001)<< " secs." << std::endl;
        break;
      case 2:
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
            << "  [1] Sort a file\n"
            << "  [2] Quit\n";

  while(choice == 0)
  {
    std::cin  >> choice;
    if(choice > 2 || choice <= 0)
    {
      std::cout << "Invalid choice\n";
      choice = 0;
    }
  }
  return choice;
}
