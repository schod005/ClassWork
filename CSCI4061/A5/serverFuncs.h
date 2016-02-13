/*
CSci 4061 Spring 2015 Assignment 5
Henry Grittner, 4560922
David Schoder, 4552990
These are misc. functions for the server program
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "md5sum.h"


#ifndef SERVERFUNCS_H
#define SERVERFUNCS_H

//declare functions
int transmitCSV(int socket, int size);
int transmitImage(int socket, char* filename, int size);
int createCatalog(char* directory, FileList* files);
void generateMD5Sum(char* file, unsigned char* buffer);


//sends the catalog of images to the client
	//returns the number of bytes sent
int transmitCSV(int socket, int size)
{
	//open the CSV file for sending
	FILE *curFile = fopen("catalog.csv", "r");
	if (curFile == NULL)
	{
		printf("ERROR: Unable to open file %s\n", "catalog.csv");
		return 0;
	}
	
	char buffer[512];
	buffer[0] = 'X';
	int curWritten = 0;
	
	//wait for ready signal from client
	while (buffer[0] != 'R')
	{
		if (read(socket, buffer, 1) == 0)
		{
			return 0;	//can't read from socket, return
		}
	}
	
	//send the length of the file as a string
	sprintf(buffer, "%d", size);
	write(socket, buffer, strlen(buffer) + 1);
	
	//wait for acknowledgement from client
	while (buffer[0] != 'Y')
	{
		read(socket, buffer, 1);
		if (buffer[0] == 'N')
		{
			return 0;
		}
	}
	
	//send the file in 512 byte chunks
	int i;
	while ((size - curWritten) > 512)
	{
		for (i=0; i<512; i++)
		{
			buffer[i] = fgetc(curFile);
		}
		int bytes = write(socket, buffer, 512);
		if (bytes != 512)
		{
			printf("Error sending data\n");
			return curWritten + bytes;
		}
		curWritten += bytes;
	}
	
	//send the rest of the file
	for (i=0; i<(size - curWritten); i++)
	{
		buffer[i] = fgetc(curFile);
	}
	curWritten += write(socket, buffer, (size - curWritten));
	
	//wait for acknowledgement from client
	while (buffer[0] != 'D')
	{
		read(socket, buffer, 1);
	}
	
	fclose(curFile);
	return curWritten;
	
}


//sends an image file over the socket to the client
	//returns the number of bytes sent
int transmitImage(int socket, char* filename, int size)
{	
	//open the desired file for sending
	FILE *curFile = fopen(filename, "r");
	if (curFile == NULL)
	{
		printf("ERROR: Unable to open file %s\n", filename);
		return 0;
	}
	
	char buffer[512];
	buffer[0] = 'X';
	int curWritten = 0;
	
	//wait for ready signal from client
	while (buffer[0] != 'R')
	{
		if (read(socket, buffer, 1) == 0)
		{
			return 0;	//can't read from socket, return
		}
	}

	//send the length of the file as a string
	sprintf(buffer, "%d", size);
	write(socket, buffer, strlen(buffer) + 1);

	//wait for acknowledgement from client
	while (buffer[0] != 'Y')
	{
		read(socket, buffer, 1);
		if (buffer[0] == 'N')
		{
			return 0;
		}
	}
	
	//send the file in 512 byte chunks
	int i;
	while ((size - curWritten) > 512)
	{
		for (i=0; i<512; i++)
		{
			buffer[i] = fgetc(curFile);
		}
		int bytes = write(socket, buffer, 512);
		if (bytes != 512)
		{
			printf("Error sending data\n");
			return curWritten + bytes;
		}
		curWritten += bytes;
	}
	
	//send the rest of the file
	for (i=0; i<(size - curWritten); i++)
	{
		buffer[i] = fgetc(curFile);
	}
	curWritten += write(socket, buffer, (size - curWritten));
	
	//wait for acknowledgement from client
	while (buffer[0] != 'D')
	{
		read(socket, buffer, 1);
	}
	fclose(curFile);
	return curWritten;
}


//generates catalog.csv in the specified directory with the given files
	//returns size of file created
int createCatalog(char* directory, FileList* files)
{
	//create cvs file and write header
	char csvFileName[strlen(directory) + 13];
	strcpy(csvFileName, directory);
	strcat(csvFileName, "/catalog.csv");
	FILE *csvFile = fopen(csvFileName,"w");
	fprintf(csvFile, "filename, size, checksum\n");
	fflush(csvFile);
	//add an entry for each file in the list
	int i;
	FileNode* curFile = files->HeadNode;
	while (curFile != NULL)
	{
		fprintf(csvFile, "%s,", curFile->FileName);	//add name
		fprintf(csvFile, "%d,", curFile->FileSize);	//add size
		
		unsigned char curHash[MD5_DIGEST_LENGTH];
		generateMD5Sum(curFile->FullFileName, curHash);
		for (i=0; i<MD5_DIGEST_LENGTH; i++)
		{
			fprintf(csvFile, "%02x", curHash[i]);		//add hash characters
		}
		fprintf(csvFile, "\n");
		fflush(csvFile);
		
		curFile = curFile->NextNode;
	}
	fseek(csvFile,0L,SEEK_END);
	int size = ftell(csvFile);
	fclose(csvFile);
	return size;
}


//generates the MD5Sum for the specified file in the specified buffer
void generateMD5Sum(char* file, unsigned char* buffer)
{
	md5sum(file, buffer);
}

#endif

