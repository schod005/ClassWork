#include <iostream>
#include <cstdlib>
#include <time.h>
using namespace std;

int main()
{
	int board[12][12];
	srand(time(NULL));
	int r=rand()%8;
	
	
// initializing the board	
	for(int x=0;x<12;x++)
		{
			for(int y=0;y<12;y++)
			board[x][y]=0;
		}
	for(int x=0;x<2;x++)
		{
			for(int y=0;y<12;y++)
			board[x][y]=1;
		}
	for(int x=10;x<12;x++)
		{
			for(int y=0;y<12;y++)
			board[x][y]=1;
		}
	for(int x=0;x<12;x++)
		{
			for(int y=0;y<2;y++)
			board[x][y]=1;
		}
	for(int x=0;x<12;x++)
		{
			for(int y=10;y<12;y++)
			board[x][y]=1;
		}
		
		
// displays board	
	for(int x=0;x<12;x++)
		{
			for(int y=0;y<12;y++)
			cout<<board[x][y]<<"\t";
		cout<<endl<<endl;
		}

		
	int horizontal[]={2,1,-1,-2,-2,-1,1,2}, vertical[]={-1,-2,-2,-1,1,2,2,1};
	int currentRow=2, currentColumn=3;
	int moveNumber, count=2, count2=1, number=1;




	board[currentRow][currentColumn]=1;
	while (count!=64)
	{
		
		
		for(int number=0;number<512;number++)
		{
		int r=rand()%8;
		for (int moveNumber=r;moveNumber<8;moveNumber++)
		{

			number++;
			if (board[currentRow + vertical[moveNumber]][currentColumn + horizontal[moveNumber]]==0)
			{

				currentRow += vertical[moveNumber];
				currentColumn += horizontal[moveNumber];
				board[currentRow][currentColumn]=count++;			
				srand(time(NULL));
				int r=rand()%8;
			}

			for(int x=2;x<10;x++)
			{
				for(int y=2;y<10;y++)
				cout<<board[x][y]<<"\t";
				cout<<endl<<endl;
			}
		cout<<endl<<"steps: "<<count-1<<endl<<endl<<count2<<endl<<endl;
	
		
		}
	
		
	
		
	
		}
	if(count2<count)
	count2=count;
	count=2;
		for(int x=0;x<12;x++)
		{
			for(int y=0;y<12;y++)
			board[x][y]=0;
		}
	for(int x=0;x<2;x++)
		{
			for(int y=0;y<12;y++)
			board[x][y]=1;
		}
	for(int x=10;x<12;x++)
		{
			for(int y=0;y<12;y++)
			board[x][y]=1;
		}
	for(int x=0;x<12;x++)
		{
			for(int y=0;y<2;y++)
			board[x][y]=1;
		}
	for(int x=0;x<12;x++)
		{
			for(int y=10;y<12;y++)
			board[x][y]=1;
		}
		int currentRow=2, currentColumn=3;
		board[currentRow][currentColumn]=1;



}
		return 0;	
}
