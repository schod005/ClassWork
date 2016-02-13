#include <iostream>
#include <fstream>
using namespace std;


int main()
{
	ifstream fin;
	char str[50]={'0'};
	cout<<"Enter your secret message: "<<endl;
	fin.open("public.message");
	fin.getline(str,500);
	
	cout<<str[0];
	for(int x=0;x<500;x++)
		{
			if(str[x-1]==' ')
			cout<<str[x];
		
		}
		cout<<endl;
	return 0;
}
