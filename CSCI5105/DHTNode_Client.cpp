#include "./gen-cpp-node/DHTNode_NodeInterface.h"
#include "./gen-cpp-super/DHTNode_SupernodeInterface.h"

#include <thrift/transport/TSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/protocol/TBinaryProtocol.h>
#include <iostream>

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int main(int argc, char** argv) {

    if(argc != 1) {
      std::cout << "Usage: ./client" << std::endl;
    }

    std::string ipAddress = "";
    int port = 0;

    std::cout << "What's the IP Address of the SuperNode you would like to connect to?: ";
    std::cin >> ipAddress;
    std::cout << "Port Number?: ";
    std::cin >> port;

    boost::shared_ptr<TSocket> socket(new TSocket(ipAddress, port));
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    DHTNode_SupernodeInterfaceClient SClient(protocol);
    NodeInfo contactNode;
    transport->open();
    SClient.getNode(contactNode);
    transport->close();

    boost::shared_ptr<TSocket> socket_node(new TSocket(contactNode.network_info.ipAddress, contactNode.network_info.port));
    boost::shared_ptr<TTransport> transport_node(new TBufferedTransport(socket_node));
    boost::shared_ptr<TProtocol> protocol_node(new TBinaryProtocol(transport_node));

    DHTNode_NodeInterfaceClient NClient(protocol_node);
    std::endl;

    WriteFile fileInfo;
    LogInfo returnInfo;
    int64_t flags = 1;
    while(true) {
      std::cout << "Which file would you like to access? :";

      transport_node->open();
      NClient.Write(returnInfo, fileInfo, flags);
      transport->close();
      std::cout << "Here is the node I should contact: " << contactNode.ID << std::endl;
    return 0;
}
