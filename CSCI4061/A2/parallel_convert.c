/*
Information
CSci 4061 Spring 2015 Assignment 2
Name1=Henry Grittner
Name2=David Schoder
StudentID1=4560922
StudentID2=4552990
Commentary=This program creates children programs that convert images in a directory into *.jpg thumbnails in a different directory. The program also creates html files for each converted image that link together in a cycle. The image conversions are done in parallel with one another.

usage: parallel_convert convert_count output_dir input_dir
*/

//include dependencies
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>

#include "listfuncs.h"
#include "funcs.h"
#include "convertfunctions.h"


//declare functions
int getArgs(int argc, char *argv[]);


//declare global variables
char *input_dir, *output_dir;	//directories
int convert_count;		//convert_count
struct FileList *imageList;	//list of images to be converted


//main function
int main(int argc, char *argv[]){
	if (getArgs(argc, argv)){	//check that args are valid
		return 1;
	}
	printf("Beginning conversion program:\n");
	int status = 0;		//for wait() functions
	int i;			//counter
	pid_t child_pid;	//id for fork()

	//create list of files to convert in input_dir
	imageList = createFileList(input_dir);
	printf("    Found %d files to convert\n", getListLength(imageList));

	printf("    Beginning child creation process\n\n");
	//create convert_count processes right away
	for(i = 0; i < convert_count; i++)
	{
		child_pid = fork();	//create child
		if(child_pid != 0){
			//parent removes file that child will convert
			removeNextFileFromList(imageList, child_pid);
		}
		else{
			//child gets pid and calls convert function
			child_pid = getpid();
			convert(argv, imageList, child_pid);
			return 0;
		}
	}
	//after convert_count children were created, keep waiting
		//for children to finish and creating new children
		//until all images have been converted
	printf("Waiting for children to complete...\n\n");
	while(getListLength(imageList) !=  0)
	{
		wait(&status);		//wait for child
		child_pid = fork();	//create new child
		if(child_pid != 0){
			//parent removes file that child will convert
			removeNextFileFromList(imageList, child_pid);
		}
		else{
			//child gets pid and calls convert function
			child_pid = getpid();
			convert(argv, imageList, child_pid);
			return 0;
		}
		
	}
	wait(&status);	//wait for final child to finish
	printf("\nAll conversions completed\n");

	return 0;	//exit success
}


//parse input arguments and test for validity
int getArgs(int argc, char *argv[]){
	//check number of args
	if (argc != 4){
		printf("usage: parallel_convert convert_count output_dir input_dir\n");
		return 1;
	}
	else {
		//check value for convert_count
		convert_count = atoi(argv[1]);
		if ((convert_count < 1) || (convert_count > 10)){
			printf("ERROR: invalid argument for number of processes: %s\n",argv[1]);
			return 1;
		}

		//check that input_dir is valid/readable
		input_dir = argv[3];
		if (access(input_dir, R_OK) == -1){
			perror("ERROR");
			printf("    Invalid input directory: %s\n",argv[3]);
			return 1;
		}

		//check that output_dir is valid/readable
		output_dir = argv[2];
		if (access(output_dir, R_OK | W_OK) == -1){
			//if output_dir does not exist, create it
			if (mkdir(argv[2],0777) == -1){
				perror("ERROR");
				printf("    Invalid output directory: %s\n",argv[2]);
				return 1;
			}
		}
		return 0;	//return success
	}
}

