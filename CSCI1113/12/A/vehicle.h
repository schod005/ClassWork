#ifndef VEHICLE_H
#define VEHICLE_H
#include <string>
#include <iostream>
class vehicle
{
	public:
	vehicle(){Make="";Model="";Year=0;Mileage=0;};
	void setMake(string a){Make=a;};
	void setModel(string a){Model=a;};
	void setYear(int a){Year=a;};
	void setMileage(int a){Mileage=a;};
	string getMake(){return Make;};
	string getModel(){return Model;};
	int getYear(){return Year;};
	int getMileage(){return Mileage;};
	void Display(ostream& cout){cout<<"Make: "<<Make<<endl<<"Year: "<<Year<<endl<<"Model: "<<Model<<endl<<"Miles: "<<Mileage<<" miles"<<endl;};	
	
	protected:
	string Make;
	string Model;
	int Year;
	int Mileage;




};



#endif

#ifndef CAR_H
#define CAR_H

class car:public vehicle
{
	public:
	car(){NumberDoors="";};
	void setNumberDoors(string a){NumberDoors=a;};
	string getNumberDoors(){return NumberDoors;};
	void Display(ostream& cout){cout<<"Make: "<<Make<<endl<<"Year: "<<Year<<endl<<"Model: "<<Model<<endl<<"Number of doors: "<<NumberDoors<<endl<<"Miles: "<<Mileage<<" miles"<<endl;};
	private:
	string NumberDoors;
	
	
};
#endif



#ifndef TRUCK_H
#define TRUCK_H

class truck:public vehicle
{
	public:
	truck(){DriveType="2-wheel drive";};	
	void setDriveType(string a){DriveType=a;};
	string getDriveType(){return DriveType;}
	void Display(ostream& cout){cout<<"Make: "<<Make<<endl<<"Drive Type: "<<DriveType<<endl<<"Year: "<<Year<<endl<<"Model: "<<Model<<endl<<"Miles: "<<Mileage<<" miles"<<endl;};
	private:
	string DriveType;
	
	
};
#endif



#ifndef SUV_H
#define SUV_H

class SUV:public vehicle
{
	public:
	SUV(){PassengerCapacity="";};	
	void setPassengerCapacity(string a){PassengerCapacity=a;};
	string getPassengerCapacity(){return PassengerCapacity;};
	void Display(ostream& cout){cout<<"Make: "<<Make<<endl<<"Passenger Capacity: "<<PassengerCapacity<<endl<<"Year: "<<Year<<endl<<"Model: "<<Model<<endl<<"Miles: "<<Mileage<<" miles"<<endl;};
	
	private:
	string PassengerCapacity;
	
	
};
#endif
