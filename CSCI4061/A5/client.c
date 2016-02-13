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
 * 		./client [IP Address] [Port] [Optional Extension]
 **/

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include "md5sum.h"
#include "clientFuncs.h"


//function declarations
int initialize(int argc, char **argv);
void getCSV();
void getImages();
int checkArg(char* arg);
void interactive();
void passive();


//global variables
char buffer[256];
char *mode, *ext;
int clientSocket, len, numfiles;
struct sockaddr_in serverAddress, clientAddress;
socklen_t clientSize;
FILE *htmlFile;	//download.html


int main(int argc, char **argv)
{
	//check args and initialize TCP socket
	if(initialize(argc, argv) == 1)
	{
		return 1;
	}
	getCSV();				//download CSV file
	getImages();			//download images
	close(clientSocket);	//close socket
	fclose(htmlFile);		//close html file
	
	return 0;
}


//checks arguments and sets up a TCP socket
int initialize(int argc, char **argv)
{
	//get running mode depending on number of arguments
	mode = (char *)malloc(sizeof(char));
	if(argc == 3)
	{
		printf("Interactive mode\n");
		*mode = 'I';
	}
	else if(argc == 4)
	{
		printf("Passive mode\n");
		*mode = 'P';
		if(checkArg(argv[3]) == 1)	//make sure extension is png, gif, or tiff
		{
			printf("%s is not a valid extension\n",argv[3]);
			return 1;
		}
	}
	else	//wrong number of args
	{
		printf("Usage:\n\t./client [IP Address] [Port] [Optional Extension]\n\n");
		return 1;
	}
	
	//Receive all files from server and store in ./images
	if(mkdir("./images",0777) == -1)
	{
		if(errno != EEXIST) //if folder exists, we don't care
		{	
			perror("ERROR");
			printf("\tCould not create output directory \"./images\"\n");
			return 1;
		}
	}
	
	//create socket connection
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket < 0)
	{
		printf("Error creating socket\n");
		return 1;
	}
	clientSize = sizeof(clientAddress);

	bzero(&serverAddress,sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(argv[1]);
	serverAddress.sin_port = htons(atoi(argv[2]));
	
	//connect to server program
	if (connect(clientSocket, (struct sockaddr *)&serverAddress,sizeof(serverAddress)) < 0)
	{
		printf("Error connecting to server\n");
		return 1;
	}
	printf("Connected...\n");
	
	//create html file and initialize
	htmlFile = fopen("download.html","w");
	fprintf(htmlFile, "<html>\n\t<head>\n\t\t<title>Downloaded images</title>\n\t</head>\n\t<body>\n\t<h1> Downloaded images</h1>\n\t<pre>\n");
	fflush(htmlFile);
	return 0;
}


//download the csv file from the server
void getCSV()
{	
	//Receive catalog.csv
	printf("Receiving file list from server...\n");
	write(clientSocket, "CSV", 3);	//message to send file
	receiveCSV(clientSocket);		//receive file
	numfiles = displayCSV();		//print csv file to terminal
}


//get the images depending on run mode
void getImages()
{
	if(*mode == 'I')
		interactive();		//start interactive mode
	else if(*mode == 'P')
		passive();			//start passive mode
	
	//finish html file
	fprintf(htmlFile,"\t\t</pre>\n\t</body>\n</html>");
	fflush(htmlFile);
}


//get images in interactive mode
void interactive()
{
	//send ready message
	write(clientSocket, mode, 1);
	
	char filename[512];
	char filename2[512];
	char buf[10];
	int input;
	
	//repeat until the user wants to quit
	while(input != 0)
	{
		printf("Enter ID to download (0 to quit): ");
		scanf("%s",buf);	//get value from keyboard
		if ((buf[0] < 48) || (buf[0] > 57))		//check if input is a number
		{
			printf("Invalid ID value: %s\n", buf);
			continue;
		}
		input = atoi(buf);	//convert input to int
		if (input == 0)		//see if we should quit
		{
			write(clientSocket, "Input", 1);
			sprintf(buf, "%d", input);
			write(clientSocket,buf,strlen(buf)); //tell the server to quit
			continue;
		}
		if(input > numfiles || input < 0)	//make sure input is in range
		{
			printf("Invalid file number: %d\n", input);
			continue;
		}
		
		write(clientSocket, "Input", 1);		//send input message
		sprintf(buf, "%d", input);				//make sure there are only number characters in buffer
		write(clientSocket,buf,strlen(buf));	//send file ID
		
		//receive image
		strcpy(filename, "./images/");
		read(clientSocket,filename2,512);
		strcat(filename,filename2);
		receiveFile(clientSocket,filename);
		htmlAdd(htmlFile, filename2);
		printf("Downloaded %s\n",filename2);
	}
	
	printf("All files received\n");
}


//download images in passive mode
void passive()
{
	//send ready message
	write(clientSocket, mode, 1);
	
	char filenum[10];
	int num;
	char filename[512];
	char filename2[512];
	write(clientSocket,ext,1);//send first letter of extension
	read(clientSocket,filenum,10);//receive number of files
	num = atoi(filenum);
	printf("Receiving %d files:\n", num);
	
	//repeat until we have all the files
	while(num)
	{
		write(clientSocket, "Go", 1);	//send ready message
		num--;
		strcpy(filename, "./images/");	//create full filename of image
		read(clientSocket, filename2, 512);
		strcat(filename,filename2);
		int bytes = receiveFile(clientSocket, filename);	//receive file
		htmlAdd(htmlFile, filename2);	//add file to html
		printf("    Downloaded %s: %d\n",filename, bytes);
	}
	
	printf("All files received\n");
}


//check to make sure the extension passed in is valid
int checkArg(char *Arg)
{
	if(strncmp(Arg,"png",3) == 0 || strncmp(Arg,"tiff",4) == 0 || strncmp(Arg,"gif",3) == 0)
	{
		ext = (char *)malloc(sizeof(char));
		strncpy(ext,Arg,1);
		return 0;
	}
	return 1;
}


