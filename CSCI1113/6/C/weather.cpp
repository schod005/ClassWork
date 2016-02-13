#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;



int main()
{
	int date,month,year;
	double lowt,hight;
	char j1,as='y';
	
cout.setf(ios::fixed);
cout.setf(ios::showpoint);
cout.precision(1);

ofstream foo;
foo.open("/home/schod005/CSCI1113/6/C/weather.dat",ios::app);
if (foo.fail())
{
	cout<<"file open failed, hahahaha you did it wrong!! XD"<<endl;
	exit(1);
}
while (as=='y')
{

	cin>>month>>j1>>date>>j1>>year>>hight>>lowt;
	foo<<month<<j1<<date<<j1<<year<<" "<<hight<<" "<<lowt<<endl;
	cout<<"more data? y/n"<<endl;
	cin>>as;
	if (as=='n')
	break;
	
}


return 0;

}
