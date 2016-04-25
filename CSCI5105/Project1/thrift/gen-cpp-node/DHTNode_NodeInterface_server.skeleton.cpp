// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "DHTNode_NodeInterface.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

class DHTNode_NodeInterfaceHandler : virtual public DHTNode_NodeInterfaceIf {
 public:
  DHTNode_NodeInterfaceHandler() {
    // Your initialization goes here
  }

  void Write(LogInfo& _return, const WriteFile& fileInfo, const int64_t flags) {
    // Your implementation goes here
    printf("Write\n");
  }

  void Read(ReadFile& _return, const std::string& filename, const int64_t flags) {
    // Your implementation goes here
    printf("Read\n");
  }

  void UpdateDHT(const std::vector<UpdateDHTInfo> & NodesList) {
    // Your implementation goes here
    printf("UpdateDHT\n");
  }

  void getInfo(myInfo& _return) {
    // Your implementation goes here
    printf("getInfo\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<DHTNode_NodeInterfaceHandler> handler(new DHTNode_NodeInterfaceHandler());
  shared_ptr<TProcessor> processor(new DHTNode_NodeInterfaceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
