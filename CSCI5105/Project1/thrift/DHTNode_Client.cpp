#include "./gen-cpp-node/DHTNode_NodeInterface.h"
#include "./gen-cpp-super/DHTNode_SupernodeInterface.h"

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <iostream>
#include <fstream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int display_menu();

int main(int argc, char** argv) {

    if(argc != 1) {
      std::cout << "Usage: ./client" << std::endl;
    }

    std::string ipAddress = "";
    std::string port_string = "";
    int port = 0;

    std::cout << "What's the IP Address of the SuperNode you would like to connect to?: ";
    getline(std::cin, ipAddress);
    std::cout << "Port Number?: ";
    getline(std::cin, port_string);
    port = atoi(port_string.c_str());

    boost::shared_ptr<TSocket> socket(new TSocket(ipAddress, port));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    DHTNode_SupernodeInterfaceClient SClient(protocol);
    NodeInfo contactNode, empty;
    transport->open();
    SClient.getNode(contactNode);
    transport->close();

    if(contactNode == empty) {
      std::cout << "No DHTNodes in the DHT" << std::endl;
      return 1;
    }

    boost::shared_ptr<TSocket> socket_node(new TSocket(contactNode.network_info.ipAddress, contactNode.network_info.port));
    boost::shared_ptr<TTransport> transport_node(new TBufferedTransport(socket_node));
    boost::shared_ptr<TProtocol> protocol_node(new TBinaryProtocol(transport_node));

    DHTNode_NodeInterfaceClient NClient(protocol_node);

    WriteFile fileInfo;
    ReadFile readInfo;
    LogInfo returnInfo;
    std::vector<NodeInfo> NodeList;
    int64_t flags = 1;

    int choice = 0;
    std::string filename;
    std::ifstream fin;

    while(true) {
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

          fileInfo.filename = filename.substr(filename.find_last_of("/\\")+1);

          //preallocate memory for the string
          fin.seekg(0, std::ios::end);
          fileInfo.file.reserve(fin.tellg());
          fin.seekg(0, std::ios::beg);

          //read entire file into string
          fileInfo.file.assign((std::istreambuf_iterator<char>(fin)),
                                std::istreambuf_iterator<char>());

          //write file to DHT
          transport_node->open();
          NClient.Write(returnInfo, fileInfo, flags);
          transport_node->close();
          fin.close();
          break;
        case 2:
          std::cout << "Which file would you like to read?" << std::endl;
          std::cin >> filename;
          transport_node->open();
          NClient.Read(readInfo, filename, flags);
          transport_node->close();

          if(readInfo.error)
          {
            std::cout << readInfo.errorMessage << std::endl;
            continue;
          }
          else
          {
            std::cout << readInfo.filename << ":" << std::endl;
            std::cout << "File content: " << readInfo.file << std::endl;
            std::cout << "Here is the file path: ";
            for(int i = readInfo.log.nodesVisited.size() - 1; i >= 0; i--) {
              if(i == 0)
                std::cout << readInfo.log.nodesVisited[i] << std::endl;
              else
                std::cout << readInfo.log.nodesVisited[i] << ", ";
            }
          }
          break;
        case 3:
          transport->open();
          SClient.getNodeList(NodeList);
          transport->close();

          std::cout << "Printing DHT network: " << std::endl;
          for(unsigned int k = 0; k < NodeList.size(); k++)
          {
            boost::shared_ptr<TSocket> socket_node1(new TSocket(NodeList[k].network_info.ipAddress, NodeList[k].network_info.port));
            boost::shared_ptr<TTransport> transport_node1(new TBufferedTransport(socket_node1));
            boost::shared_ptr<TProtocol> protocol_node1(new TBinaryProtocol(transport_node1));

            DHTNode_NodeInterfaceClient NodeContact(protocol_node1);
            myInfo INFO;
            transport_node1->open();
            NodeContact.getInfo(INFO);
            transport_node1->close();

            std::cout << "Node:         " << INFO.ID << std::endl
                      << "Range:        " << INFO.minKey << "-" << INFO.maxKey << std::endl
                      << "Predecessor:  " << INFO.predecessor << std::endl
                      << "Successor:    " << INFO.successor << std::endl
                      << "Num files:    " << INFO.numFiles << std::endl
                      << "File List:    " << std::endl;
            for(unsigned int i = 0; i < INFO.files.size(); i++)
              std::cout << "  " << INFO.files[i] << std::endl;
            std::cout << "Finger table: " << std::endl;
            for(unsigned int i = 1; i <= INFO.fingerTable.size(); i++)
              std::cout << "  " << i << ": " << INFO.fingerTable[i].ID << "  "
                        << INFO.fingerTable[i].ipAddress << ":"
                        << INFO.fingerTable[i].port << std::endl;
            std::cout << std::endl;



          }
          break;
        case 4:
          return 0;
          break;
        default:
          std::cout << "If this is printed out, something went wrong!" << std::endl;
          break;
      }

      std::cout << "Here is the node I should contact: " << contactNode.ID << std::endl;
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
