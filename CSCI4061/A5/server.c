/**
 * Information
 * CSci 4061 Spring 2015 Assignment 5
 * Name1=Henry Grittner
 * Name2=David Schoder
 * StudentID1=4560922
 * StudentID2=4552990
 * CSELabs machine: KH4250-01, KH1262-01
 * Commentary:
 * This code implements a simple client-server TCP socket program
 * that is capable of transmitting images between two computers.
 * The server program looks for all png, gif, and tiff files in a
 * given input directory, and then creates a catalog of these files.
 * The client program connects to the server over a tcp socket,
 * downloads the catalog file, and then downloads either specific
 * images or all images of a certain type. The client saves links to
 * the images in an html file, and error checking is performed using
 * the md5 hash function.
 * 
 * Usage:
 * 		./server [Port] [Directory]
 **/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "md5sum.h"
#include "directoryFuncs.h"
#include "serverFuncs.h"


//function declarations
int initialize(int argc, char **argv);
void sendCSV();
void sendImages();
void interactive();
void passive();


//global variables
char buffer[256];
int clientSocket, serverSocket, len, childpid, CSVsize;
struct sockaddr_in serverAddress, clientAddress;
FileList* files;
socklen_t clientSize;
char *inputDir;


int main(int argc, char **argv)
{
	//check arguments and set up TCP socket
	if(initialize(argc, argv) == 1)
	{
		return 1;
	}
	sendCSV();	//send catalog.csv to client
	sendImages();	//send images to client
	close(clientSocket);	//close socket
	close(serverSocket);	//close socket
	
	return 0;
}


//check input arguments and set up TCP socket
int initialize(int argc, char **argv)
{
	//check number of arguments
	if(argc != 3)
	{
		printf("Usage:\n\t./server [Port] [Directory]\n\n");
		return 1;
	}
	
	inputDir = argv[2];
	
	//create linked list with all files in inputDir
	files = createFileList(inputDir);
	if (files->HeadNode == NULL)
	{
		printf("Error finding images: %s\n", inputDir);
		return 1;
	}
	
	//print out list of images
	printf("List of images found:\n");
	FileNode* curNode = files->HeadNode;
	while(curNode != NULL)
	{
		printf("    %s\n", curNode->FullFileName);
		curNode = curNode->NextNode;
	}
	
	//create catalog.csv in current working directory
	CSVsize = createCatalog(".", files);
	
	//set up the TCP socket
	printf("Creating socket...\n");

	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0)
	{
		printf("Error creating socket\n");
		return 1;
	}
	clientSize = sizeof(clientAddress);

	bzero((char*)&serverAddress,sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(atoi(argv[1]));

	//bind socket
	if (bind(serverSocket, (struct sockaddr *)&serverAddress,sizeof(serverAddress)) < 0)
	{
		printf("Error binding socket\n");
		return 1;
	}
	
	//listen to socket
	listen(serverSocket,1024);
	
	//connect to client
	clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddress, &clientSize);
	if (clientSocket < 0)
	{
		printf("Error accepting client socket\n");
		return 1;
	}
	printf("Connected...\n");
	return 0;
}


//send the csv file to the client
void sendCSV()
{
	//wait for client to transmit "CSV" as a ready message
	while(strcmp(buffer,"CSV") != 0)
	{
		read(clientSocket, buffer, 3);
		buffer[3] = '\0';
	}
	printf("Transmitting CSV file\n");
	transmitCSV(clientSocket,CSVsize);	//send catalog.csv
	
}


//send images to client based on mode
void sendImages()
{
	char *mode = (char *)malloc(sizeof(char));
	read(clientSocket,mode,1);	//read mode from socket
	
	if(*mode == 'I')
	{
		interactive();	//send images interactively
	}
	else if(*mode == 'P')
	{
		passive();	//send images passively
	}
}


//send images interactively
void interactive()
{
	printf("Entering interactive mode\n");
	//wait for client to transmit image number
	int index = 1;
	int i;
	int bytes;
	FileNode *curImage = files->HeadNode;
	
	//keep transmitting images until client indicates done
	while(index != 0)
	{
		//empty buffer until 'I' is received
		read(clientSocket, buffer, 1);
		while (buffer[0] != 'I')
		{
			read(clientSocket, buffer, 1);
		}
		//get input and convert to integer
		bytes = read(clientSocket, buffer,10);
		buffer[bytes] = '\0';
		index = atoi(buffer);
		if (index == 0)
		{
			break;
		}
		
		//send file
		curImage = files->HeadNode;
		for(i = 1; i < index; i++)
			curImage = curImage->NextNode;
		printf("    Received command to send %s\n",curImage->FileName);
		write(clientSocket,curImage->FileName,strlen(curImage->FileName) + 1);
		bytes = transmitImage(clientSocket, curImage->FullFileName, curImage->FileSize);
		printf("    Transmitted %d bytes\n", bytes);
	}
	
	printf("Done transmitting\n");
}


//send images passively
void passive()
{
	FileList *list = (FileList*)malloc(sizeof(FileList)); //list of files to be sent
	list->HeadNode = NULL;
	list->TailNode = NULL;
	FileNode *curImage = files->HeadNode;
	printf("Entering passive mode\n");
	char *ext = (char *)malloc(sizeof(char));
	char *extension;
	char *curextension;
	int numfiles = 0;
	int length;
	int extsize;
	int bytes;
	read(clientSocket,ext,1);
	
	//check type of files the client wants
	if(*ext == 'p')	//png files
	{
		extension = (char *)malloc(3*sizeof(char));
		curextension = (char *)malloc(3*sizeof(char));
		strcpy(extension,"png");
		extsize = 3;
	}
	else if(*ext == 't')	//tiff files
	{
		extension = (char *)malloc(4*sizeof(char));
		curextension = (char *)malloc(4*sizeof(char));
		strcpy(extension,"tiff");
		extsize = 4;
	}
	else if(*ext == 'g')	//gif files
	{
		extension = (char *)malloc(3*sizeof(char));
		curextension = (char *)malloc(3*sizeof(char));
		strcpy(extension,"gif");
		extsize = 3;
	}
	
	//count the number of images of the given type
	while(curImage != NULL)
	{
		length = strlen(curImage->FileName);
		curextension = &curImage->FileName[length-extsize];
		if (strcmp(extension,curextension) == 0)
		{
			numfiles++;
			addNodeToList(list,curImage); //save files for sending
		}
		curImage = curImage->NextNode;
	}

	char filenum[10];
	sprintf(filenum,"%d",numfiles);
	write(clientSocket,filenum,10);//send number of images
	curImage = list->HeadNode;
	printf("Sending all files ending in %s\n",extension);
	
	//send the images
	while(numfiles)
	{
		buffer[0] = 'X';
		//check for ready message from client
		while (buffer[0] != 'G')
		{
			read(clientSocket, buffer, 1);
		}

		//send the images
		printf("    Sending: %s\n",curImage->FileName);
		write(clientSocket, curImage->FileName, strlen(curImage->FileName) + 1);
		bytes = transmitImage(clientSocket, curImage->FullFileName, curImage->FileSize); //send images
		printf("    Transmitted %d bytes\n", bytes);
		numfiles--;
		curImage = curImage->NextNode;
	}
	
	printf("Done transmitting\n");
}
