#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	double n, guess1, guess2, r;
	cout << "Please enter a positive number: " <<endl;
	cin >> n;
	guess1 = n/2;
	
	while(true)
	{
		
		r=n/guess1;
		guess2=guess1;
		guess1=(guess1+r)/2;
		cout << guess1 << endl;
		if(abs(guess2-guess1)<=0.01*guess1)
		break;
	}
	cout << "The square root is about "<<r<<endl;
	cout << "The square root is actually "<<sqrt(n)<<endl;
	return 0;
}
