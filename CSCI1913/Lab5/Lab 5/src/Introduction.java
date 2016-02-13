

import java.util.Scanner;

/**
 *
 * @author Jordan Hayes
 */
public class Introduction {

    public static void main(String[] args) 
    {
        Introduction app = new Introduction();
        //To test your getUser method
          app.getUser();
        //To test your multiplyMatrix method
   //int[][] matrix = new int[2][2];
 // int[][] multiplierResult = app.multiplyMatrix(matrix, 5);
 // for(int i=0;i<2;i++)
//	  for(int j=0;j<2;j++)
//		  System.out.println(multiplierResult[i][j]+" ");
      //To test your rowSumProduct
//        int rowSumProduct(matrix, 0);
        // There is no test for the PrintPascal function your output should look like the one in the PDF
  
 app.PrintPascal(8);   }
    
    public void getUser()
    {
        Scanner input = new Scanner(System.in);
        String s1 = input.next();
        System.out.println("Welcome, "+s1+"!  This is lab 5!");
    }
    
    public int[][] multiplyMatrix(int [][] matrix, int multiplier)
    {
    	 if(matrix == null)
        	return null;
        int [][] empty= new int[matrix.length][matrix[0].length];
        for(int i=0;i<matrix.length;i++)
    		for(int j=0;j<matrix[0].length;j++)
    			empty[i][j]=matrix[i][j]*multiplier;

        return empty;
        
    }
    public Integer rowSumProduct(int [][] matrix, int currentRow)
    {
    	if(matrix == null)
        	return null;
    	if(currentRow>matrix.length)
    		return null;
        if(currentRow==matrix.length)
    		return 1;
    	int sum=0;
    	for(int i=0;i<matrix[0].length;i++)
    		sum+=matrix[currentRow][i];	
        return sum*rowSumProduct(matrix,currentRow+1);
    }
    public void PrintPascal(int N){
        int[][] pascal  = new int[N][]; //initializing array

        // initialize first row
        pascal[0] = new int[1];
        pascal[0][0] = 1;
        
        // TODO fill in Pascal's triangle
        for(int i = 1;i<N;i++)
        	{pascal[i] = new int[i+1];
        	pascal[i][0]=1;
        	pascal[i][i]=1;
        	for(int j=1;j<i;j++)
        		pascal[i][j]=pascal[i-1][j-1]+pascal[i-1][j];}
        		
        
        //TODO print results
        	for(int i=0;i<N;i++)
        		{for(int j=0;j<pascal[i].length;j++)
        			System.out.print(pascal[i][j]+" ");
        		System.out.println(" ");}
    }
}
