#include <iostream>
using namespace std;

double drag(double v)
{
return .5*1.23*2.5*.2*v*v;	
}

double power(double v)
{
return drag(v)*v;	
}

double hp(double v)
{
	return power(v)/746;
}

int main()
{
	double v, result;
	cout<<"Enter the velocity in m/s: ";
	cin>>v;
	cout<<hp(v)<<" Horse power"<<endl<<power(v)<<" Watts"<<endl;
	return 0;
}
