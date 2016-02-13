#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <fcntl.h>
#include <time.h>
#include <ftw.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <dirent.h>

//to hold the file info for each file
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

typedef struct Seach_Arg
{
	char *dir;
	char *extension;
}Search_Arg;

//node for linked list of currently running threads
typedef struct ThreadNode
{
	pthread_t Thread;
	struct ThreadNode* NextNode;
}ThreadNode;


//function declarations
void thread_creator(char *dir);
void *showimagesV1(void *arg);
void *showimagesV2(void *arg);
void *image_search(void *dir);
char *getFileExtension(char *filename);
void getFileInfo(char *fileName);
void thread_joiner();
void thread_creator_image_search(char *dir);

void timer_handler(int signum);

//global variables
int count = 0;	//total number of files
int dirCount = 0; //total number of directories
char* version = "v2";	//set this from parsing command-line arguments
ThreadNode *ThreadHead = NULL, *ThreadTail = NULL;	//linked list of active thread nodes
pthread_mutex_t CountMutex;
pthread_mutex_t dirCountMutex;
pthread_mutex_t ThreadListMutex;	//mutex lock for adding to thread list
pthread_mutex_t FilePrinting;	//mutex lock for writing to html
FILE *htmlFile;	//html file



int main()
{
	//initialize log timer
	struct sigaction action;
	struct itimerval timer;
	memset(&action, 0, sizeof(action));
	action.sa_handler = &timer_handler;
	sigaction(SIGVTALRM, &action, NULL);
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 100000;
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 100000;
	setitimer(ITIMER_VIRTUAL, &timer, NULL);
	
	//initialize mutexes (is the plural mutecies?)
	pthread_mutex_init(&ThreadListMutex, NULL);
	pthread_mutex_init(&FilePrinting, NULL);
	pthread_mutex_init(&CountMutex,NULL);
	pthread_mutex_init(&dirCountMutex,NULL);
	
	//create an initialize html file
	htmlFile = fopen("./catalog.html","w");
	fprintf(htmlFile, "<html>\n\t<head>\n\t\t<title>My Image Manager</title>\n\t</head>\n<body>\n");
	fflush(htmlFile);
	
	//replace with directory to scan
	char *dir = "./dir";
	printf("\n\n\n\nBeginning scan of directory: %s\n","/home/schod005/Documents/csci4061/A4/dir");
	thread_creator(dir);	//create thread for input directory
	thread_joiner();
	
	fprintf(htmlFile, "\n</body>\n</html>\n");
	fflush(htmlFile);
	fclose(htmlFile);
	printf("\nScan complete\n");
	printf("Number of images: %d\n",count);
	return 0;
}

void timer_handler(int signum)
{
	printf("TIMER!!!!!!!!!!!!!!\n");
}

//spawns a single thread for a directory and adds it to the thread linked list
void thread_creator(char *dir)
{
	//get control of linked list
	pthread_mutex_lock(&ThreadListMutex);
	
	//create new thread
	pthread_t thread;
	if(strcmp(version,"v1") == 0)
	{
		if (pthread_create(&thread,NULL, &showimagesV1, (void *)dir) != 0)
		{
			printf("Error creating thread\n");
			pthread_mutex_unlock(&ThreadListMutex);
			return;
		}
	}
	else if(strcmp(version,"v2") == 0)
	{
		if (pthread_create(&thread,NULL, &showimagesV2, (void *)dir) != 0)
		{
			printf("Error creating thread\n");
			pthread_mutex_unlock(&ThreadListMutex);
			return;
		}
	}
	printf("     Created thread for: %s\n", dir);
	
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
}

void thread_joiner()
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
		printf("     Joined a thread\n");
		
		//get control of thread list and remove first node
		pthread_mutex_lock(&ThreadListMutex);
		ThreadNode* curNode = ThreadHead;
		ThreadHead = ThreadHead->NextNode;
		free(curNode);
		pthread_mutex_unlock(&ThreadListMutex);
	}
}

//prints out all of the images for the given directory
//spawns new threads for each new directory encountered
void *showimagesV1(void *arg1)
{
	//get argument
	char *dir = (char*)arg1;
	DIR *dp = opendir(dir);
	if(dp == NULL)
	{
		printf("Cannot open directory: %s\n", dir);
		return NULL;
	}

	//scan through everything in current directory
	struct dirent *entry;
	while((entry = readdir(dp)) != NULL)
	{
		//ignore . and .. directories
		if(strcmp(".",entry->d_name) == 0 ||strcmp("..",entry->d_name) == 0)
				{continue;}
		pthread_mutex_lock(&dirCountMutex);
		dirCount++;
		pthread_mutex_unlock(&dirCountMutex);
		//get full file name (with path) of current file
		char curName[strlen(dir) + strlen(entry->d_name) + 3];
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
		else if(getFileExtension(entry->d_name) != NULL)	//file is not a directory, check extension
		{
			//get information about file
			pthread_mutex_lock(&FilePrinting);
			getFileInfo(curName);
			pthread_mutex_unlock(&FilePrinting);
			//printf("%s\n",curName);
			pthread_mutex_lock(&CountMutex);
			count++;
			pthread_mutex_unlock(&CountMutex);
		}
	}
	closedir(dp);	//close directory
	return NULL;
}

void *showimagesV2(void *arg1)
{
	//get argument
	char *dir = (char*)arg1;
	DIR *dp = opendir(dir);
	if(dp == NULL)
	{
		printf("Cannot open directory: %s\n", dir);
		return NULL;
	}

	thread_creator_image_search(dir); //create threads to search for images

	//scan through everything in current directory
	struct dirent *entry;
	while((entry = readdir(dp)) != NULL)
	{
		//ignore . and .. directories
		if(strcmp(".",entry->d_name) == 0 ||strcmp("..",entry->d_name) == 0)
				{continue;}
		pthread_mutex_lock(&dirCountMutex);
		dirCount++;
		pthread_mutex_unlock(&dirCountMutex);
		//get full file name (with path) of current file
		char curName[strlen(dir) + strlen(entry->d_name) + 3];
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
	return NULL;
}

void thread_creator_image_search(char *dir)
{
	//get control of linked list
	pthread_mutex_lock(&ThreadListMutex);
	
	//create new thread
	pthread_t thread[4];
	Search_Arg *bmp = (Search_Arg *)malloc(sizeof(Search_Arg));
	Search_Arg *gif = (Search_Arg *)malloc(sizeof(Search_Arg));
	Search_Arg *png = (Search_Arg *)malloc(sizeof(Search_Arg));
	Search_Arg *jpg = (Search_Arg *)malloc(sizeof(Search_Arg));
	bmp->dir = dir;
	bmp->extension = ".bmp";
	gif->dir = dir;
	gif->extension = ".gif";
	png->dir = dir;
	png->extension = ".png";
	jpg->dir = dir;
	jpg->extension = ".jpg";
	
	if (pthread_create(&thread[0],NULL, &image_search, (void *)bmp) != 0)
	{
		printf("Error creating thread\n");
		pthread_mutex_unlock(&ThreadListMutex);
		return;
	}
	if (pthread_create(&thread[1],NULL, &image_search, (void *)gif) != 0)
	{
		printf("Error creating thread\n");
		pthread_mutex_unlock(&ThreadListMutex);
		return;
	}
	if (pthread_create(&thread[2],NULL, &image_search, (void *)png) != 0)
	{
		printf("Error creating thread\n");
		pthread_mutex_unlock(&ThreadListMutex);
		return;
	}
	if (pthread_create(&thread[3],NULL, &image_search, (void *)jpg) != 0)
	{
		printf("Error creating thread\n");
		pthread_mutex_unlock(&ThreadListMutex);
		return;
	}
	printf("     Created thread for: %s\n", dir);
	
	//create new thread node
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

void *image_search(void *arg)
{
	Search_Arg *arg1 = (Search_Arg *)arg;
	char *dir = arg1->dir;
	char *extension = arg1->extension;
	DIR *dp = opendir(dir);
	if(dp == NULL)
	{
		printf("Cannot open directory: %s\n", dir);
		return NULL;
	}
	
	//scan through everything in current directory
	struct dirent *entry;
	while((entry = readdir(dp)) != NULL)
	{
		//ignore . and .. directories
		if(strcmp(".",entry->d_name) == 0 ||strcmp("..",entry->d_name) == 0)
				{continue;}
		char curName[strlen(dir) + strlen(entry->d_name) + 3];
		strcpy(curName, dir);
		strcat(curName, "/");
		strcat(curName, entry->d_name);
		//see if the entry is a directory by attempting to open it
		DIR *dp2 = opendir(curName);
		if(dp2 != NULL); // if directory, do nothing
		else if(getFileExtension(entry->d_name) == extension)	//file is not a directory, check extension
		{
			//get information about file
			pthread_mutex_lock(&FilePrinting);
			getFileInfo(curName);
			pthread_mutex_unlock(&FilePrinting);
			//printf("%s\n",curName);
			pthread_mutex_lock(&CountMutex);
			count++;
			pthread_mutex_unlock(&CountMutex);
		}
	}
	closedir(dp);	//close directory
	return NULL;
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
	fflush(htmlFile);
	free(info);
	free(fileStats);
}

//check to see if file is an image
char *getFileExtension(char *filename)
{
	char *extension;
	int numComp;
	extension = strrchr(filename,'.');
	if (extension == NULL)
	{
		return NULL;	//file has no extension, can't be an image
	}

	numComp = strncmp(extension,".bmp",4);	//check *.bmp

	//gets rid of . and .. directories in folder
	if (numComp < 0){
		return NULL;
	}

	if (numComp == 0){
		return ".bmp";
	}
	else {
		numComp = strncmp(extension,".gif",4);	//check *.gif
		if (numComp == 0){
			return ".gif";
		}
		else {
			numComp = strncmp(extension,".png",4);	//check *.png
			if (numComp == 0){
				return ".png";
			}
			else {
				numComp = strncmp(extension,".jpg",4);	//check *.jpg
				if (numComp == 0){
					return ".jpg";
				}
			}
		}
	}
	return NULL;	//otherwise file is of unknown type
}
