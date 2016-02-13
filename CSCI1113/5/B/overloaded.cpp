#include <iostream>
using namespace std;

double max(double x, double y)
{
	if (x>=y)
	return x;
	else 
	return y;
}


double max(double x, double y, double z)
{
	
	if(x>=y && x>=z)
	return x;
	else if(y>=x && y>=z)
	return y;	
	else if(z>=y && z>=x)
	return z;	
	
}


int main()
{
	double x,y,z;
	int number;

	cout << "How many numbers? 2 or 3" << endl;
	cin >> number;
	
	if (number==2)
	{
		cout << "Enter two numbers." << endl;
		cin >>x>>y;
		cout << "The maximum is " << max(x,y)<<endl;
	}
	else if (number==3)
	{
		cout << "Enter three numbers." << endl;
		cin >>x>>y>>z;
		cout << "The maximum is " << max(x,y,z)<<endl;
	}
	return 0;
}
