/*
CSci 4061 Spring 2015 Assignment 5
Henry Grittner, 4560922
David Schoder, 4552990
These are misc. functions for the client program
*/

#include <stdio.h>
#include <stdlib.h>
#include "md5sum.h"

#ifndef CLIENTFUNCS_H
#define CLIENTFUNCS_H

//declare functions
void htmlAdd(FILE *htmlFile, char *filename);
int checkSumMatch(char *filename);
int receiveCSV(int socket);
int receiveFile(int socket, char* filename);
int displayCSV();


//add an image to the html
void htmlAdd(FILE *htmlFile, char *filename)
{
	//generate checksum and check against catalog.csv
	if(checkSumMatch(filename))	//checksum match, link to file
	{
		fprintf(htmlFile,"(Checksum match!) ");
		fprintf(htmlFile,"\t<a href=\"images/%s\">%s</a><br />\n",filename,filename);
	}
	else	//checksum mismatch, don't link to file
	{
		fprintf(htmlFile,"(Checksum mismatch!) ");
		fprintf(htmlFile,"\t%s<br />\n",filename);
	}
}


//generate the checksum for a file and compare to value in catalog.csv
int checkSumMatch(char *filename)
{
	//open catalog.csv
	FILE* curFile = fopen("./images/catalog.csv", "r");
	if (curFile == NULL)
	{
		printf("Unable to read ./images/catalog.csv\n");
		return 0;
	}
	
	//generate full image filename
	char fullFilename[strlen(filename) + 10];
	strcpy(fullFilename, "./images/");
	strcat(fullFilename, filename);
	
	//values for reading from csv file
	char downloadHash[MD5_DIGEST_LENGTH*2 + 1];
	int nameLen = strlen(filename);
	ssize_t size = 0;
	char* lineBuf = NULL;
	size_t curSize = 0;
	
	//read lines from the csv file until we find a match
	while (size != -1)
	{
		//read a line from the csv file
		size = getline(&lineBuf, &curSize, curFile);
		
		//check to see if line starts with filename
		if (strncmp(lineBuf, filename, nameLen) == 0)
		{
			char* hash = strrchr(lineBuf, ',');	//get location of hash value
			hash++;	//don't want to read ',' character
			strncpy(downloadHash, hash, MD5_DIGEST_LENGTH*2);	//store hash from csv file
			downloadHash[MD5_DIGEST_LENGTH*2] = '\0';	//make into a string
			break;	//exit loop
		}
	}
	
	if (size == -1)	//filename not found in csv file
	{
		return 0;
	}
	
	//generate hash for image file
	unsigned char curHash[MD5_DIGEST_LENGTH];
	md5sum(fullFilename, curHash);
	
	//write generated hash to a string
	char calculatedHash[MD5_DIGEST_LENGTH*2 + 1];
	char* pcalcHash = calculatedHash;
	int i;
	for (i=0; i<MD5_DIGEST_LENGTH; i++)
	{
		sprintf(pcalcHash, "%02x", curHash[i]);	
		pcalcHash += 2;
	}
	calculatedHash[MD5_DIGEST_LENGTH*2] = '\0';
	
	//check to see if both hashes match one another
	if (strcmp(downloadHash, calculatedHash) == 0)
	{
		return 1;
	}
	return 0;
}


//receive the csv file from the server
int receiveCSV(int socket)
{
	//show we are ready to receive CSV
	if (write(socket, "Ready", 1) == 0)
	{
		return 0;	//can't write to socket, return
	}
	char buffer[512];
	
	//first get size of file in bytes from server
	if (read(socket, buffer, 512) == 0)
	{
		return 0;	//can't read from socket, return
	}
	int size = atoi(buffer);
	
	//create CSV file in ./images directory
	FILE* curFile = fopen("./images/catalog.csv", "w");
	if (curFile == NULL)
	{
		printf("ERROR creating file: %s\n","./images/catalog.csv");
		write(socket, "No", 1);
		return 0;
	}
	
	//send acknowledgement
	write(socket, "Yes", 1);
	
	//receive file and write to catalog.csv
	int bytesReceived = 0;
	while (bytesReceived < size)
	{
		int curBytes = read(socket, buffer, 512);
		fwrite(buffer, curBytes, 1, curFile);
		bytesReceived += curBytes;
	}
	
	fflush(curFile);
	fclose(curFile);
	
	//send acknowledgment message
	write(socket, "Done", 1);
	
	return bytesReceived;
}


//receives a file from the server and saves it to filename
	//returns the number of bytes received
int receiveFile(int socket, char* filename)
{
	//show we are ready to receive a file
	if (write(socket, "Ready", 1) == 0)
	{
		return 0;	//can't write to socket, return
	}
	
	char buffer[512];
	
	//first get size of file in bytes from server
	if (read(socket, buffer, 512) == 0)
	{
		return 0;	//can't read from socket, return
	}
	int size = atoi(buffer);
	
	//create image file
	FILE* curFile = fopen(filename, "w");
	if (curFile == NULL)
	{
		printf("ERROR creating file: %s\n", filename);
		write(socket, "No", 1);
		return 0;
	}

	//send acknowledgement
	write(socket, "Yes", 1);
	
	//receive file data and write to image file
	int bytesReceived = 0;
	while (bytesReceived < size)
	{
		int curBytes = read(socket, buffer, 512);
		fwrite(buffer, curBytes, 1, curFile);
		bytesReceived += curBytes;
	}
	
	fflush(curFile);
	fclose(curFile);

	//send acknowledgement message
	write(socket, "Done", 1);
	
	return bytesReceived;
}


//Displays contents of catalog.csv
	//return number of files
int displayCSV()
{
	printf("===============================\n");
	printf("Dumping contents of catalog.csv\n");
	
	//open csv file for reading
	FILE* csv = fopen("./images/catalog.csv","r");
	char buffer[256];
	char filename[128];
	int i = 0;
	char *comma;
	int index;
	fgets(buffer,256,csv); //don't care about first line
	
	//write file to terminal
	while(fgets(buffer,256,csv) != NULL)
	{
		i++;
		comma = strchr(buffer, ','); //find comma index
		if(comma == NULL)
		{
			printf("Error\n");
			return;
		}
		index = comma - buffer; //compute comma index
		strncpy(filename,buffer,index);
		filename[index] = '\0';
		printf("[%d]	%s\n",i,filename);
	}
	fclose(csv);
	printf("===============================\n");
	return i;
}

#endif
