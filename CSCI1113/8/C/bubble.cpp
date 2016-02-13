#include <iostream>

using namespace std;

void swap(int& x,int& y)
{
	int temp;
	temp=x;
	x=y;
	y=temp;
}

void bsort(int array[], int num)
{
	for(int x=0;x<49;x++)
	{
		/*
		if (array[x]>array[x+1])
		swap(array[x],array[x+1]);
		*/
		
		if (array[x]>array[x+1])
		{
			int dog=array[x];
			array[x]=array[x+1];
			array[x+1]=dog;
		}
		
	}
}

int main()
{
	int x=0;
	int cat=0;
	int list[50];
	for(int x=0;x<50;x++)
	{
		list[x]=100-x;
	}
	
	for(int x=0;x<50;x+=5)
	cout<<list[x]<<" "<<list[x+1]<<" "<<list[x+2]<<" "<<list[x+3]<<" "<<list[x+4];
	
	cout<<endl<<endl;
	for(int x=0;x<50;x++)
	bsort(list,50);
	
	for(int x=0;x<50;x+=5)
	cout<<list[x]<<" "<<list[x+1]<<" "<<list[x+2]<<" "<<list[x+3]<<" "<<list[x+4]<<endl;
	
	cout<<endl;
	
}
