#include <iostream>
using namespace std;
#include "vehicle.h"

int main()
{
	car c1, c2;
	truck t1;
	SUV suv1,suv2;
	c1.setYear(1987);
	c1.setMake("Audi");
	c1.setMileage(185000);
	c1.setModel("A6");
	c1.setNumberDoors("4-door");
	
	c2.setYear(1963);
	c2.setMake("Volkswagen");
	c2.setMileage(240000);
	c2.setModel("Beetle");
	c2.setNumberDoors("2-door");
	
	t1.setYear(2007);
	t1.setMake("Ford");
	t1.setMileage(82000);
	t1.setModel("F-150");
	t1.setDriveType("4-wheel");
	
	suv1.setYear(2001);
	suv1.setMake("Chevrolet");
	suv1.setMileage(118000);
	suv1.setModel("Suburban");
	suv1.setPassengerCapacity("8-passenger");
	
	suv2.setYear(2010);
	suv2.setMake("Kia");
	suv2.setMileage(29000);
	suv2.setModel("Sorento");
	suv2.setPassengerCapacity("5-passenger");
	
	c1.Display(cout);
	cout<<endl;
	c2.Display(cout);
	cout<<endl;
	t1.Display(cout);
	cout<<endl;
	suv1.Display(cout);
	cout<<endl;
	suv2.Display(cout);
	cout<<endl;
	
	return 0;
}
