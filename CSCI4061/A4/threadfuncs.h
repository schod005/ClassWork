/*
CSci 4061 Spring 2015 Assignment 4
Henry Grittner, 4560922
David Schoder, 4552990
These functions control the program threads and search for images
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <dirent.h>
#include <string.h>

#ifndef THREADFUNCS_H
#define THREADFUNCS_H

//external variables
extern pthread_mutex_t ThreadListMutex;
extern pthread_mutex_t fileCountMutex;
extern pthread_mutex_t dirCountMutex;
extern pthread_mutex_t htmlMutex;
extern char *version;
extern int fileCount;
extern int dirCount;
extern int threadCount;
extern FILE *outputFile;
extern int numBMP;
extern int numPNG;
extern int numGIF;
extern int numJPG;

//declare functions
void thread_creator(char *dir);
void thread_joiner(void);
void thread_creator_image_search(char *dir);
void *showimagesV1(void *arg);
void *showimagesV2(void *arg);
void *image_search(void *dir);

//argument struct for image_search
typedef struct Seach_Arg
{
	char *dir;
	int extension;
}Search_Arg;

//node struct for linked list of running threads
typedef struct ThreadNode
{
	pthread_t Thread;
	struct ThreadNode* NextNode;
}ThreadNode;

//global variables
ThreadNode *ThreadHead = NULL, *ThreadTail = NULL;	//linked list of active thread nodes


//######################################################Funcs


//spawns a single thread for a directory and adds it to the thread linked list
void thread_creator(char *dir)
{
	//get control of linked list
	pthread_mutex_lock(&ThreadListMutex);
	
	//check version and create new thread
	pthread_t thread;
	if(strcmp(version,"v1") == 0)
	{
		if (pthread_create(&thread,NULL, &showimagesV1, (void *)dir) != 0)
		{
			fprintf(outputFile,"Error creating thread\n");
			printf("Error creating thread\n");
			pthread_mutex_unlock(&ThreadListMutex);
			return;
		}
	}
	else if(strcmp(version,"v2") == 0)
	{
		if (pthread_create(&thread,NULL, &showimagesV2, (void *)dir) != 0)
		{
			fprintf(outputFile,"Error creating thread\n");
			printf("Error creating thread\n");
			pthread_mutex_unlock(&ThreadListMutex);
			return;
		}
	}
	fprintf(outputFile,"    Thread 0x%lx: %s\n",(unsigned long int)thread, dir);
	
	//create new thread node
	ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
	newNode->Thread = thread;
	newNode->NextNode = NULL;
	
	//if head of thread list is null, set this thread as the head
	if (ThreadHead == NULL)
	{
		ThreadHead = newNode;	  	//set head node of thread list
		ThreadTail = ThreadHead;	//set tail node of thread list
	}
	else	//add this thread to the end of the list
	{
		ThreadTail->NextNode = newNode; //update end of list
		ThreadTail = newNode;		   	//set tail node of thread list
	}
	
	//release control of the thread list
	pthread_mutex_unlock(&ThreadListMutex);
	
	//update the directory count
	pthread_mutex_lock(&dirCountMutex);	
	dirCount++;
	pthread_mutex_unlock(&dirCountMutex);
}


//join all of the threads in the linked list in order, removing nodes as we go
void thread_joiner(void)
{
	pthread_t curThread;
	while(ThreadHead != NULL)
	{
		//get control of thread list and look at first active thread
		pthread_mutex_lock(&ThreadListMutex);
		curThread = ThreadHead->Thread;
		pthread_mutex_unlock(&ThreadListMutex);
		
		//join thread
		pthread_join(curThread, NULL);
		threadCount++;
		
		//get control of thread list and remove first node
		pthread_mutex_lock(&ThreadListMutex);
		fprintf(outputFile,"    Joined thread: 0x%lx\n", (unsigned long int)curThread);
		ThreadNode* curNode = ThreadHead;
		ThreadHead = ThreadHead->NextNode;
		free(curNode);
		pthread_mutex_unlock(&ThreadListMutex);
	}
}


//create four threads to search each of the file types (for v2)
void thread_creator_image_search(char *dir)
{
	//get control of linked list
	pthread_mutex_lock(&ThreadListMutex);
	
	//create new arguments for each type of image
	pthread_t thread[4];
	Search_Arg *bmp = (Search_Arg *)malloc(sizeof(Search_Arg));
	Search_Arg *gif = (Search_Arg *)malloc(sizeof(Search_Arg));
	Search_Arg *png = (Search_Arg *)malloc(sizeof(Search_Arg));
	Search_Arg *jpg = (Search_Arg *)malloc(sizeof(Search_Arg));
	bmp->dir = dir;
	bmp->extension = 1;
	gif->dir = dir;
	gif->extension = 2;
	jpg->dir = dir;
	jpg->extension = 3;
	png->dir = dir;
	png->extension = 4;
	
	//create new threads for each type of image
	if (pthread_create(&thread[0],NULL, &image_search, (void *)bmp) != 0)
	{
		fprintf(outputFile,"Error creating thread\n");
		printf("Error creating thread\n");
		free(bmp);
		pthread_mutex_unlock(&ThreadListMutex);
		return;
	}
	if (pthread_create(&thread[1],NULL, &image_search, (void *)gif) != 0)
	{
		fprintf(outputFile,"Error creating thread\n");
		printf("Error creating thread\n");
		free(gif);
		pthread_mutex_unlock(&ThreadListMutex);
		return;
	}
	if (pthread_create(&thread[2],NULL, &image_search, (void *)png) != 0)
	{
		fprintf(outputFile,"Error creating thread\n");
		printf("Error creating thread\n");
		free(png);
		pthread_mutex_unlock(&ThreadListMutex);
		return;
	}
	if (pthread_create(&thread[3],NULL, &image_search, (void *)jpg) != 0)
	{
		fprintf(outputFile,"Error creating thread\n");
		printf("Error creating thread\n");
		free(jpg);
		pthread_mutex_unlock(&ThreadListMutex);
		return;
	}
	fprintf(outputFile,"    BMP thread 0x%lx: %s\n",(unsigned long int)thread[0], dir);
	fprintf(outputFile,"    GIF thread 0x%lx: %s\n",(unsigned long int)thread[1], dir);
	fprintf(outputFile,"    PNG thread 0x%lx: %s\n",(unsigned long int)thread[2], dir);
	fprintf(outputFile,"    JPG thread 0x%lx: %s\n",(unsigned long int)thread[3], dir);
	
	//create new thread nodes in list
	int i;
	for(i = 0; i < 4; i++)
	{
		ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
		newNode->Thread = thread[i];
		newNode->NextNode = NULL;
		
		//if head of thread list is null, set this thread as the head
		if (ThreadHead == NULL)
		{
			ThreadHead = newNode;	  	//set head node of thread list
			ThreadTail = ThreadHead;	//set tail node of thread list
		}
		else	//add this thread to the end of the list
		{
			ThreadTail->NextNode = newNode; //update end of list
			ThreadTail = newNode;		   	//set tail node of thread list
		}
	}
	//release control of the thread list
	pthread_mutex_unlock(&ThreadListMutex);
}


//finds all of the images for the given directory (V1)
//spawns new threads for each new directory encountered
void *showimagesV1(void *arg1)
{
	//get argument
	char *dir = (char*)arg1;
	DIR *dp = opendir(dir);
	int extension;
	
	//error checking
	if(dp == NULL)
	{
		fprintf(outputFile,"Cannot open directory: %s\n", dir);
		return NULL;
	}

	//scan through everything in current directory
	struct dirent *entry;
	while((entry = readdir(dp)) != NULL)
	{
		//get extension
		extension = getFileExtension(entry->d_name);
		//ignore . and .. directories
		if((strcmp(".",entry->d_name) == 0) || (strcmp("..",entry->d_name) == 0))
				{continue;}
		//get full file name (with path) of current file
		char curName[strlen(dir) + strlen(entry->d_name) + 2];
		strcpy(curName, dir);
		strcat(curName, "/");
		strcat(curName, entry->d_name);
		
		//see if the entry is a directory by attempting to open it
		DIR *dp2 = opendir(curName);
		if(dp2 != NULL)
		{
			//entry is a directory
			closedir(dp2);		//close directory
			char* curDir = (char*)malloc(strlen(curName) + 1);	//malloc to avoid string deletion
			strcpy(curDir, curName);
			thread_creator(curDir);	//spawn new thread for the directory
		}
		else if(extension != 0)	//file is not a directory, check extension
		{
			//update file counts
			pthread_mutex_lock(&fileCountMutex);
			if(extension == 3)
				{
					numJPG++;
					fileCount++;
				}
			if(extension == 2)
				{
					numGIF++;
					fileCount++;
				}
			if(extension == 1)
				{
					numBMP++;
					fileCount++;
				}
			if(extension == 4)
				{
					numPNG++;
					fileCount++;
				}
			pthread_mutex_unlock(&fileCountMutex);
			
			//get information about file and add to html
			pthread_mutex_lock(&htmlMutex);
			getFileInfo(curName);
			pthread_mutex_unlock(&htmlMutex);
		}
	}
	closedir(dp);	//close directory
	
	//update output.log file to show successful thread execution
	pthread_mutex_lock(&ThreadListMutex);
	fprintf(outputFile,"    Thread 0x%lx exiting after successful execution\n",(unsigned long int)pthread_self());
	pthread_mutex_unlock(&ThreadListMutex);
	return NULL;
}


//finds all of the images for the given directory (V2)
//spawns four new threads to search for each image type
//spawns new threads for each new directory encountered
void *showimagesV2(void *arg1)
{
	//get argument
	char *dir = (char*)arg1;
	DIR *dp = opendir(dir);
	
	//error checking
	if(dp == NULL)
	{
		fprintf(outputFile,"Cannot open directory: %s\n", dir);
		return NULL;
	}

	//create four threads to search for images
	thread_creator_image_search(dir);

	//scan through everything in current directory
	struct dirent *entry;
	while((entry = readdir(dp)) != NULL)
	{
		//ignore . and .. directories
		if((strcmp(".",entry->d_name) == 0) || (strcmp("..",entry->d_name) == 0))
				{continue;}
		//get full file name (with path) of current file
		char curName[strlen(dir) + strlen(entry->d_name) + 2];
		strcpy(curName, dir);
		strcat(curName, "/");
		strcat(curName, entry->d_name);
		
		//see if the entry is a directory by attempting to open it
		DIR *dp2 = opendir(curName);
		if(dp2 != NULL)
		{
			//entry is a directory
			closedir(dp2);		//close directory
			char* curDir = (char*)malloc(strlen(curName) + 1);	//malloc to avoid string deletion
			strcpy(curDir, curName);
			thread_creator(curDir);	//spawn new thread for the directory
		}
	}
	closedir(dp);	//close directory
	
	//update log file to show successful thread execution
	pthread_mutex_lock(&ThreadListMutex);
	fprintf(outputFile,"    Thread 0x%lx exiting after successful execution\n",(unsigned long int)pthread_self());
	pthread_mutex_unlock(&ThreadListMutex);
	return NULL;
}


//used by four image-type threads to search directories
void *image_search(void *arg)
{
	//get parameters
	Search_Arg *arg1 = (Search_Arg *)arg;
	char *dir = arg1->dir;
	int extension = arg1->extension;
	DIR *dp = opendir(dir);
	
	//error checking
	if(dp == NULL)
	{
		fprintf(outputFile,"Cannot open directory: %s\n", dir);
		return NULL;
	}
	
	//scan through everything in current directory
	struct dirent *entry;
	while((entry = readdir(dp)) != NULL)
	{
		//ignore . and .. directories
		if((strcmp(".",entry->d_name) == 0) || (strcmp("..",entry->d_name) == 0))
				{continue;}
		char curName[strlen(dir) + strlen(entry->d_name) + 2];
		strcpy(curName, dir);
		strcat(curName, "/");
		strcat(curName, entry->d_name);

		//check to see if the file is of the correct type
		if(getFileExtension(entry->d_name) == extension)
		{
			//update file counts
			pthread_mutex_lock(&fileCountMutex);
			if(extension == 3)
				{
					numJPG++;
					fileCount++;
				}
			if(extension == 2)
				{
					numGIF++;
					fileCount++;
				}
			if(extension == 1)
				{
					numBMP++;
					fileCount++;
				}
			if(extension == 4)
				{
					numPNG++;
					fileCount++;
				}
			pthread_mutex_unlock(&fileCountMutex);
			
			//get information about file
			pthread_mutex_lock(&htmlMutex);
			getFileInfo(curName);
			pthread_mutex_unlock(&htmlMutex);
		}
	}
	closedir(dp);	//close directory
	free(arg); //free allocated space for argument struct
	
	//update log file to show successful thread execution
	pthread_mutex_lock(&ThreadListMutex);
	fprintf(outputFile,"    Thread 0x%lx exiting after successful execution\n",(unsigned long int)pthread_self());
	pthread_mutex_unlock(&ThreadListMutex);
	return;
}

#endif

