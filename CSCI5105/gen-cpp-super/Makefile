GEN_SRC := DHTNode_SupernodeInterface.cpp \
					 DHTNode_SupernodeInterface_constants.cpp \
					 DHTNode_SupernodeInterface_types.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY:	all clean

all: supernode

%.o: %.cpp
	$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

supernode: DHTNode_SupernodeInterface_server.o $(GEN_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift -pthread

clean:
	$(RM) *.o supernode
