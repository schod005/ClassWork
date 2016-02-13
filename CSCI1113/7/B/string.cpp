#include <iostream>
using namespace std;

int main()
{
	string str1, str2;
	getline(cin,str1);
	
	cout<<"str1[0]: "<<str1[0]<<endl;
	cout<<"str1[1]: "<<str1[1]<<endl;
	
	cout<<"The number of characters in str1: "<<str1.length()<<endl;
	
	str2 = str1.substr(0,3);
	
	cout<<"str2: "<<str2<<endl;
	
	int pos1 = str1.find('0');
	
	cout<<"position of the first 0: "<<pos1<<endl;
	
	int pos2 = str1.find('0',pos1+1);
	if(pos2==string::npos)
		cout<<"pos2: NOT FOUND!!"<<endl;
	cout<<"position of the second 0: "<<pos2<<endl;
	
	int pos3 = str1.find(' ');
	
	cout<<"position of the first space: "<<pos3<<endl;
}
