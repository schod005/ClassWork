/*
CSci 4061 Spring 2015 Assignment 2
Henry Grittner, 4560922
David Schoder, 4552990

This file contains misc. functions used to work with images and file lists.
*/

#ifndef FUNCS_H
#define FUNCS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include "listfuncs.h"


//declare functions
int getImageType(pid_t procID);
int getFileExtension(char *filename);
struct FileList* createFileList(char *directory);
void removeNextFileFromList(struct FileList *curList, pid_t child_pid);


//return the type of image the process should convert based on pid
	//1=bmp, 2=gif, 3=png
int getImageType(pid_t procID){
	if ((procID % 2) == 0){
		return 3;
	}
	else if ((procID % 3) == 0){
		return 1;
	}
	else {
		return 2;
	}
}


//returns the type of image corresponding to filename
	//1=bmp, 2-gif, 3=png, 0=other
int getFileExtension(char *filename){
	char *extension;
	int numComp, numComp2;
	extension = strrchr(filename,'.');

	numComp = strncmp(extension,".BMP",4);	//check *.BMP
	numComp2 = strncmp(extension,".bmp",4);	//check *.bmp

	//gets rid of . and .. directories in folder
	if (numComp < 0){
		return 0;
	}

	if ((numComp == 0) || (numComp2 == 0)){
		return 1;
	}
	else {
		numComp = strncmp(extension,".GIF",4);	//check *.GIF
		numComp2 = strncmp(extension,".gif",4);	//check *.gif
		if ((numComp == 0) || (numComp2 == 0)){
			return 2;
		}
		else {
			numComp = strncmp(extension,".PNG",4);	//check *.PNG
			numComp2 = strncmp(extension,".png",4);	//check *.png
			if ((numComp == 0) || (numComp2 == 0)){
				return 3;
			}
		}
	}
	return 0;	//otherwise file is of unknown type
}


//create the linked-list with files from input directory
struct FileList* createFileList(char *directory){
	char *curFile;
	struct dirent *entry;

	//create and init new list
	struct FileList *newlist = (struct FileList*)malloc(sizeof(struct FileList));
	newlist->headnode = NULL;
	newlist->tailnode = NULL;

	DIR *inDir = opendir(directory);	//open input directory for reading

	//read all files in directory
	while ((entry = readdir(inDir)) != NULL){
		curFile = entry->d_name;		//get name of file
		if (getFileExtension(curFile) != 0){	//make sure file is image
			addNode(newlist, curFile);	//add file to list
		}
	}
	closedir(inDir);	//close input_dir
	return newlist;		//return new file list
}


//removes file that child process will convert from linked list based on pid
void removeNextFileFromList(struct FileList *curList, pid_t child_pid)
{
	int filetype = getImageType(child_pid);			//get type of image
	struct Node *node = findNextImage(curList, filetype);	//find image to be converted
	if(node != NULL){
		deleteNode(curList, node);	//delete node if it exists
	}
}

#endif

