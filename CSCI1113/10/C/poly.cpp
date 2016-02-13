#include <iostream>
#include <cmath>
using namespace std;
#include "poly.h"
#include "Complex.h"
Poly::Poly()
{
	for(int i=0;i<20;i++)
	coefficient[i]=0;
}

Poly::Poly(double a, double b, double c)
{
	coefficient[0]=a;
	coefficient[0]=b;
	coefficient[0]=c;
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
	int n=19;
	/*b.degree()*/
	char s;

    if(b.coefficient[0]!=0)
	cout<<b.coefficient[0];

	s='+';


		if(b.coefficient[1]<0 && abs(b.coefficient[1])!=1)
		{
			s='-';
			if(b.coefficient[0]==0)
            cout<<abs(b.coefficient[1])<<"x";
			else if(b.coefficient[1]!=0)
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
			if(b.coefficient[0]==0 && b.coefficient[1]==1)
            cout<<"x";
            else
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

double Poly::evaluate(double x)
{
	double value;

	for(int i=0;i<20;i++)
	value+=pow(x,i)*coefficient[i];
	return value;
}

void Poly::roots(Complex &c1, Complex &c2)
{
	double a,b,c,dis;
	a=coefficient[2];
	b=coefficient[1];
	c=coefficient[0];
	dis=sqrt(b*b-4*a*c);



	if (dis>0)
	{
		c1.real=(-b+sqrt(b*b-4*a*c))/2/a;
		c2.real=(-b-sqrt(b*b-4*a*c))/2/a;
		cout<<"Two real roots, x1 = "<<c1<<", x2 = "<<c2<<endl;
	}
	else if (dis==0)
	{
		c1.real=(-b+sqrt(b*b-4*a*c))/2/a;

		cout<<"One double root, x = "<<c1<<endl;
	}
	else
	{
		c1.real=-b/2/a;
		c1.imag=(sqrt(-b*b+4*a*c))/2/a;
		c2.real=-b/2/a;
		c2.imag=-(sqrt(-b*b+4*a*c))/2/a;

		cout<<"Two complex roots, c1 = "<<c1<<", c2 = "<<c2<<endl;
	}

}

Poly Poly::dx()
{
	Poly c;
	for(int i=1;i<20;i++)
	{
		c.coefficient[i]=coefficient[i]*i;
	}
	for (int j=1;j<20;j++)
	{
		c.coefficient[j-1]==coefficient[j];
	}
	return c;
}

Poly Poly::integral()
{
	Poly c;
	for (int j=0;j<20;j++)
	{
		c.coefficient[j+1]=coefficient[j]/(j+1);
	}


	return c;
}
