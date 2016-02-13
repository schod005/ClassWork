#makefile
# CSci 4061 Spring 2015 Assignment 5
# Henry Grittner, 4560922
# David Schoder, 4552990
# This is the makefile for the client and server programs
#
# Options:
#    make client
#    make server
#    make all

client: client.c md5sum.c md5sum.h clientFuncs.h
	gcc client.c md5sum.c -o client -lcrypto

server: server.c directoryFuncs.h serverFuncs.h md5sum.c md5sum.h
	gcc server.c md5sum.c -o server -lcrypto

all: client server
