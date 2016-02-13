CC=g++
CFLAGS=-std=c++0x -O3
INCLUDES=-I \
	./SFML-2.0/include

LIBRARIES=-L \
	./SFML-2.0/lib

LIBS= \
	-lsfml-graphics \
	-lsfml-window \
	-lsfml-system

SnakeAI:
	$(CC) $(CFLAGS) main.cpp $(INCLUDES) $(LIBRARIES) $(LIBS) 
	echo "export LD_LIBRARY_PATH=./SFML-2.0/lib && ./a.out" > run
	chmod 700 run
