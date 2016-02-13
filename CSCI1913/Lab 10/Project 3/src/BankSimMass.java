import java.io.DataOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;


public class BankSim {
	static PQ agenda = new PQ();
	public static IndividualQTeller[] iTellerList;
	public static SharedQTeller[] sTellerList;
	public static boolean EXPRESS_AVAILABLE = false; //toggle for use of express line in bank
	public static double PRIORITY_LINE_MAXIMUM_TIME = 45; //sets the upper limit on service time for customers entering express line
	public static int NUMBER_OF_TELLERS = 8; 
	public static int SIMULATION_LENGTH = 15000;
	public static int INTERARRIVAL_RATE = 30; //sets the average arrival time of customers
	public static boolean WRITE_TO_FILE = true;
	public static DataOutputStream individualQFile = null;
	public static DataOutputStream sharedQFile = null;

	
	public static void main(String args[]) {
		int distArray[] = {45,70,100,100,190,190,190,190,240,250,420,500};
		for(int h = 15000;h<=15000;h+=5000){ //h will run through differing simulation lengths
			SIMULATION_LENGTH=h;
			for(int i=0;i<1;i++){ //j runs through both express teller and no express teller
				if(i==0)
					EXPRESS_AVAILABLE=false;
				else
					EXPRESS_AVAILABLE = true;
				for(int j=25;j<=35;j++){ //j runs through various interarrival times
					for(int k=1;k<9;k++){ //k runs through the differing amounts of tellers (1-8)
						for(int l=1;l<16;l++){ // l is the number of replicate measurements desired for each set of conditions
							NUMBER_OF_TELLERS=k;
							INTERARRIVAL_RATE=j;
							iTellerList = IndividualQTeller.initialize(NUMBER_OF_TELLERS);
							sTellerList = SharedQTeller.initialize(NUMBER_OF_TELLERS);
				
							SharedQStat.initialize(NUMBER_OF_TELLERS);
							IndividualQStat.initialize(NUMBER_OF_TELLERS);
					
							agenda.add(new CustomerMaker(INTERARRIVAL_RATE, distArray),0); //adds the first CustomerMaker to the agenda at time 0
							
							while (agenda.getCurrentTime() <= SIMULATION_LENGTH)
								agenda.remove().run();
							
							if(WRITE_TO_FILE){ // If WRITE_TO_FILE toggle is true, the data will be output to the specified file
								try {
									individualQFile = new DataOutputStream(new FileOutputStream("individual data.txt",true)); //indicate file location to store data from Individual Queue simulations
									sharedQFile = new DataOutputStream(new FileOutputStream("shared data.txt",true)); // indicate file location to store data from Shared Queue simulations
								} catch (FileNotFoundException e) {
									
									e.printStackTrace();
								}
							}
							SharedQStat.displayStats(WRITE_TO_FILE); //Prints statistics for individual queue system to the console and will also write to file, if desired
							IndividualQStat.displayStats(WRITE_TO_FILE); // Prints statistics for Shared Queue system to the console and will write to file if WRITE_TO_FILE is true
							SharedQTeller.reset(); //Resets SharedQTeller class to prepare for next run
							IndividualQTeller.reset(); //Resets IndividualQ class to prepare for next run
							agenda=new PQ();

						}
						}
					}
				}	
		}
	}
}


