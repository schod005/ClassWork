#include <iostream>
using namespace std;

int gcd(int a, int b)
{
	int temp, r, q;
	if (b>a)
	{
		temp=a;
		a=b;
		b=temp;
	}
	
	q=a/b;
	r=a-b*q;
	
	if (r==0)
	return b;
	else
	{
		return gcd(b,r);
	}
	
	
}

int main()
{
	int a,b;
	cout<<"enter two integers: "<<endl;
	cin>>a>>b;
	cout<<"the greatest common divisor is: "<<gcd(a,b)<<endl;
	return 0;
}
