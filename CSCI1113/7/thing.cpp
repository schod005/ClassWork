#include <iostream>
#include <cmath>
using namespace std;
long double fact(double x)
{
	long double total=1;
	while(x>0)
	{
		total*=x--;
		cout<<total<<endl;
	}
}
int main()
{
	double n;
	cin>>n;
	fact(n);
	
}
