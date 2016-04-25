#include "../gen-cpp-server/MR_ServerInterface.h"

#include "MR_ComputeNodeInterface.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <thrift/transport/TSocket.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

std::string my_ip;
int my_port;
int server_port;
double fail_prob;
std::string server_ip;
bool heartbeat;

pthread_mutex_t merge_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sort_lock = PTHREAD_MUTEX_INITIALIZER;

void *ComputeNodeHandle;

void *TimerWrapper(void*);

class MR_ComputeNodeInterfaceHandler : virtual public MR_ComputeNodeInterfaceIf {
  public:
    int64_t sort_time,
            merge_time,
            num_sort,
            num_merge,
            task_count;

    MR_ComputeNodeInterfaceHandler() {
      //Setup signal handler for node termination
      srand(time(NULL));
      heartbeat = true;
      sort_time =  0;
      merge_time = 0;
      num_sort = 0;
      num_merge = 0;
      task_count = 0;

      //start heartbeat sender in background.
      ComputeNodeHandle = (void*)this;
      pthread_t Thread;
      pthread_create(&Thread, NULL, TimerWrapper, NULL);
      pthread_detach(Thread);
    }

    void wakeup() {
      heartbeat = true;
      task_count = 0;
      std::cout << "Woken up for next task!" << std::endl;
    }

    //Used to see if compute node is alive
    void pingable() {
      return;
    }

    void sendHB() {
      if(heartbeat) {
        boost::shared_ptr<TSocket> socket(new TSocket(server_ip, server_port));
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

        MR_ServerInterfaceClient Server(protocol);

        transport->open();
        Server.sendHeartbeat(my_ip, my_port);
        transport->close();
      }
    }

    void Sort(const std::string& filename, const int64_t offset, const int64_t size) {
      struct timeval tv1, tv2;
      gettimeofday(&tv1, NULL);
      if(heartbeat && task_count % 10 == 0)
      {
        if((double)rand()/RAND_MAX * 100 <= fail_prob)
        {
          heartbeat = false;
          std::cout << std::endl << "Failure Injection: Compute Node failure! Node will be running next task." << std::endl;
        }
      }
      if(heartbeat) { //If Compute Node is alive
        task_count++;
        printf("Sorting\n");
        std::ifstream fin;
        std::ofstream fout;
        std::stringstream s;
        char *array;
        std::vector<int> numbers;
        std::string output_filename;
        numbers.reserve(100000);

        fin.open(("../input_files/" + filename).c_str());

        if(fin.fail())
        {
          std::cerr << "Sort: Cannot open file " << filename << std::endl;
          return;
        }

        array = new char[size + 1];
        fin.seekg(offset);
        fin.read(array, size);
        fin.close();
        array[size] = '\0';

        s << array;
        delete [] array;

        int num;
        while(s >> num)
        {
          numbers.push_back(num);
        }

        std::sort(numbers.begin(), numbers.end());

        std::stringstream fname;
        fname << "../intermediary_files/" << filename << "offset" << offset
          << "sorted" << my_ip << my_port;
        output_filename = fname.str();
        fout.open(output_filename.c_str());
        for(unsigned int i = 0; i < numbers.size(); i++)
        {
          fout << numbers[i] << " ";
        }
        fout.close();

        boost::shared_ptr<TSocket> socket(new TSocket(server_ip, server_port));
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

        MR_ServerInterfaceClient Server(protocol);

        transport->open();
        bool fileExists = Server.sendFilename(output_filename, my_ip, my_port, offset, size);
        transport->close();

        if(fileExists)
        {
          //some other node beat us to it.  delete file
          remove(output_filename.c_str());
        }

      }
      gettimeofday(&tv2, NULL); //set heartbeat to current time

      pthread_mutex_lock(&sort_lock);
      sort_time += tv2.tv_sec * 1000000 + tv2.tv_usec - (tv1.tv_sec * 1000000 + tv1.tv_usec);
      num_sort++;
      pthread_mutex_unlock(&sort_lock);
    }
    //Sort in ascending order
    void Merge(const std::vector<std::string> & sorted_inter_files,
        const int64_t task_number) {
      struct timeval tv1, tv2;
      gettimeofday(&tv1, NULL);
      // Your implementation goes here
      if(heartbeat && task_count % 6 == 0)
      {
        if((double)rand()/RAND_MAX * 100 <= fail_prob)
        {
          heartbeat = false;
          std::cout << std::endl << "Failure Injection: Compute Node failure! Node will be running next task." << std::endl;
        }
      }
      if(heartbeat) {
        task_count++;
        printf("Merging\n");
        std::ifstream fin;
        std::ofstream fout;
        std::string output_filename;
        std::vector<int> numbers[sorted_inter_files.size()];
        std::vector<int> merged_numbers;
        int number;

        if(sorted_inter_files.size() == 0)
          return;

        if(sorted_inter_files.size() == 1) { //Cannot merge only one file
          output_filename = sorted_inter_files[0];
        } else {
          std::stringstream fname;
          fname << "../intermediary_files/merged_" << task_number << "_" << my_ip << "_" << my_port;
          output_filename = fname.str();

          for(unsigned int i = 0; i < sorted_inter_files.size(); i++) {
            numbers[i].reserve(400);

            fin.open(sorted_inter_files[i].c_str());
            if(fin.fail())
            {
              std::cout << "Cannot open file " << sorted_inter_files[i] << std::endl;
              boost::shared_ptr<TSocket> socket(new TSocket(server_ip, server_port));
              boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
              boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

              MR_ServerInterfaceClient Server(protocol);
              transport->open();
              Server.callback_merge(output_filename, my_ip, my_port, task_number);
              transport->close();
              return;
            }
            //Read numbers into vector
            while(fin >> number) numbers[i].push_back(number);
            fin.close();

          }

          for(unsigned int i = 0; i < sorted_inter_files.size(); i++) {
            if(merged_numbers.size() == 0) {
              merged_numbers = MergeHelper(numbers[i], numbers[i+1]);
              i++;
            } else {
              merged_numbers = MergeHelper(merged_numbers, numbers[i]);
            }
          }

          fout.open(output_filename.c_str());
          for(unsigned int i = 0; i < merged_numbers.size(); i++) {
            fout << merged_numbers[i] << " ";
          }
          fout.close();
        }

        //Return result back to server
        boost::shared_ptr<TSocket> socket(new TSocket(server_ip, server_port));
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

        MR_ServerInterfaceClient Server(protocol);
        transport->open();
        bool fileExists = Server.callback_merge(output_filename, my_ip, my_port, task_number);
        transport->close();
        if(fileExists)
        {
          remove(output_filename.c_str());
        }
      }

      gettimeofday(&tv2, NULL); //set heartbeat to current time

      pthread_mutex_lock(&merge_lock);
      merge_time += tv2.tv_sec * 1000000 + tv2.tv_usec - (tv1.tv_sec * 1000000 + tv1.tv_usec);
      num_merge++;
      pthread_mutex_unlock(&merge_lock);
    }

    std::vector<int> MergeHelper(std::vector<int> a, std::vector<int> b) {
      std::vector<int> c;
      c.reserve(a.size()+b.size());

      if(a.size() == 0) return b;
      else if (b.size() == 0) return a;

      unsigned int i = 0, j = 0;
      while(i < a.size() && j < b.size()) {
        if(a[i] > b[j]) {
          c.push_back(b[j]);
          j++;
        } else {
          c.push_back(a[i]);
          i++;
        }
      }

      while(i < a.size()) {c.push_back(a[i]); i++;}

      while(j < b.size()) {c.push_back(b[j]); j++;}

      return c;
    }

    void maybeFail() {
      if(heartbeat)
      {
        if((double)rand()/RAND_MAX * 100 <= fail_prob)
        {
          heartbeat = false;
          std::cout << std::endl << "Failure Injection: Compute Node failure! Node will be running next task." << std::endl;
        }
      }
    }

    void outputStats() {
      std::cout << "Number of sort tasks:   " << num_sort << std::endl
                << "Number of merge tasks:  " << num_merge << std::endl;
      if(num_sort != 0)
       std::cout << "Average time for sort:  " << sort_time / num_sort / 1000 << "ms" << std::endl;
      if(num_merge != 0)
       std::cout << "Average time for merge: " << merge_time / num_merge / 1000 << "ms" << std::endl;
      num_sort = 0;
      num_merge = 0;
      sort_time = 0;
      merge_time = 0;
    }


};

void* TimerWrapper(void* useless)
{
  int64_t count = 0;
  while(true)
  {
    count++;
    ((MR_ComputeNodeInterfaceHandler*)ComputeNodeHandle)->sendHB();
    //check fail probability every 400ms
    /*if(count % 30 == 0)
      ((MR_ComputeNodeInterfaceHandler*)ComputeNodeHandle)->maybeFail();*/
    usleep(100000); //run every 100ms
  }
  return useless;
}

/*Returns IP Address of local machine*/
std::string getIPAddress() {
  struct ifaddrs * ifAddrStruct = NULL;
  struct ifaddrs * ifa = NULL;
  void * tmpAddrPtr = NULL;
  std::string IPAddress = "";

  getifaddrs(&ifAddrStruct);

  for(ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
    if(!ifa->ifa_addr) {
      continue;
    }

    if(ifa->ifa_addr->sa_family == AF_INET) {
      tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
      char addressBuffer[INET_ADDRSTRLEN];
      inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);
      IPAddress = std::string(addressBuffer);
    }
  }

  if(ifAddrStruct != NULL)
    freeifaddrs(ifAddrStruct);

  return IPAddress;
}

int main(int argc, char **argv) {
  if(argc != 5) {
    std::cout << "Usage: ./compute_node <port> <server_ip> <server_port> <fail_probability 0-100>" << std::endl;
    return 1;
  }

  srand(time(0));

  sscanf(argv[4], "%lf", &fail_prob);
  server_port = atoi(argv[3]);
  server_ip = argv[2];
  my_ip = getIPAddress();
  my_port = atoi(argv[1]);
  //Register with server
  boost::shared_ptr<TSocket> socket(new TSocket(server_ip, server_port));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

  MR_ServerInterfaceClient Server(protocol);

  transport->open();
  int status = Server.Register(my_ip, my_port);
  transport->close();
  if(status == -1) {
    std::cout << "Couldn't register with server!" << std::endl;
  } else {
    std::cout << "Successfully registered with server" << std::endl;
  }

  shared_ptr<MR_ComputeNodeInterfaceHandler> handler(new MR_ComputeNodeInterfaceHandler());
  shared_ptr<TProcessor> processor(new MR_ComputeNodeInterfaceProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(my_port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TThreadedServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}
