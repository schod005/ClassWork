
public class Longhand {
	public static void longh(int n)
	{
		int leadDigit = 0;
		switch(n){
			case 0:
				System.out.print("Zero");
		}
		switch(n){
			case 1000:
				System.out.print("One thousand");
		}
		n=n%1000;
		leadDigit = n/100;
		leadDigit = leadDigit*100;
		switch(leadDigit){
			case 900:{
				System.out.print("Nine Hundred ");
				n=n-900;
				break;}
			case 800:{
				System.out.print("Eight Hundred ");
				n=n-800;
				break;}
			case 700:{
				System.out.print("Seven Hundred ");
				n=n-700;
				break;}
			case 600:{
				System.out.print("Six Hundred ");
				n=n-600;
				break;}
			case 500:{
				System.out.print("Five Hundred ");
				n=n-500;
				break;}
			case 400:{
				System.out.print("Four Hundred ");
				n=n-400;
				break;}
			case 300:{
				System.out.print("Three Hundred ");
				n=n-300;
				break;}
			case 200:{
				System.out.print("Two Hundred ");
				n=n-200;
				break;}
			case 100:{
				System.out.print("One Hundred ");
				n=n-100;
				break;}
		}
		leadDigit = n/10;
		leadDigit = leadDigit*10;
		switch(leadDigit){
			case 90:{
				System.out.print("Ninety ");
				n=n-90;
				break;}
			case 80:{
				System.out.print("Eighty ");
				n=n-80;
				break;}
			case 70:{
				System.out.print("Seventy ");
				n=n-70;
				break;}
			case 60:{
				System.out.print("Sixty ");
				n=n-60;
				break;}
			case 50:{
				System.out.print("Fifty ");
				n=n-50;
				break;}
			case 40:{
				System.out.print("Forty ");
				n=n-40;
				break;}
			case 30:{
				System.out.print("Thirty ");
				n=n-30;
				break;}
			case 20:{
				System.out.print("Twenty ");
				n=n-20;}
		}
		switch(n){
			case 19:{
				System.out.print("Nineteen");
				break;}
			case 18:{
				System.out.print("Eighteen");
				break;}
			case 17:{
				System.out.print("Seventeen");
				break;}
			case 16:{
				System.out.print("Sixteen");
				break;}
			case 15:{
				System.out.print("Fifteen");
				break;}
			case 14:{
				System.out.print("Fourteen");
				break;}
			case 13:{
				System.out.print("Thirteen");
				break;}
			case 12:{
				System.out.print("Twelve");
				break;}
			case 11:{
				System.out.print("Eleven");
				break;}
			case 10:{
				System.out.print("Ten");
				break;}
			case 9:{
				System.out.print("Nine");
				break;}
			case 8:{
				System.out.print("Eight");
				break;}
			case 7:{
				System.out.print("Seven");
				break;}
			case 6:{
				System.out.print("Six");
				break;}
			case 5:{
				System.out.print("Five");
				break;}
			case 4:{
				System.out.print("Four");
				break;}
			case 3:{
				System.out.print("Three");
				break;}
			case 2:{
				System.out.print("Two");
				break;}
			case 1:
				System.out.print("One");
		}
	System.out.print("\n");
	}
	public static void main(String args[]) {
		for(int i=0;i<20;i++)
			longh(i);
	}
}
