#ifndef POLY_H
#define POLY_H
#include "Complex.h"

class Poly
	{
		public:
			Poly();
			Poly(double,double,double);
			Poly(double [], int);
			int degree();
			friend ostream & operator <<(ostream &, Poly &);
			friend Poly operator +(Poly, Poly);
			friend Poly operator +(Poly, double);
			friend Poly operator -(Poly, Poly);
			friend Poly operator -(Poly, double);
			friend Poly operator *(Poly, Poly);
			friend Poly operator *(Poly, double);
			double evaluate(double);
			void roots(Complex &, Complex &);
			Poly dx();
			Poly integral();
		private:
			double coefficient[20];
			

	
	};


#endif
