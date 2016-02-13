#ifndef POLY_H
#define POLY_H


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
		private:
			double coefficient[20];
			

	
	};


#endif
