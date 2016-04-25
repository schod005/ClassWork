GEN_SRC := MR_ComputeNodeInterface.cpp \
					 MR_ComputeNodeInterface_constants.cpp \
					 MR_ComputeNodeInterface_types.cpp\
					 ../gen-cpp-server/MR_ServerInterface.cpp \
					 ../gen-cpp-server/MR_ServerInterface_constants.cpp \
					 ../gen-cpp-server/MR_ServerInterface_types.cpp
GEN_OBJ := $(patsubst %.cpp,%.o, $(GEN_SRC))

THRIFT_DIR := /usr/local/include/thrift
BOOST_DIR := /usr/local/include

INC := -I$(THRIFT_DIR) -I$(BOOST_DIR)

.PHONY:	all clean

all: compute_node

%.o: %.cpp
	$(CXX) -Wall -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H $(INC) -c $< -o $@

compute_node: MR_ComputeNodeInterface_server.o $(GEN_OBJ)
	$(CXX) $^ -o $@ -L/usr/local/lib -lthrift -pthread

clean:
	$(RM) *.o compute_node
