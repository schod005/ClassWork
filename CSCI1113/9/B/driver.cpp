#include <iostream>
#include "Bug.h"

using namespace std;

int main()
{
	Bug a(10);
	a.move();
	a.display();
	a.turn();
	a.display();
	a.move();
	a.display();
	
	
	return 0;
}
