#include <iostream>
#include <cstdlib>
#include <time.h>
#include <ctime>

using namespace std;

void diceRoll(int &r1, int &r2)
{
	

	r1=rand()%6+1;
	r2=rand()%6+1;
	
}

void displayRoll(int& r1, int& r2)
{
	cout<<"The dice roll is: ["<<r1<<","<<r2<<"] = "<<r1+r2<<endl;
}

int main()
{
	int r1, r2,total;
	srand(time(NULL));
	diceRoll(r1,r2);
	displayRoll(r1,r2);
	if(((r1+r2)==7)||(((r1+r2)==11)))
		cout<<"You win!"<<endl;
	else if(((r1+r2)==2)||((r1+r2)==3)||((r1+r2)==12))
		cout<<"Craps!  Sorry, you lose"<<endl;
	else
	{
		cout<<"Point is "<<(r1+r2)<<".  Roll again"<<endl;
		total=r1+r2;

		diceRoll(r1,r2);
		while(r1+r2!=total && r1+r2!=7)
		{

			displayRoll(r1,r2);
			diceRoll(r1,r2);

		}
		if((r1+r2)==total)
		{
			displayRoll(r1,r2);
			cout<<"You win!"<<endl;
		}
		else if(r1+r2==7)
		{
			displayRoll(r1,r2);
			cout<<"Sorry, you lose"<<endl;
		}
	}
	return 0;
}
