#include <cmath>
#include <iostream>
#include <cstdlib>
using namespace std;

int main()
{
	double x,y,p;
	int size,count;
	
	count =0;
	p=0;
	
	cout << "What's the sample size?" << endl;
	cin >> size;
	
	while (count!=size)
	{
		double rannum1 = static_cast<double>(rand())/RAND_MAX;
		double rannum2 = static_cast<double>(rand())/RAND_MAX;
		x=rannum1*2-1;
		y=rannum2*2-1;
		
		if(x*x+y*y<=1)
		p++;
		
		count++;
	}
	

	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(10);
	cout << "pi is estimated to be: "<<p/size*4<<endl; 
	
	return 0;
}
