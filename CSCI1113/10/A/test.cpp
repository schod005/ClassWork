#include <iostream>
using namespace std;
#include "Complex.h"



int main()
{
	
	double r,i;
	cout<<"Input the real and imag part of a:"<<endl;
	cin>>r>>i;
	
	Complex *a = new Complex(r,i);
	
	cout<<*a<<endl;
	
	cout<<"The real part is :"<<a->getReal()<<", and the imaginary part is :"<<a->getImag()<<endl;
	
	return 0;
	
	
	
	
}
