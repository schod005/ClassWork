#include <iostream>
using namespace std;

long int fact(int n)
{
	if (n==0 || n==1)
	return 1;
	else
	return n*fact(n-1);
	
}

int choose(int n, int k)
{
	return fact(n)/(fact(k)*fact(n-k));
}

int main()
{
	for(int i=1;i<=12;i++)
	cout<<choose(12,i)<<endl;
	
	return 0;
}
