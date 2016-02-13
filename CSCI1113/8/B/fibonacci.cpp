#include <iostream>
using namespace std;

int fibonacci(int n)
{
		if (n==0)
		return 0;
		if (n==1)
		return 1;
		else
		return fibonacci(n-1)+fibonacci(n-2);
	
}


int main()
{
	for (int i=1; i<=20; ++i)
	cout<<fibonacci(i)<<endl;
	return 0;
}
