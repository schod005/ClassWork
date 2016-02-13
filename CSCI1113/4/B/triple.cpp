#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int side1=1,side2=1,hyp=1, count=0;
	for(;side1<=300;side1++)
		{
			for(side2=side1;side2<=300;side2++)
				{
					for(hyp=side2;hyp<=300;hyp++)
						{
							if(side1*side1+side2*side2==hyp*hyp)
								{
									cout<<side1<<" "<<side2<<" "<<hyp<<endl;
									count++;
									
								}
						}
				}
		}
		cout<<count<<endl;
		return 0;
}
