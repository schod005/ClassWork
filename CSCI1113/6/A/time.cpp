#include <iostream>

using namespace std;


void addMinutes(int &hr, int &min, int add)
{
	hr=hr+(min+add)/60;
	min=(min+add)%60;
	hr=hr%24;
}

int main()
{
	int hr, min, add;
	char junk;
	cout<<"Please enter the time, in the form of hrs:min :"<<endl;
	cin>>hr>>junk>>min;
	cout<<"How many minutes to add?"<<endl;
	cin>>add;
	addMinutes(hr, min, add);
	cout<<"The updated time is "<<hr<<junk<<min<<endl;

	
	return 0;
}
