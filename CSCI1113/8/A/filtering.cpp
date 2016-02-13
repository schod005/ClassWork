#include <iostream>
using namespace std;

void smooth(double values[], int size)
	{
		for(int x=0;x<size;x++)
		{
			if(x==0)
			values[x]=(values[x]+values[x+1])/2;
			if(1<=x && x<(size-1))
			values[x]=(values[x-1]+values[x+1]+values[x])/3;
			if(x==size-1)
			values[x]=(values[x]+values[x-1])/2;
		}
	}

int main()
{
	double values[123321],size;
	cout<<"Enter the size"<<endl;
	cin>>size;
	cout<<"Enter the array"<<endl;
	for(int x=0;x<size;x++)
		cin>>values[x];
	smooth(values,size);
	for(int x=0;x<size;x++)
		cout<<values[x]<<" ";
	cout<<endl;
	return 0;
	
	
}



