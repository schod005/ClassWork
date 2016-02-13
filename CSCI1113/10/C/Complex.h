#ifndef COMPLEX_H
#define COMPLEX_H


class Complex
	{
		public:
			Complex();
			Complex(double, double);
			friend ostream & operator <<(ostream &, Complex &);
			double getReal();
			double getImag();

			double real;
			double imag;

	
	};


#endif
