/**
 * Information
 * CSci 4061 Spring 2015 Assignment 3
 * Name1=Henry Grittner
 * Name2=David Schoder
 * StudentID1=4560922
 * StudentID2=4552990
 * CSELabs machine: KH4250-20
 * Commentary:
 * This code tests the functionality of our in-memory filesystem by
 * witing all .jpg files from a specified input directory.  After 
 * being written into the filesystem, the .jpg files read out of the 
 * filesystem and written to a specified output directory in the hard
 * disk.  Thumbnails of the .jpg files and an html file linking them
 * are created.  All accesses to the filesystem are logged and output to 
 * a specified log file.  The total number of filesystem accesses is 
 * output at the end of the program.  
 * 
 * As the program is running, it will output the current process being
 * completed.
 * 
 * Usage:
 * 		./test input_directory output_directory log_filename
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
#include "mini_filesystem.h"
#include "testfuncs.h"

//variables
char **Files, **Filenames;
int numFiles = 0;
//int fileNumber = 0;
char *input_dir, *output_dir, *log_filename;	//directories

int main(int argc, char *argv[])
{

    //parse command line arguments
	if (getArgs(argc,argv) == 1)
	{
		return 1;
	}
	
	printf("\nStarting...\n");
	
	printf("\nImage files: ");
	//get all jpg files in input_dir
	ftw(input_dir, fileNumGet, 1);
	Files = (char **)malloc(numFiles*sizeof(char *));
	ftw(input_dir, fileListGet, 1);
	fileNamesGet();
	printf("%d found\n", numFiles);
	
	int j;
	for(j = 0; j < numFiles; j++)
		{printf("    %s\n",Files[j]);}
    
    //initialize filesystem
    printf("\nInitializing filesystem\n");
    int init = Initialize_Filesystem(log_filename);
    if (init != 0)
    {
        printf("Could not initialize filesystem\n");
        return 1;
    }
    
    //read image files into filesystem
    FILE *inputImage;
    printf("\nReading images into filesystem:\n");
    for (j=0; j<numFiles; j++)
    {
        inputImage = fopen(Files[j], "r");
        if (inputImage == NULL) {
            printf("    Cannot open file: %s\n", Files[j]);
            free(Filenames[j]);
            Filenames[j] = NULL;
            continue;
        }
        printf("    %s\n",Files[j]);
        
        //get size of image
        fseek(inputImage, 0L, SEEK_END);
        int size = ftell(inputImage);
        fseek(inputImage, 0L, SEEK_SET);
        
        //create array to hold image file bytes
        char* A = (char*) malloc(sizeof(char)*size);
        
        //read image file into character array
        int i = 0;
        int ch;
        while( (ch = fgetc(inputImage)) != EOF )
        {
            A[i] = ch;
            i++;
        }
        fclose(inputImage);
        
        //create image file with name of file
        char* filename = Filenames[j];
        int create = Create_File(filename);
        if (create == -1)
        {
            printf("        Could not create file: %s\n", filename);
            free(Filenames[j]);
            Filenames[j] = NULL;
            continue;
        }
        printf("        Created file: %s\n", filename);
    
        //open file and write in image data
        int curFile = Open_File(filename);
        int write = Write_File(curFile, 0, A, size);
        if (write != size)
        {
            printf("        Could not write image data\n");
            free(Filenames[j]);
            Filenames[j] = NULL;
            continue;
        }
        Close_file(curFile);
        printf("        Wrote file: %s\n", filename);
        free(A);
    }
    
    fcloseall();
    
    //read image files out of filesystem
    FILE *outputImage;
    printf("\nReading images out of filesystem:\n");
    for (j=0; j<numFiles; j++)
    {
        if (Filenames[j] == NULL)
        {
            continue;
        }
        
        char* filename = Filenames[j];
        int filenameLength = strlen(output_dir);
        filenameLength += strlen(filename);
        
        char outputFilename[filenameLength + 6];
        strcpy(outputFilename, output_dir);
        strcat(outputFilename, "/");
        strcat(outputFilename, filename);
        strcat(outputFilename, ".jpg");
        
        int curFile = Open_File(filename);
        if (curFile == -1)
        {
            printf("    Could not open file: %s\n", filename);
            continue;
        }
        printf("    Reading file: %s\n", filename);
        int size = Get_File_Size(curFile);
        
        //create array to hold image file bytes
        char* A = (char*) malloc(sizeof(char)*size);
        
        //read image file into character array
        int read = Read_File(curFile, 0, size, A);
        if (read != size)
        {
            printf("        Could not read image data\n");
            continue;
        }
        Close_file(curFile);
        printf("        Read image data\n");
        
        //open new jpg file to copy image data into
        outputImage = fopen(outputFilename, "w");
        if (outputImage == NULL) {
            printf("        Unable to open file: %s\n", outputFilename);
            continue;
        }
    
        //copy image data into new jpg file
        int i = 0;
        while(i<size)
        {
            fputc(A[i], outputImage);
            i++;
        }
        fclose(outputImage);
        printf("        Copied image into file: %s\n", outputFilename);
        
        free(A);
    }
    fcloseall();
    
    printf("\nCreating thumbnail files and HTML file...\n");
    createThumbs_HTML();
    
    printf("\nFinal Count: %d\n", Count);
    printf("\nDone!\n");
}











