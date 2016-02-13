#include <iostream>
#include "Bug.h"
using namespace std;


	
		Bug::Bug()
		{
			position=0;
			dir=1;
		}
		
		Bug::Bug(int x)
		{
			position=x;
			dir=1;
		}
		
		void Bug::move()
		{
			position+=dir;
		}
		
		void Bug::turn()
		{
			dir*=-1;
		}
		
		void Bug::display()
		{
			cout<<"the current position is "<<position<<", and the current direction is "<<dir<<endl;
		}
	
	

