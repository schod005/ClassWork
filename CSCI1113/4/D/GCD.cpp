#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int A, B, R, Q, GCD;
	cout<<"Enter two numbers from largest to "<<endl<<"smallest to find the greatest common divisor: "<<endl;
	cin>>A>>R;

	while(R!=0)
	{
		B=R;
		R=A%B;
		Q=(A-R)/B;
		A=B;
		
		GCD=B;
	}
	cout<<"The greatest common divisor is: "<<GCD<<endl;
	return 0;
}
