/*
CSci 4061 Spring 2015 Assignment 5
Henry Grittner, 4560922
David Schoder, 4552990
These are functions for looking through the input directory
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

#ifndef DIRECTORYFUNCS_H
#define DIRECTORYFUNCS_H


//linked list node to hold file information
typedef struct FileNode
{
	char* FullFileName; //with path
	char* FileName;		//no path
	int FileType;		//1=gif, 2=png, 3=tiff
	int FileSize;		//in bytes
	struct FileNode *NextNode;
}FileNode;


//linked list pointing to all the nodes
typedef struct FileList
{
	FileNode* HeadNode;	//the first node in the list
	FileNode* TailNode;	//the last node in the list
}FileList;


//define functions
FileList* createFileList(char* directory);
FileNode* createFileNode(char* filename);
void addNodeToList(FileList* filelist, FileNode* filenode);
void addListToList(FileList* filelist, FileList* listToAdd);
int getFileExtension(char* filename);


//searches through a directory for all gif, png, and tiff images
	//returns a linked list containing all the files
FileList* createFileList(char* directory)
{
	//create new empty filelist
	FileList *curlist = (FileList*)malloc(sizeof(FileList));
	curlist->HeadNode = NULL;
	curlist->TailNode = NULL;
	
	//open directory for reading
	DIR *inDir = opendir(directory);
	if (inDir == NULL)
	{
		return curlist;
	}

	//search all files in directory
	char *curFile;
	struct dirent *entry;
	while ((entry = readdir(inDir)) != NULL)
	{
		curFile = entry->d_name;			//get name of file
		//get full filename of file
		char fullFileName[strlen(curFile) + strlen(directory) + 2];
		strcpy(fullFileName, directory);
		strcat(fullFileName, "/");
		strcat(fullFileName, curFile);
		
		int curType = getFileExtension(curFile);
		
		if (curType > 0)	//if file is an image, add it to the list
		{
			FileNode* newnode = createFileNode(fullFileName);
			addNodeToList(curlist, newnode);
		}
		else if (curType == 0)	//if file is not an image, treat it like a directory
		{
			FileList* newlist = createFileList(fullFileName);
			addListToList(curlist, newlist);
			free(newlist);
		}
	}
	closedir(inDir);	//close input_dir
	return curlist;		//return new file list
}


//creates a FileNode object for a given file
FileNode* createFileNode(char* filename)
{
	//initialize new filenode
	FileNode* newnode = (FileNode*)malloc(sizeof(FileNode));
	newnode->NextNode = NULL;
	
	//copy full file name into node
	newnode->FullFileName = (char*)malloc(strlen(filename)+1);
	strcpy(newnode->FullFileName, filename);
	
	//pointer in fullfilename to short file name
	char* shortFilename = strrchr(newnode->FullFileName,'/');
	newnode->FileName = shortFilename + 1;
	
	//type of file
	newnode->FileType = getFileExtension(filename);
	
	//use stat to get file size
	struct stat *fileStats = (struct stat *)malloc(sizeof(struct stat));
	stat(filename,fileStats);
	newnode->FileSize = (int)(fileStats->st_size);
	free(fileStats);
	
	return newnode;
}


//adds a given FileNode to the given FileList
void addNodeToList(FileList* filelist, FileNode* filenode)
{
	if (filelist->HeadNode == NULL)
	{
		filelist->HeadNode = filenode;
		filelist->TailNode = filenode;
		return;
	}
	
	filelist->TailNode->NextNode = filenode;
	filelist->TailNode = filenode;
}


//adds all nodes in a given FileList to a different FileList
void addListToList(FileList* filelist, FileList* listToAdd)
{
	if (listToAdd->HeadNode == NULL)
	{
		return;
	}
	
	if (filelist->HeadNode == NULL)
	{
		filelist->HeadNode = listToAdd->HeadNode;
		filelist->TailNode = listToAdd->TailNode;
		return;
	}
	
	filelist->TailNode->NextNode = listToAdd->HeadNode;
	filelist->TailNode = listToAdd->TailNode;
}


//return the file extension of the file
	//1=gif, 2=png, 3=tiff, 0=other, -1 = . or .. directories
int getFileExtension(char* filename)
{
	char *extension;
	int numComp;
	
	//check for . and .. directories
	if ((strcmp(filename, "..") == 0) || (strcmp(filename, ".") == 0))
	{
		return -1;
	}
	
	extension = strrchr(filename,'.');
	
	if (extension == NULL)	//file has no extension
	{
		return 0;
	}

	numComp = strcmp(extension,".gif");		//check *.gif
	if (numComp == 0)
	{
		return 1;
	}
	numComp = strcmp(extension, ".png");	//check *.png
	if (numComp == 0)
	{
		return 2;
	}
	numComp = strcmp(extension, ".tiff");	//check *.tiff
	if (numComp == 0)
	{
		return 3;
	}

	return 0;	//otherwise file is of unknown type
}

#endif

