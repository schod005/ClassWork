#include <iostream>
using namespace std;
long int pow(int b)
{
	long int e=2;
	for(int t=0;t<b;t++)
	e*=2;
  return e;
}
int main()
{
	int num, x=1;
	cout<<"how high?"<<endl;
	cin>>num;
	
	while (x<num)
	{	
		
	cout<<pow(x)<<endl;
		if ((pow(x)-2)%x==0)
		{
			cout<<x<<endl;
		}
	x++;
	}
	return 0;
}
