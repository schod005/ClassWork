#include <iostream> #include <cmath> #include <fstream> using namespace
std;

void display(double temp[][200]);


int main() {
	ofstream temp1; temp1.open("temp.dat");

	double temp[200][200], old[200][200]; double top, bottom,
	left, right, interior; int foo=0; cout<<"Please enter the top,
	bottom, left, right, and initial interior temperature: "<<endl;
	cin>>top>>bottom>>left>>right>>interior; for (int i=1;i<199;i++) {
		for (int j=1;j<199;j++) old[i][j]=interior;
	} for (int i=0;i<200;i++)
		old[0][i]=top;
	for (int i=0;i<200;i++)
		old[199][i]=bottom;
	for (int i=1;i<199;i++)
		old[i][0]=left;
	for (int i=1;i<199;i++)
		old[i][199]=right;

		for (int i=0;i<200;i++) {
			for (int j=0;j<200;j++) temp[i][j]=old[i][j];
		}


	cout<<endl<<endl<<"The initial state is:"<<endl<<endl;

	display(old);

	cout<<"The final state is:"<<endl<<endl<<endl;


	while (foo<39100) {
		foo=0; for (int i=1;i<199;i++) {
			for (int j=1;j<199;j++)
			temp[i][j]=0.25*(old[i+1][j]+old[i-1][j]+old[i][j+1]+old[i][j-1]);
		}

		for (int i=1;i<199;i++) {
			for (int j=1;j<199;j++)
				{ if (abs(temp[i][j]-old[i][j])<0.0001)
					{
						foo++;
					}
				}
		}

		for (int i=1;i<199;i++) {
			for (int j=1;j<199;j++) old[i][j]=temp[i][j];
		}
	cout<<foo<<endl;

	}

	display(temp); cout<<foo<<endl; for (int i=0;i<200;i++) {
		for (int j=0;j<200;j++)
			temp1<<temp[i][j]<<"\t";
		temp1<<endl;
	} temp1.close(); return 0;
}

void display(double temp[][200]) {
	for (int i=0;i<200;i++) {
		for (int j=0;j<200;j++) cout<<temp[i][j]<<"\t";
	cout<<endl<<endl; }
}
