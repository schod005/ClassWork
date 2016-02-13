#include <iostream>
#include <cmath>
using namespace std;
#include "poly.h"

Poly::Poly()
{
	for(int i=0;i<20;i++)
	coefficient[i]=0;
}

Poly::Poly(double a, double b, double c)
{
	coefficient[0]=a;
	coefficient[1]=b;
	coefficient[2]=c;	
}

Poly::Poly(double x[],int size)
{
	for(int i=0;i<size;i++)
		coefficient[i]=x[i];
}

int Poly::degree()
{
	int d;
	for(int i=0;i<20;i++)
	{
		if (coefficient[i]!=0)
		d=i;
	}
	
	return d;
}

ostream & operator <<(ostream &a, Poly &b)
{
	int n=b.degree();
	char s;
	
	
	cout<<b.coefficient[0];
	
	s='+';
		
		
		if(b.coefficient[1]<0 && abs(b.coefficient[1])!=1)
		{
			s='-';
			if(b.coefficient[1]!=0)
			cout<<' '<<s<<' '<<abs(b.coefficient[1])<<"x";
		}

		else if(b.coefficient[1]>0 && abs(b.coefficient[1])!=1)
		{
			if(b.coefficient[1]!=0)
			cout<<' '<<s<<' '<<abs(b.coefficient[1])<<"x";
		}
		 
		else if(abs(b.coefficient[1])==1)
		{
			if (b.coefficient[1]==-1)
			s='-';
			cout<<' '<<s<<' '<<"x";
		}
	
	for(int i=2;i<=n;i++)
	{
		s='+';
		
		
		if(b.coefficient[i]<0 && abs(b.coefficient[i])!=1)
		{
			s='-';
			if(b.coefficient[i]!=0)
			cout<<' '<<s<<' '<<abs(b.coefficient[i])<<"x^"<<i;
		}

		else if(b.coefficient[i]>0 && abs(b.coefficient[i])!=1)
		{
			if(b.coefficient[i]!=0)
			cout<<' '<<s<<' '<<abs(b.coefficient[i])<<"x^"<<i;
		}
		 
		else if(abs(b.coefficient[i])==1)
		{
			if (b.coefficient[i]==-1)
			s='-';
			cout<<' '<<s<<' '<<"x^"<<i;
		}
		
		
	}
	cout<<endl;

	return a;
}

Poly operator +(Poly a, Poly b)
{
	Poly c;
	for(int i=0;i<20;i++)
	{
		c.coefficient[i]=a.coefficient[i]+b.coefficient[i];
	}
		return c;
}

Poly operator -(Poly a, Poly b)
{
	Poly c;
	for(int i=0;i<20;i++)
	{
		c.coefficient[i]=a.coefficient[i]-b.coefficient[i];
	}
	return c;
}

Poly operator +(Poly a, double x)
{
	Poly c;
	for(int i=0;i<20;i++)
	{
		c.coefficient[i]=a.coefficient[i];
	}
		c.coefficient[0]+=x;
	return c;
}

Poly operator -(Poly a, double x)
{
	Poly c;
	for(int i=0;i<20;i++)
	{
		c.coefficient[i]=a.coefficient[i];
	}
		c.coefficient[0]-=x;
	return c;
}

Poly operator *(Poly a, Poly b)
{
	Poly c;
	for(int i=0;i<10;i++)
	{
		
		for(int j=0;j<10;j++)
		c.coefficient[i+j]+=a.coefficient[i]*b.coefficient[j];
		
	}
	return c;
	
	
}

Poly operator *(Poly a, double x)
{
	Poly c;
	for(int i=0;i<20;i++)
	{
		c.coefficient[i]=a.coefficient[i]*x;
	}

	return c;
}
