#include <iostream>
#include <cmath>
using namespace std;

double det2(double a, double b, double c, double d)
{
	return a*d-b*c;
}

double det3(double a, double b, double c, double d, double e, double f, double g, double h, double i)
{
	return a*(e*i-h*f)-b*(d*i-g*f)+c*(d*h-g*e);
}

int main()
{
	int u;
	double a,b,c,d,e,f,g,h,i;
	cout<<"2x2 matrix (enter 2) or 3x3 matrix (enter 3)"<<endl;
	cin>>u;
	cout<<"Enter the numbers"<<endl;
	if(u==2)
		{
			cin>>a>>b>>c>>d;
			cout<<"The determinant is: "<<det2(a,b,c,d)<<endl;
		}
	else if(u==3)
		{
			cin>>a>>b>>c>>d>>e>>f>>g>>h>>i;
			cout<<"The determinant is: "<<det3(a,b,c,d,e,f,g,h,i)<<endl;
		}
	return 0;
}
