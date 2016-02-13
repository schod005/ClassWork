#include <iostream>
#include <cmath>
#include "Quadratic.h"

using namespace std;

int main()
{
	Quadratic f1;
	f1.GetData();
	f1.ShowData();
	cout<<f1.Value(8)<<endl;
	f1.Roots();
	
	Quadratic f2;
	f2.GetData();
	f2.ShowData();
	cout<<f2.Value(8)<<endl;
	f2.Roots();
	
	return 0;
}
