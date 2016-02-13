/*
CSci 4061 Spring 2015 Assignment 4
Henry Grittner, 4560922
David Schoder, 4552990
These functions control the html file and logging
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>

#ifndef MISCFUNCS_H
#define MISCFUNCS_H

//external variables
extern FILE *htmlFile;
extern FILE *LogFile;
extern int fileCount;
extern int dirCount;
extern int StopTime;

//struct to hold the file info for each file
typedef struct FileInfoNode
{
	ino_t FileID;
	char* FullFileName; //with path
	char* FileName;		//no path
	char* FileType;
	off_t FileSize;
	time_t TimeofModification;
	pthread_t ThreadID;
}FileInfoNode;

//global variables
int timeval = 1;
int numGIF = 0, numJPG = 0, numPNG = 0, numBMP = 0;

//declare functions
static void timer_handler(int signum);
void getFileInfo(char *fileName);
int getFileExtension(char *filename);


//######################################################Funcs

//handler for log timer
//prints to log file every time timer activates
static void timer_handler(int signum)
{
	//if we should stop logging, exit
	if (StopTime == 1)
		{return;}
	
	//add entry to log file and update time
	fprintf(LogFile,"-------- Time %d ms\t#dir\t%d\t#files\t%d --------\n", timeval, dirCount, fileCount);
	timeval++;
}


//gets the file info for the given filename and adds it to the html file
void getFileInfo(char *fileName)
{
	//create filestat struct for file information
	struct stat *fileStats = (struct stat *)malloc(sizeof(struct stat));
	//puts file info into fileStats struct
	stat(fileName,fileStats);
	FileInfoNode *info = (FileInfoNode *)malloc(sizeof(FileInfoNode));
	
	//get information into FileInfoNode
	info->FileID = fileStats->st_ino;
	info->FullFileName = fileName;
	info->FileName = strrchr(fileName, '/') + 1;
	info->FileType = strrchr(fileName,'.') + 1;
	info->FileSize = fileStats->st_size;
	info->TimeofModification = fileStats->st_mtime;
	info->ThreadID = pthread_self();
	
	//update html file with image and info
	fprintf(htmlFile, "\n<a href=\"%s\">\n", info->FullFileName);
	fprintf(htmlFile, "\t<img src=\"%s\" width=100 height=100> </img>\n", info->FullFileName);
	fprintf(htmlFile, "</a>\n");
	fprintf(htmlFile, "<p align= \"left\">\n");
	fprintf(htmlFile, "\t%d, %s, %s, %d, %s, 0x%lx\n",
		(int)info->FileID,
		info->FileName,
		info->FileType,
		(int)info->FileSize,
		asctime(localtime(&(info->TimeofModification))),
		info->ThreadID);
	fprintf(htmlFile, "</p>\n");
	
	//flush file and free memory
	fflush(htmlFile);
	free(info);
	free(fileStats);
}


//check to see if file is an image
	//1=bmp, 2=gif, 3=jpg, 4=png, 0=other
int getFileExtension(char *filename)
{
	char *extension;
	int numComp;
	//get extension of current file
	extension = strrchr(filename,'.');
	
	if (extension == NULL)
	{
		return 0;	//file has no extension, can't be an image
	}

	numComp = strncmp(extension,".bmp",4);	//check *.bmp

	//gets rid of . and .. directories in folder
	if (numComp < 0){
		return 0;
	}

	if (numComp == 0){
		return 1;	//file is bmp
	}
	else {
		numComp = strncmp(extension,".gif",4);	//check *.gif
		if (numComp == 0){
			return 2;
		}
		else {
			numComp = strncmp(extension,".jpg",4);	//check *.png
			if (numComp == 0){
				return 3;
			}
			else {
				numComp = strncmp(extension,".png",4);	//check *.jpg
				if (numComp == 0){
					return 4;
				}
			}
		}
	}
	return 0;	//otherwise file is of unknown type
}

#endif

