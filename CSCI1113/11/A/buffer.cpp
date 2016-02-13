#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;


int* generateData(int* &inbuf,int &count)
{
	int ran;
	ran=rand()%10;
	inbuf[count]=ran;
	count++;
	if(count>=10)
	{
		count=0;
		int *temp=inbuf;
		inbuf=new int[10];
		return temp;
	
	}
	else
	return NULL;
}

void processData(int* &outbuf, int &count, int &total)
{
	if (outbuf!=NULL)
	{
		total+=outbuf[count];
		count++;
	}
	if (count==10)
	{
		count=0;
		delete [] outbuf;
		outbuf=NULL;
	}
}

const int BUFSIZE=10; 
const int ITERATIONS=50; 

double getProb()
{
	return rand()/static_cast<double>(RAND_MAX);
}

int main() 
{
	int *fillbuffer = new int[BUFSIZE]; 
	srand(time(0));
	int fillcnt=0; 
	int *processbuffer = NULL; 
	int processcnt=0; 
	int tcount = 0; 
 
	for(int i=0; i<ITERATIONS; i++) 
	{
		int *temp; 
		if(getProb() <= 0.40 ) 
		{
			temp = generateData(fillbuffer,fillcnt); 
			if( temp != NULL ) 
			processbuffer = temp; 
		} 
		if(getProb() <= 0.60) 
			processData(processbuffer,processcnt,tcount); 
		cout << fillcnt << '\t' << processcnt << endl; 
	} 

	cout << "Total value: " << tcount << endl; 
	return 0; 
}
