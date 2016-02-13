#include <iostream>
#include <cstdlib>
#include <time.h>
#include "resistor.h"
using namespace std;




resistor::resistor(double x, double y)
{
	double a,b;

	a=rand();
	b=2*a/RAND_MAX-1;
	n_resistance=x;
	tolerance=y;
	actual_r=(x+b*x*y/100);
}


