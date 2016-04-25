#!/bin/bash
cd ./gen-cpp-node
make clean
make all
for i in {8945..8955}
do
	konsole -e ./compute_node $i 128.101.39.169 8456 $1
	sleep 1
done
