#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream poop;
	int month,day,year, count=0;
	double lowt,hight,meanl,meanh,max=1,min=100;
	char junk;
	string filename;
	cout<<"File location: ";
	cin>>filename;
	poop.open(filename.c_str());
	while(true)
		{
			poop>>month>>junk>>day>>junk>>year>>hight>>lowt;
			if(poop.eof())
				break;
			meanl+=lowt;
			meanh+=hight;
			count++;
			if (hight>=max)
			max=hight;
			if (lowt<=min)
			min=lowt;
		}
	
	cout<<"Number of days on record: "<<count<<endl;
	cout<<"Hightest daily temperature: "<<max<<endl;
	cout<<"Lowest daily temperature: "<<min<<endl;
	cout<<"The average low is: "<<meanl/count<<endl;
	cout<<"The average high is: "<<meanh/count<<endl;
	
	return 0;
}
