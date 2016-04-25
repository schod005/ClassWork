#!/bin/bash
cd ../
make clean
make all
for i in {0..3}
do
	./client 128.101.37.94 8456 < scripts/$1 > data/file$i.txt &
done
