GEN_SRC := MR_ServerInterface.cpp \
					 MR_ServerInterface_constants.cpp \
					 MR_ServerInterface_types.cpp \
					 ../gen-cpp-node/MR_ComputeNodeInterface.cpp \
					 ../gen-cpp-node/MR_ComputeNodeInterface_constants.cpp \
					 ../gen-cpp-node/MR_ComputeNodeInterface_types.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY:	all clean

all: server

%.o: %.cpp
	$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@ -g

server: MR_ServerInterface_server.o $(GEN_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift -pthread -g

clean:
	$(RM) *.o server
