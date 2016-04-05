GEN_SRC := DHTNode_NodeInterface.cpp \
					 DHTNode_NodeInterface_constants.cpp \
					 DHTNode_NodeInterface_types.cpp \
					 ../gen-cpp-super/DHTNode_SupernodeInterface.cpp \
					 ../gen-cpp-super/DHTNode_SupernodeInterface_constants.cpp \
					 ../gen-cpp-super/DHTNode_SupernodeInterface_types.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY:	all clean

all: dht_node

%.o: %.cpp
	$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

dht_node: DHTNode_NodeInterface_server.o $(GEN_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift -pthread

clean:
	$(RM) *.o dht_node
