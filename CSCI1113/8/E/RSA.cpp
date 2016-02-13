#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

int encode(int a, int e, int n)
{
	return (static_cast<int>(pow(static_cast<double>(a),e))%n);
}

int char_to_number(char x)
{ 
		
		if (x=='A')
		return 1;
		if (x=='B')
		return 2;
		if (x=='C')
		return 3;
		if (x=='D')
		return 4;
		if (x=='E')
		return 5;
		if (x=='F')
		return 6;
		if (x=='G')
		return 7;
		if (x=='H')
		return 8;
		if (x=='I')
		return 9;
		if (x=='J')
		return 10;
		if (x=='K')
		return 11;
		if (x=='L')
		return 12;
		if (x=='M')
		return 13;
		if (x=='N')
		return 14;
		if (x=='O')
		return 15;
		if (x=='P')
		return 16;
		if (x=='Q')
		return 17;
		if (x=='R')
		return 18;
		if (x=='S')
		return 19;
		if (x=='T')
		return 20;
		if (x=='U')
		return 21;
		if (x=='V')
		return 22;
		if (x=='W')
		return 23;
		if (x=='X')
		return 24;
		if (x=='Y')
		return 25;
		if (x=='Z')
		return 26;
		
}


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

bool check_epq(int e,int p,int q)
{	
	if (gcd(e,(p-1)*(q-1))==1)
	return 1;
	else
	return 0;
}


int main()
{
	int e,q,p,n;
	char a,s,d,f;
	cout<<"Enter e, p, and q: "<<endl;
	cin>>e>>p>>q;
	if (check_epq(e,p,q)==0)
	{
		cout<<"ERROR!!!!"<<endl;
		exit(1);
	}
	else
	{
		n=q*p;
		cout<<"Enter four uppercase letters: ";
		cin>>a>>s>>d>>f;
		
		cout<<"The encoding of "<<a<<s<<d<<f<<" is "<<encode(char_to_number(a),e,n)<<" "<<encode(char_to_number(s),e,n)<<" "<<encode(char_to_number(d),e,n)<<" "<<encode(char_to_number(f),e,n)<<endl;
	}
	return 0;
}
