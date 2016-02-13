#include <iostream>
using namespace std;

long int fact(int n)
{
	if (n==0 || n==1)
	return 1;
	else
	return n*fact(n-1);
	
}


int main()
{
	
	for(int n=0;n<21;n++)
	cout<<fact(n)<<endl;




		return 0;
}
