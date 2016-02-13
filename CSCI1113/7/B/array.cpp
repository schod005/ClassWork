#include <iostream>
using namespace std;

void function(int array[], int arraysize) //function called with 1D array
{
//Do something	
}

void FUNCTION(int ARRAY[][8], int numrows) // rumrows should be passed as 5.
{}

int main()
{
	int array[10];
	
	int numrows=5, numcols=8;
	int ARRAY[5][8];
	
	
	for(int i=0; i<numrows; i++)
		for(int j=0; j<numcols; j++)
			ARRAY[i][j]=0;
	
	
	//calling FUNCTION
	
	FUNCTION(ARRAY,numrows);
	
	for(int i = 0; i<10; i++)
		array[i] = i;
	
	for(int i = 0; i<10; i++)
		cout<<array[i]<<endl;
	
	
	
	return 0;
}
