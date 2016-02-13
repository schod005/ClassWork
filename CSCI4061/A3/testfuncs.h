/*
CSci 4061 Spring 2015 Assignment 3
Henry Grittner, 4560922
David Schoder, 4552990
These are functions used by the test program for various purposes
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <ftw.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>


//declare functions
int getArgs(int argc, char *argv[]);
int fileListGet(const char *name, const struct stat *status, int type);
int fileNumGet(const char *name, const struct stat *status, int type);
int fileNamesGet(void);
int createThumbs_HTML(void);


//external variables
extern char **Files, **Filenames;
extern int numFiles;
int fileNumber = 0;
extern char *input_dir, *output_dir, *log_filename;	//directories


//parse input arguments and test for validity
int getArgs(int argc, char *argv[]){
	//check number of args
	if (argc != 4){
		printf("usage: test input_dir output_dir log_file\n");
		return 1;
	}
	else {
		//check that input_dir is valid/readable
		input_dir = argv[1];
		if (access(input_dir, R_OK) == -1){
			perror("ERROR");
			printf("    Invalid input directory: %s\n",argv[2]);
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
		
		//check if log file exists
		log_filename = argv[3];
		if (access(log_filename, F_OK) != -1) //file exists
		{
			if (remove(log_filename) != 0)
			{
				perror("ERROR");
				printf("	Could not delete file: %s\n",argv[3]);
				return 1;
			}
			//create file
			FILE *File = fopen(log_filename,"w");
			if (File == NULL){
				perror("ERROR");
				printf("    Invalid output directory: %s\n",argv[3]);
				return 1;
			}
			fclose(File);
		}
		else //file does not exist
		{
			//create file
			FILE *File = fopen(argv[3],"w");
			if (File == NULL){
				perror("ERROR");
				printf("    Invalid output directory: %s\n",argv[3]);
				return 1;
			}
			fclose(File);
		}
		return 0;	//return success
	}
}


//get the number of .jpg files in the (nested) input directory
    //store value in numFiles global variable
int fileNumGet(const char *name, const struct stat *status, int type) {
	if(type == FTW_F)
	{
		char *extension;
		extension = strrchr(name,'.');
		int isJPG;
		if ( extension == NULL )
		{
			return 1;
		}
		
		isJPG = strncmp(extension, ".jpg",4);
		if (!isJPG)
		{
			numFiles++;
		}
	}
	return 0;
}


//get the names (with paths) of all the .jpg files in the input directory
    //save the names in Files[] global variable
int fileListGet(const char *name, const struct stat *status, int type) {
	
	if(type == FTW_F)
	{
		char *extension;
		extension = strrchr(name,'.');
		int isJPG;
		if ( extension == NULL )
		{
			isJPG = 1;
		}
		else
		{
			isJPG = strncmp(extension, ".jpg",4);
		}
		
		if (!isJPG)
		{
			Files[fileNumber] = malloc(strlen(name) + 1);
			strcpy(Files[fileNumber], name);
			fileNumber++;
		}
	}
	return 0;
}


//get the names of the .jpg files (no paths/extensions)
    //store the names in the Filenames[] global variable
int fileNamesGet(void)
{
    int i;
    Filenames = (char **)malloc(numFiles*sizeof(char *));
    
	for(i = 0; i < numFiles; i++)
	{
        char *filename1, *filename2;
        filename1 = strrchr(Files[i],'/');
        filename2 = strrchr(Files[i],'.');
        int nameLength = filename2 - filename1 - 1;
        if (nameLength > 15)
        {
            nameLength = 15;
        }
        Filenames[i] = (char*)malloc(16);
        strncpy(Filenames[i], (filename1 + 1), nameLength);
        Filenames[i][nameLength] = '\0';
    }
}


//creates the thumbnail images for each image in the output directory and links them to the html file
int createThumbs_HTML(void)
{
    int i;
    int outputLength = strlen(output_dir);
    
    //check if html file exists
    char htmlFile[outputLength + 24];
    strcpy(htmlFile, output_dir);
    strcat(htmlFile, "/filesystem_content.html");
    if (access(htmlFile, F_OK) != -1) //file exists
    {
        if (remove(htmlFile) != 0)
        {
            perror("ERROR");
            printf("	Could not delete html file\n");
            return 1;
        }
    }
    //create html file
    FILE *File = fopen(htmlFile,"w");
    if (File == NULL){
        perror("ERROR");
        printf("    Cannot create HTML file\n");
        return 1;
    }
    
    //start html file
    fprintf(File, "<html>\n<head>\n<title>Filesystem Output</title>\n</head>\n<body>\n");
    
    //loop through all image files
    for (i=0; i<numFiles; i++)
    {
        char* curFile = Filenames[i];
        if (curFile == NULL)
        {
            continue;
        }
        int curLength = strlen(curFile);
        char fileLoc[curLength+outputLength+6];
        char outFile[curLength+outputLength+12];
        
        //get input and thumbs output names
        strcpy(fileLoc, output_dir);
        strcat(fileLoc, "/");
        strcat(fileLoc, curFile);
        strcpy(outFile, fileLoc);
        strcat(fileLoc, ".jpg");
        strcat(outFile, "_thumb.jpg");
        
        //link image to html file
        fprintf(File, "<a href=\"%s.jpg\">\n<img src=\"%s_thumb.jpg\"/>\n</a>\n", curFile, curFile);
        
        //create thumbnail image
        char *const parmList[] = {"convert", fileLoc, "-resize", "200x200",  outFile, NULL};
        
        pid_t child = fork();
        int status;
        if (child == 0)
            {execvp("convert", parmList);}
        else
            {wait(&status);}
    }
    
    //finish up html file
    fprintf(File, "</body>\n</html>\n");
    fclose(File);
}

