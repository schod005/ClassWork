#include <iostream>
#include <string>
#include <cmath>
using namespace std;

int exp(int num, int ex)
{
	int result=1;
	while (ex!=0)
	{
		result*=num;
		ex--;
	}
	return result;
}

unsigned int revnum(unsigned int n, unsigned int numdigits)
{
	int result=0;
	while (numdigits!=0)
	{
		result+=(n%10)*(exp(10,--numdigits));
		n/=10;
	}
	return result;
}

int main()
{
	int n, d;
	cout << "Enter a number and the amount of reverse digits: " <<endl;
	cin >> n>> d;
	cout << revnum(n,d)<<endl;
	
	return 0;
}
