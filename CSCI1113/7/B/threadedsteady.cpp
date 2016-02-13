#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <pthread.h>
using namespace std;

double temp[500][500], old[500][500];

void display(double temp[][500]);

void *updatetoplefttemps(void* A)
{
			for (int i=1;i<249;i++)
		{
			for (int j=1;j<249;j++)
			temp[i][j]=0.25*(old[i+1][j]+old[i-1][j]+old[i][j+1]+old[i][j-1]);
		}
}

void *updatebottomlefttemps(void* B)
{
			for (int i=1;i<249;i++)
		{
			for (int j=249;j<499;j++)
			temp[i][j]=0.25*(old[i+1][j]+old[i-1][j]+old[i][j+1]+old[i][j-1]);
		}
}

void *updatetoprighttemps(void* B)
{
			for (int i=249;i<499;i++)
		{
			for (int j=1;j<249;j++)
			temp[i][j]=0.25*(old[i+1][j]+old[i-1][j]+old[i][j+1]+old[i][j-1]);
		}
}

void *updatebottomrighttemps(void* B)
{
			for (int i=249;i<499;i++)
		{
			for (int j=249;j<499;j++)
			temp[i][j]=0.25*(old[i+1][j]+old[i-1][j]+old[i][j+1]+old[i][j-1]);
		}
}



int main()
{
	ofstream temp1;
	temp1.open("temp.dat");
	pthread_t threads[4];
	void * Alpha;
	double top, bottom, left, right, interior;
	int foo=0;
	cout<<"Please enter the top, bottom, left, right, and initial interior temperature: "<<endl;
	cin>>top>>bottom>>left>>right>>interior;
	for (int i=1;i<499;i++)
	{
		for (int j=1;j<499;j++)
		old[i][j]=interior;
	}
	for (int i=0;i<500;i++)
		old[0][i]=top;
	for (int i=0;i<500;i++)
		old[499][i]=bottom;
	for (int i=1;i<499;i++)
		old[i][0]=left;
	for (int i=1;i<499;i++)
		old[i][499]=right;		

		for (int i=0;i<500;i++)
		{
			for (int j=0;j<500;j++)
			temp[i][j]=old[i][j];
		}

	
	cout<<endl<<endl<<"The initial state is:"<<endl<<endl;
		
	//display(old);
	
	cout<<"The final state is:"<<endl<<endl<<endl;


	while (foo<248003)
	{
		foo=0;
		
		
		pthread_create(&threads[0], NULL, updatetoplefttemps, Alpha);
		pthread_create(&threads[1], NULL, updatebottomlefttemps, Alpha);
		pthread_create(&threads[2], NULL, updatetoprighttemps, Alpha);
		pthread_create(&threads[3], NULL, updatebottomrighttemps, Alpha);
		pthread_join(threads[0],NULL);
		pthread_join(threads[1],NULL);
		pthread_join(threads[2],NULL);
		pthread_join(threads[3],NULL);
		//pthread_exit(NULL);
	/*	for (int i=99;i<100;i++)
		{
			for (int j=1;j<199;j++)
			temp[i][j]=0.25*(old[i+1][j]+old[i-1][j]+old[i][j+1]+old[i][j-1]);
		}
		
		
		for (int i=1;i<199;i++)
		{
			for (int j=99;j<100;j++)
			temp[i][j]=0.25*(old[i+1][j]+old[i-1][j]+old[i][j+1]+old[i][j-1]);
		}
		*/
		for (int i=1;i<499;i++)
		{
			for (int j=1;j<499;j++)
				{
				if (abs(temp[i][j]-old[i][j])<0.0001)
					{
						foo++;
					}
				}
		}					
	
	
		for (int i=1;i<499;i++)
		{
			for (int j=1;j<499;j++)
			old[i][j]=temp[i][j];
		}
	cout<<foo<<endl;

	}

	//display(temp);
	cout<<foo<<endl;
	for (int i=0;i<500;i++)
	{
		for (int j=0;j<500;j++)
			temp1<<temp[i][j]<<"\t";
		temp1<<endl;
	}
	temp1.close();
	return 0;
}

void display(double temp[][500])
{
	for (int i=0;i<500;i++)
	{
		for (int j=0;j<500;j++)
		cout<<temp[i][j]<<"\t";
	cout<<endl<<endl;
	}
}
