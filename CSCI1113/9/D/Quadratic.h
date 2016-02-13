#ifndef QUADRATIC_H
#define QUADRATIC_H


class Quadratic
	{
		public:
		
		Quadratic();
		
		void GetData();
		void ShowData();
		double Value(double);
		void Roots();

		private:
		
		double a;
		double b;
		double c;
		
	};


#endif
