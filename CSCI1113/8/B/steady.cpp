#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void display(double temp[][20])
{
	for (int i=0;i<20;i++)
	{
		for (int j=0;j<20;j++)
		cout<<temp[i][j]<<"\t";
	cout<<endl<<endl;
	}
}


int main()
{
	ofstream temp1;
	temp1.open("temp.dat");
	
	double temp[20][20], old[20][20];
	double top, bottom, left, right, interior;
	int foo=0;
	bool steady=false;
	cout<<"Please enter the top, bottom, left, right, and initial interior temperature: "<<endl;
	cin>>top>>bottom>>left>>right>>interior;
	for (int i=1;i<19;i++)
	{
		for (int j=1;j<19;j++)
		old[i][j]=interior;
	}
	for (int i=0;i<20;i++)
		old[0][i]=top;
	for (int i=0;i<20;i++)
		old[19][i]=bottom;
	for (int i=1;i<19;i++)
		old[i][0]=left;
	for (int i=1;i<19;i++)
		old[i][19]=right;		

		for (int i=0;i<20;i++)
		{
			for (int j=0;j<20;j++)
			temp[i][j]=old[i][j];
		}

	
	cout<<endl<<endl<<"The initial state is:"<<endl<<endl;
		
	display(old);
	
	cout<<"The final state is:"<<endl<<endl<<endl;


	while (foo<324)
	{
		foo=0;
		for (int i=1;i<19;i++)
		{
			for (int j=1;j<19;j++)
			temp[i][j]=0.25*(old[i+1][j]+old[i-1][j]+old[i][j+1]+old[i][j-1]);
		}
	
		for (int i=1;i<19;i++)
		{
			for (int j=1;j<19;j++)
				{
				if (abs(temp[i][j]-old[i][j])<0.0001)
					{
						foo++;
					}
				}
		}					
	
		for (int i=1;i<19;i++)
		{
			for (int j=1;j<19;j++)
			old[i][j]=temp[i][j];
		}
	cout<<foo<<endl;

	}

	display(temp);
	cout<<foo<<endl;
	for (int i=0;i<20;i++)
	{
		for (int j=0;j<20;j++)
			temp1<<temp[i][j]<<"\t";
		temp1<<endl;
	}
	temp1.close();
	return 0;
}
