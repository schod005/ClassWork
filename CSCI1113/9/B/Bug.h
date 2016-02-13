#ifndef BUG_h
#define BUG_h


class Bug
	{
		public:
		Bug();
		Bug(int);
		void move();
		void turn();
		void display();
		
		
		
		private:
		int position;
		int dir;
	};

#endif
