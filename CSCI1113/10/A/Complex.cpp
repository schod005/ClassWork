#include <iostream>
#include <cmath>
using namespace std;
#include "Complex.h"



Complex::Complex()
{
	real=0;
	imag=0;
}

Complex::Complex(double a,double b)
{
	real=a;
	imag=b;
}

ostream & operator <<(ostream &b, Complex &a)
{
	char s('+');
	if (a.imag<0)
	{
		s='-';
		cout<<a.real<<" "<<s<<" "<<abs(a.imag)<<"i"<<endl;
	}
	if (a.imag==0)
	cout<<a.real<<endl;
	if (a.imag>0)
	cout<<a.real<<" "<<s<<" "<<abs(a.imag)<<"i"<<endl;
	return b;
}

double Complex::getReal()
{
	return real;
}

double Complex::getImag()
{
	return imag;
}
