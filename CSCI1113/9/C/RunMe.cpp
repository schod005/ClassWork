#include <iostream>
#include <cstdlib>
#include "time.h"
#include "resistor.h"
#include "VoltageDivider.h"

using namespace std;

int main()
{
	srand (time(NULL));
	for(int i=1;i<=10;i++)
	{
		resistor re1(250,5);
		resistor re2(750,5);
			VoltageDivider d(re1,re2);
		cout<<"Divider #"<<i<<": Nominal gain = "<<d.gainnr<<", Actual gain = "<<d.gainr<<endl<<endl;
	}
	return 0;
}
