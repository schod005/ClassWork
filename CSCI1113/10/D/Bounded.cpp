#include <iostream>
using namespace std;
#include "poly.h"
#include "Complex.h"


int main()
{

	double co[20]={0}, co2[20]={0};
	cout<<"Enter the coefficients of f(x): "<<endl;

	for(int i=0;i<3;i++)
	cin>>co[i];
	Poly f(co,20);

	cout<<"Enter the coefficients of g(x): "<<endl;
	for(int i=0;i<3;i++)
	cin>>co[i];
	Poly g(co,20);
	cout<<"f(x)= "<<f<<endl<<"g(x)= "<<g<<endl;
	
    Poly h=f-g;
    Complex c1,c2;
    h.roots(c1,c2);
    Poly i=h.integral();
    cout<<"The integral of f(x)-g(x) is: "<<i<<endl;
    cout<<"The area between f(x) and g(x) is: "<<i.evaluate(c1.getReal())-i.evaluate(c2.getReal())<<endl;
   


	return 0;


}
