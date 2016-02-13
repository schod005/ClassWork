/**
 * Information
 * CSci 4061 Spring 2015 Assignment 4
 * Name1=Henry Grittner
 * Name2=David Schoder
 * StudentID1=4560922
 * StudentID2=4552990
 * CSELabs machine: KH4250-20
 * Commentary:
 * This code uses multiple threads to search through a directory tree
 * and find all of the valid jpg, png, gif, and bmp files. The program
 * also finds information about the image (type, size, etc.) and then
 * creates an html file with the information and links it back to
 * the image files. This program can run in two different modes. The
 * first mode creates a single thread for each directory in the tree
 * that finds the image files. The second mode creates five threads
 * for each directory, one that spawns more threads in subdirectories
 * and four that search for each of the different image types.
 * Information about the program is logged to two different files as
 * the program runs.
 * 
 * As the program is running, it will log information about the
 * management of threads. It also logs information about how many
 * files the search has found as of that moment.
 * 
 * Usage:
 * 		./image_manager [version] ~/[input_dir] ./[output_dir]
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <pthread.h>
#include <dirent.h>
#include "miscfuncs.h"
#include "threadfuncs.h"

//external variables
extern int numBMP;
extern int numPNG;
extern int numGIF;
extern int numJPG;

//declare functions
int getArgs(int argc, char *argv[]);

//global variables
pthread_mutex_t fileCountMutex; //mutex for incrementing file count
pthread_mutex_t dirCountMutex; //mutex for incrementing dir count
pthread_mutex_t ThreadListMutex; //mutex for adding to thread list
pthread_mutex_t htmlMutex; //mutex for writing to html
FILE *htmlFile;	//catalog.html
FILE *LogFile;	//catalog.log
FILE *outputFile; //output.log
char* version = "v1";	//reset from parsing command-line arguments
int fileCount = 0;	//total number of files
int dirCount = 0; //total number of directories
int threadCount = 0;	//total number of threads created
int StopTime = 0;
char *input_dir, *output_dir;	//directories


int main(int argc, char *argv[])
{
	//get arguments
	if(getArgs(argc,argv) == 1)
		{return 1;}
	
	printf("\nBeginning program...\n");
	
	//create output.log and return if error
	char output[strlen(output_dir) + 12];
	strcpy(output, output_dir);
	strcat(output, "/output.log");
	outputFile = fopen(output,"a");
	if (outputFile == NULL)
	{
		printf("ERROR: could not open log file: %s\n", output);
		return 1;
	}
	fprintf(outputFile, "\n------------------------------------------------\n\n");
	fprintf(outputFile, "Beginning program...\nVersion: %s\n\n", version);
	
	//initialize catalog.log file and timer
	char log[strlen(output_dir) + 13];
	strcpy(log, output_dir);
	strcat(log, "/catalog.log");
	LogFile = fopen(log,"a");
	if (outputFile == NULL)
	{
		printf("ERROR: could not open log file: %s\n", log);
		return 1;
	}
	fprintf(LogFile, "\n------------------------------------------------\n\n");
	fprintf(LogFile,"Log for variant %s:\n\n", version);
	struct sigaction action;
	struct itimerval timer;
	memset(&action, 0, sizeof(action));
	action.sa_handler = &timer_handler;
	sigaction(SIGALRM, &action, NULL); //set up signal handler
	timer.it_value.tv_sec = 0;
	timer.it_value.tv_usec = 1000;		//timer goes off every 1 ms
	timer.it_interval.tv_sec = 0;
	timer.it_interval.tv_usec = 1000;
	setitimer(ITIMER_REAL, &timer, NULL);
	
	//initialize mutexes
	pthread_mutex_init(&ThreadListMutex, NULL);
	pthread_mutex_init(&htmlMutex, NULL);
	pthread_mutex_init(&fileCountMutex,NULL);
	pthread_mutex_init(&dirCountMutex,NULL);
	
	//create and initialize html file
	char htmlFileName[strlen(output_dir) + 14];
	strcpy(htmlFileName, output_dir);
	strcat(htmlFileName, "/catalog.html");
	htmlFile = fopen(htmlFileName,"w");
	fprintf(htmlFile, "<html>\n\t<head>\n\t\t<title>My Image Manager</title>\n\t</head>\n<body>\n");
	fflush(htmlFile);
	
	//get starting times and create threads in input_directory
	fprintf(outputFile,"Beginning scan of directory: %s\n",input_dir);
	time_t startTime = time(NULL);
	struct timeval timerTime;
	gettimeofday(&timerTime, NULL);
	long int TotalTime = timerTime.tv_usec;
	thread_creator(input_dir);	//create thread for input directory
	
	//join threads until search is done
	thread_joiner();
	
	//get final times for total run time
	gettimeofday(&timerTime, NULL);
	TotalTime = (long int)timerTime.tv_usec - TotalTime;
	StopTime = 1;		//stop timing threads
	
	//finish html file
	fprintf(htmlFile, "\n</body>\n</html>\n");
	fflush(htmlFile);
	fclose(htmlFile);
	
	//finish updating output.log
	fprintf(outputFile,"\nScan complete\n");
	fprintf(outputFile,"Number of images: %d\n",fileCount);
	fprintf(outputFile,"Number of directories: %d\n",dirCount);
	fprintf(outputFile,"Number of threads: %d\n",threadCount);
	
	//finish updating catalog.log file
	fprintf(LogFile,"\nProgram Initiation: %s\n", asctime(localtime(&startTime)));
	fprintf(LogFile,"Number of JPG files: %d\n", numJPG);
	fprintf(LogFile,"Number of BMP files: %d\n", numBMP);
	fprintf(LogFile,"Number of PNG files: %d\n", numPNG);
	fprintf(LogFile,"Number of GIF files: %d\n", numGIF);
	
	fprintf(LogFile,"\nTotal number of valid image files: %d\n", fileCount);
	fprintf(LogFile,"Total number of directories:       %d\n", dirCount);
	fprintf(LogFile,"Total number of threads created:   %d\n", threadCount);
	fprintf(LogFile,"\nTotal time of execution: %f ms\n", (double)TotalTime/1000.0);
	
	fprintf(LogFile,"\nEnd of log\n");
	fflush(LogFile);
	fclose(LogFile);
	
	fprintf(outputFile, "Done!\n");
	fflush(outputFile);
	fclose(outputFile);
	printf("Done!\n\n");
	return 0;
}


//parse input arguments and test for validity
int getArgs(int argc, char *argv[]){
	//check number of args
	if (argc != 4){
		printf("\nusage: ./image_manager [version] ~/[input_dir] ./[output_dir]\n\n");
		return 1;
	}
	else {
		//check value for version
		version = argv[1];
		if ((strcmp(version,"v1") != 0) && (strcmp(version,"v2") != 0)){
			printf("ERROR: invalid argument for version: %s\n",argv[1]);
			printf("    Choose from: v1 v2\n");
			return 1;
		}

		//check that input_dir is valid/readable
		input_dir = argv[2];
		if (strncmp(input_dir, "/", 1) != 0)
			{
				printf("ERROR: Invalid input directory: %s\n", argv[2]);
				printf("Please use path starting with \"~/\"\n");
				return 1;
			}
		if (opendir(input_dir) == NULL)
		{
			perror("ERROR");
			printf("    Invalid input directory: %s\n",argv[2]);
			return 1;
		}

		//check that output_dir is valid/readable
		output_dir = argv[3];
		if (opendir(output_dir) == NULL)
		{
			//if output_dir does not exist, create it
			if (mkdir(argv[3],0777) == -1)
			{
				perror("ERROR");
				printf("    Invalid output directory: %s\n",argv[3]);
				return 1;
			}
		}
		return 0;	//return success
	}
}

