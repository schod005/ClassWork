import java.io.DataOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;


public class BankSim {
	static PQ agenda = new PQ();
	public static IndividualQTeller[] iTellerList;
	public static SharedQTeller[] sTellerList;
	public static boolean EXPRESS_AVAILABLE = true; //toggle for use of express line in bank
	public static double PRIORITY_LINE_MAXIMUM_TIME = 45; //sets the upper limit on service time for customers entering express line
	public static int NUMBER_OF_TELLERS = 8;
	public static int SIMULATION_LENGTH = 15000;
	public static int CUSTOMER_DIST = 40;
	public static boolean WRITE_TO_FILE = true;
	
	public static void main(String args[]) {

		int distArray[] = {45,70,100,100,190,190,190,190,240,250,420,500};
		
		
		iTellerList = IndividualQTeller.initialize(NUMBER_OF_TELLERS);
		sTellerList = SharedQTeller.initialize(NUMBER_OF_TELLERS);

		SharedQStat.initialize(NUMBER_OF_TELLERS);
		IndividualQStat.initialize(NUMBER_OF_TELLERS);

		agenda.add(new CustomerMaker(CUSTOMER_DIST, distArray),0);
		
		while (agenda.getCurrentTime() <= SIMULATION_LENGTH)
			agenda.remove().run();
		
		SharedQStat.displayStats();
		IndividualQStat.displayStats();
		if(WRITE_TO_FILE){
			DataOutputStream fileind = null;
			DataOutputStream fileshar = null;
			try {
				fileind = new DataOutputStream(new FileOutputStream("individual data.txt",true));
				fileshar = new DataOutputStream(new FileOutputStream("shared data.txt",true));
			} catch (FileNotFoundException e) {
				
				e.printStackTrace();
			}
			try {
				
				fileind.writeBytes(CUSTOMER_DIST+"\t");
				fileshar.writeBytes(CUSTOMER_DIST+"\t");
			} catch (IOException e) {
				e.printStackTrace();
			}
			IndividualQStat.filestats(fileind);
			SharedQStat.filestats(fileshar);
		}
	}
}

