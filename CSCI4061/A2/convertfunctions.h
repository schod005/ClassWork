/*
CSci 4061 Spring 2015 Assignment 2
Henry Grittner, 4560922
David Schoder, 4552990

This file contains functions that the children processes in the parallel_convert program use to convert images and create the html files.
*/

#include <string.h>
#include "funcs.h"
#include "listfuncs.h"

#ifndef CONVFUNCS_H
#define CONVFUNCS_H


//declare functions
void convert(char **argv, struct FileList *curList, pid_t child_pid);
void getFilePath(char * path, char *file, char *fileLoc);
void convertFileName(char *file, pid_t pid, char *newFilename);
void createHTML(char *filename, char *nextfile, char *outdir);


//Converting
//decides which type of conversion child process should perform
void convert(char **argv, struct FileList *curList, pid_t child_pid)
{
	//get type of image/next image to convert
	int contype = getImageType(child_pid);
	struct Node *node = findNextImage(curList, contype);

	//if there is an image we can convert...
	if(node != NULL){
		char *file = node->data;			//get filename of image to convert
		char *nextfile = node->htmlNext->data;		//get filename of image to connect html file to
		//get lengths of directory/file names
		int fileLength, inDirLength, outDirLength;
		fileLength = strlen(file);
		inDirLength = strlen(argv[3]);
		outDirLength = strlen(argv[2]);

		//get name (with path) of image to convert
		char fileLoc[fileLength + inDirLength + 2];
		getFilePath(argv[3],file,fileLoc);

		//get name (no path) of converted image: <img name>_pid.jpg
		char newFilename[fileLength + 11];
		convertFileName(file, child_pid, newFilename);
		fileLength = strlen(newFilename);

		printf("    Process %d converting '%s' to '%s'\n", child_pid, file, newFilename);

		//create html file for converted image
		createHTML(newFilename, nextfile, argv[2]);

		//get name (with path) of converted image
		char outFile[outDirLength + fileLength + 2];
		getFilePath(argv[2],newFilename,outFile);

		//create parameter list for conversion function
		char *const parmList[] = {"convert","-geometry","200x200", fileLoc, outFile, NULL};
		//run conversion program
		execvp("convert", parmList);
	}
}


//concatenate path name with filename in a new string
void getFilePath(char * path, char *file, char *fileLoc){
	strcpy(fileLoc,path);
	strcat(fileLoc,"/");
	strcat(fileLoc,file);
}


//converts an image filename to *_pid.jpg
void convertFileName(char *file, pid_t pid, char *newFilename){
	char *extension;
	char pidAsString[15];

	//image name without .<ext> at the end
	strcpy(newFilename, file);
	extension = strrchr(newFilename,'.');
	*extension = '\0';

	sprintf(pidAsString,"_%d.jpg",pid);	//string containing _pid.jpg
	strcat(newFilename, pidAsString);	//concatenated name_pid.jpg
}


//creates the html file for the current image
void createHTML(char *filename, char *nextfile, char *outdir)
{
	//get lengths of file names
	int fileLength = strlen(filename);
	int nextLength = strlen(nextfile);
	int outLength = strlen(outdir);

	//create new strings for names
	char htmlfile[fileLength + outLength + 2];
	char source[fileLength + 1];
	char nexthtml[nextLength + 2];
	char meta[nextLength + 55];
	char *extension;
	
	//create name of html file: <path>/<img name>.html
	strcpy(htmlfile,outdir);
	strcat(htmlfile,"/");
	strcat(htmlfile,filename);
	extension = strrchr(htmlfile,'_');
	*extension = '\0';
	strcat(htmlfile,".html");

	//create name of file to link to: <img name>_pid.jpg
	strcpy(source, filename);

	//create name of html file to link to: <img name>.html
	strcpy(nexthtml,nextfile);
	extension = strrchr(nexthtml,'.');
	*extension = '\0';
	strcat(nexthtml,".html");

	//create meta tag: <meta http-equiv="refresh" content="1; url=file:<img name>.html"/>
	sprintf(meta,"<meta http-equiv=\"refresh\" content=\"1; url=file:%s\"/>\n",nexthtml);
	
	//create html file to write to
	FILE *html = fopen(htmlfile,"w+");

	//add in proper html code:
	/*
		<html>
		<head>
		<meta http-equiv="refresh" content="1; url=file:<img name>.html"/>
		<title>Images</title>
		</head>
		<body>
		<img src="<img name>_pid.jpg">
		</body>
		</html>
	*/
	fprintf(html,"<html>\n<head>\n%s<title>Images</title>\n</head>\n<body>\n<img src=\"%s\"/>\n</body>\n</html>\n",meta,source);
	fflush(html);	//make sure file is written to
}

#endif

