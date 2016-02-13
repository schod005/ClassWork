#include <iostream>
#include <cmath>
#include "Quadratic.h"

using namespace std;

	
	Quadratic::Quadratic()
	{
		a=0; b=0; c=0;
	}
	
	void Quadratic::GetData()
	{
		double aa,bb,cc;
		cout<<"Please input the coefficients a, b, and c: "<<endl;
		cin>>aa>>bb>>cc;
		a=aa;
		b=bb;
		c=cc;
	}
	
	void Quadratic::ShowData()
	{
		char sa(' '),sb('+'),sc('+');
		if (a<0)
			sa='-';
		if (b<0)
			sb='-';
		if (c<0)
			sc='-';
		cout<<sa<<abs(a)<<"x^2 "<<sb<<" "<<abs(b)<<"x "<<sc<<" "<<abs(c)<<endl;		
	}
	
	double Quadratic::Value (double x)
	{
		
		return a*x*x+b*x+c;
	}
	
	void Quadratic::Roots()
	{
		if (b*b-4*a*c<0)
			cout<<"No real roots"<<endl;
		if (b*b-4*a*c==0)
			cout<<"One double root : x = "<<-b/2/a<<endl;
		if (b*b-4*a*c>0)
			cout<<"Two real roots: x1 = "<<(-b+sqrt(b*b-4*a*c))/2/a<<" , x2 = "<<(-b-sqrt(b*b-4*a*c))/2/a<<endl;
	}
	
