#include <iostream>
#include "resistor.h"
using namespace std;


int main()
{
	double r,t;

	cout<<"please enter nominal resistance and % tolerance for"<<endl;
	cin>>r>>t;
	resistor r1(r,t);
	

	cout<<"the actual resistance is "<<r1.actual_r<<endl;
	
	
	return 0;
}
