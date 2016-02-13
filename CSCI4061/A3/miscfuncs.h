/*
CSci 4061 Spring 2015 Assignment 3
Henry Grittner, 4560922
David Schoder, 4552990
These are misc. functions used by the filesystem API
*/

/////////////////// Misc. Functions ///////////////////
int copyString(char* dest, char* src, int numBytes);
int concatString(char* dest, char* src, int destStart, int numBytes);
int log_timestamp(FILE *file);

//initialize timestamp values
struct timeval times;
time_t     now;
struct tm  ts;
char       buf[80];

//copies one string into another character by character
    //returns number of bytes copied
int copyString(char* dest, char* src, int numBytes)
{
    int number = numBytes;
    while (number > 0)
    {
        *dest = *src;
        dest++;
        src++;
        number--;
    }
    return numBytes;
}


//copies numBytes from src string onto dest string starting at position destStart
    //returns number of bytes added to dest string
int concatString(char* dest, char* src, int destStart, int numBytes)
{
    int number = numBytes;
    dest += destStart;
    while (number > 0)
    {
        *dest = *src;
        dest++;
        src++;
        number--;
    }
    return numBytes;
}


//logs a timestamp entry in the log file
int log_timestamp(FILE *file)
{
    Count++;
    time(&now);
	gettimeofday(&times,0);
	ts = *localtime(&now);
	strftime(buf, sizeof(buf), "%H:%M:%S", &ts);
	fprintf(file,"%s:%.6d\t\t", buf,(int)(times.tv_usec));
	return 0;
}

