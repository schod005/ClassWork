#!/bin/bash
cd ../gen-cpp
make clean
make all
for i in {6780..6789}
do
	konsole -e ./file_server $i 0 128.101.37.94 8456 &
	sleep 1
done
