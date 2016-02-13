#include <iostream>
using namespace std;
#include "poly.h"


int main()
{
	/*
	double co[20]={0};
	cout<<"Enter the coefficients, starting from the lowest power: "<<endl;
	
	for(int i=0;i<10;i++)
	cin>>co[9-i];
	Poly x(co,20);
	cout<<x.degree()<<endl;
	cout<<x<<endl;
	
	*/
	double co1[20]={0};
	double co2[20]={0};
	co1[0]=-2; co1[1]=1;
	co2[0]=2; co2[1]=1;
	
	Poly f(co1,20);
	Poly g(co2,20);
	
	cout<<"f(x) = "<<f<<endl;
	cout<<"g(x) = "<<g<<endl;
	Poly a,b,c,d,e,h;
	a=f+g;
	b=f-g;
	c=f*g;
	d=f+2;
	e=f-2;
	h=f*2;
	cout<<"f(x) + g(x) = "<<a<<endl;
	cout<<"f(x) - g(x) = "<<b<<endl;
	cout<<"f(x) * g(x) = "<<c<<endl;
	cout<<"f(x) + 2 = "<<d<<endl;
	cout<<"f(x) - 2 = "<<e<<endl;
	cout<<"f(x) * 2 = "<<h<<endl;
	
	

	
	
	return 0;
	
	
}
