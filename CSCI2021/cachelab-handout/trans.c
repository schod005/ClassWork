/* David Schoder
 * 4552990
 * 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
 void T8x8(int M, int N, int A[N][M], int B[M][N], int starti, int startj);
 void T4x4(int M, int N, int A[N][M], int B[M][N], int starti, int startj);
 void T3x3(int M, int N, int A[N][M], int B[M][N], int starti, int startj);
 void T5x5(int M, int N, int A[N][M], int B[M][N], int starti, int startj);
 void T7x7(int M, int N, int A[N][M], int B[M][N], int starti, int startj);
 void T6x6(int M, int N, int A[N][M], int B[M][N], int starti, int startj);
 void SmarterT8x8(int M, int N, int A[N][M], int B[M][N], int starti, int startj);

char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N])
{
	//64x64
	//Works by transposing 8x8 blocks in smaller 4x4 blocks.
	//Transposes top left and bottom right 4x4 row by row and puts
	//A's bottom left transpose in B's top right.  Then copies row by 
	//row of B's top right into B's botton left while transposing A's
	//bottom left into B's top right column by column.  It is done this
	//way because 8x8 has a lot of misses while 4x4 has few.  Also, 8
	//values are loaded for each row, so doing 4x4 by itself would be a 
	//waste of the other 4 values that could be hits.
	
	int i,j; //2 local variables
	if(M==64 && N==64)
	{
		for(i=0;i<64;i+=8)
			for(j=0;j<64;j+=8)
				{
					SmarterT8x8(M,N,A,B,i,j); //8 local variables
				}

	}
	
	//61x67
	//Works by transposing a 56x56 block with 8x8 subblocks.  Then
	//transposes the rest in 8x5, 8x3, and 5x8 blocks and one 5x3 block.
	
	if(M==61 && N==67)
	{
	  int i,j,k,l; //4 local variables
		for(i = 0; i < N; i += 8)
			for(j = 0; j < M; j += 8)
			{
				if(j<56 && i<56) //56x56
					T8x8(M,N,A,B,j,i);
				else //finish up
					for(k = j; k < j + 8; k++)
						for(l = i; l < i + 8; l++)
							if(k<M && l<N)
								B[k][l]=A[l][k];
				
			}	
	}
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 

/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

 void T8x8(int M, int N, int A[N][M], int B[M][N], int starti, int startj)
{
	int a1,a2,a3,a4,a5,a6,a7,a8;
	int j=startj;
	for(int i=starti;i<starti+8;i++)
		{
			a1=A[i][j];
			a2=A[i][j+1];
			a3=A[i][j+2];
			a4=A[i][j+3];
			a5=A[i][j+4];
			a6=A[i][j+5];
			a7=A[i][j+6];
			a8=A[i][j+7];
			B[j][i]=a1;
			B[j+1][i]=a2;
			B[j+2][i]=a3;
			B[j+3][i]=a4;
			B[j+4][i]=a5;
			B[j+5][i]=a6;
			B[j+6][i]=a7;
			B[j+7][i]=a8;
		}
	
} //T8x8

 void T4x4(int M, int N, int A[N][M], int B[M][N], int starti, int startj)
{
	int a1,a2,a3,a4;
	int j=startj;
	for(int i=starti;i<starti+4;i++)
		{
			a1=A[i][j];
			a2=A[i][j+1];
			a3=A[i][j+2];
			a4=A[i][j+3];
			B[j][i]=a1;
			B[j+1][i]=a2;
			B[j+2][i]=a3;
			B[j+3][i]=a4;
		}
	
} //T4x4

 void T3x3(int M, int N, int A[N][M], int B[M][N], int starti, int startj)
{
	int a1,a2,a3;
	int j=startj;
	for(int i=starti;i<starti+3;i++)
		{
			a1=A[i][j];
			a2=A[i][j+1];
			a3=A[i][j+2];
			B[j][i]=a1;
			B[j+1][i]=a2;
			B[j+2][i]=a3;
		}
	
} //T3x3

 void T5x5(int M, int N, int A[N][M], int B[M][N], int starti, int startj)
{
	int a1,a2,a3,a4,a5;
	int j=startj;
	for(int i=starti;i<starti+5;i++)
		{
			a1=A[i][j];
			a2=A[i][j+1];
			a3=A[i][j+2];
			a4=A[i][j+3];
			a5=A[i][j+4];
			B[j][i]=a1;
			B[j+1][i]=a2;
			B[j+2][i]=a3;
			B[j+3][i]=a4;
			B[j+4][i]=a5;
		}
	
} //T5x5

 void T7x7(int M, int N, int A[N][M], int B[M][N], int starti, int startj)
{
	int a1,a2,a3,a4,a5,a6,a7;
	int j=startj;
	for(int i=starti;i<starti+7;i++)
		{
			a1=A[i][j];
			a2=A[i][j+1];
			a3=A[i][j+2];
			a4=A[i][j+3];
			a5=A[i][j+4];
			a6=A[i][j+5];
			a7=A[i][j+6];
			B[j][i]=a1;
			B[j+1][i]=a2;
			B[j+2][i]=a3;
			B[j+3][i]=a4;
			B[j+4][i]=a5;
			B[j+5][i]=a6;
			B[j+6][i]=a7;
		}
	
} //T7x7

 void T6x6(int M, int N, int A[N][M], int B[M][N], int starti, int startj)
{
	int a1,a2,a3,a4,a5,a6;
	int j=startj;
	for(int i=starti;i<starti+6;i++)
		{
			a1=A[i][j];
			a2=A[i][j+1];
			a3=A[i][j+2];
			a4=A[i][j+3];
			a5=A[i][j+4];
			a6=A[i][j+5];
			B[j][i]=a1;
			B[j+1][i]=a2;
			B[j+2][i]=a3;
			B[j+3][i]=a4;
			B[j+4][i]=a5;
			B[j+5][i]=a6;
		}
	
} //T6x6

 void SmarterT8x8(int M, int N, int A[N][M], int B[M][N], int starti, int startj)
{
	int a1,a2,a3,a4;
	int j=startj;
	int i;
	for(i=starti;i<starti+4;i++)
		{
			a1=A[i][j];
			a2=A[i][j+1];
			a3=A[i][j+2];
			a4=A[i][j+3];
			B[j][i+4]=A[i][j+4];
			B[j+1][i+4]=A[i][j+5];
			B[j+2][i+4]=A[i][j+6];
			B[j+3][i+4]=A[i][j+7];
			B[j][i]=a1;
			B[j+1][i]=a2;
			B[j+2][i]=a3;
			B[j+3][i]=a4;
		}
	i=starti;
	for(j=startj;j<startj+4;j++)
		{
			a1=B[j][i+4];
			a2=B[j][i+5];
			a3=B[j][i+6];
			a4=B[j][i+7];
			B[j][i+4]=A[i+4][j];
			B[j][i+5]=A[i+5][j];
			B[j][i+6]=A[i+6][j];
			B[j][i+7]=A[i+7][j];
			B[j+4][i]=a1;
			B[j+4][i+1]=a2;
			B[j+4][i+2]=a3;
			B[j+4][i+3]=a4;
		}
	j=startj+4;
	for(i=starti+4;i<starti+8;i++)
		{
			a1=A[i][j];
			a2=A[i][j+1];
			a3=A[i][j+2];
			a4=A[i][j+3];
			B[j][i]=a1;
			B[j+1][i]=a2;
			B[j+2][i]=a3;
			B[j+3][i]=a4;
		}

	
} //SmarterT8x8

