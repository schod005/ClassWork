#!/bin/bash
cd gen-cpp-node
make clean
make all
for i in {6780..6788}
do
	konsole -e ./dht_node $i 128.101.37.70 8456 &
	sleep 1
done
