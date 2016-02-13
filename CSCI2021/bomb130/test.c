#include <stdio.h>
#include <stdlib.h>

int isone(int x)
{
	if (x==1)
		return 1;
	else
		return 0;
}

int main()
{
	int num=0;
	scanf("%d",&num);
	int y=isone(num);
	
	printf("%10d",y);
	
	return 0;
}
