import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;

// Stat.java

// Priority Queue and Simulation

// Statistics class for Bank Simulation

public class IndividualQStat {

    // public methods
	
	public static void initialize(int n){
		numberOfTellers = n;
		for(int i=0;i<n;i++){
			lastUpdateTime = new double[n];
			oldQLength = new int[n];
		    lastQUpdateTime = new double[n];
		    customersServed = new int[n];
		    busyTime = new double[n];
		    idleTime = new double[n];
		    averageWait = new double[n];
		    maxQLength = new int[n];
		    averageQLength = new double[n]; 
		    averageServiceTime = new double[n];
		}
	}

    public static void updateQueueStats(IndividualQTeller t,double time, int qlen) {
    	
    	int index = t.getIndex();

        if (qlen > maxQLength[index])

          maxQLength[index] = qlen;

        averageQLength[index] += oldQLength[index] * (time - lastQUpdateTime[index]);

        totalTime += (time - lastQUpdateTime[index])/numberOfTellers;  //divide by numberOfTellers to normalize this result as each teller has its own queue

        lastQUpdateTime[index] = time;

        oldQLength[index] = qlen;

    }

    public static void updateBusyTimeStats(IndividualQTeller t,double time) {
    	
    	int index = t.getIndex();
        busyTime[index] += time - lastUpdateTime[index];

        lastUpdateTime[index] = time;

    }        

    public static void updateIdleTimeStats(IndividualQTeller t,double time) {

        int index = t.getIndex();

        idleTime[index] += time - lastUpdateTime[index];

        lastUpdateTime[index] = time;

    }

    public static void updateServiceTimeStats(IndividualQTeller t,double st) {
    	
        averageServiceTime[t.getIndex()] += st;

    }

    public static void updateWaitTimeStats(IndividualQTeller t,double time, double enterTime) {

    	int index = t.getIndex();

        double wait = time - enterTime;
        
        if(wait >= 438)
        	upsetcustomers++;
        
        if (wait > maxWait)

          maxWait = wait;

        averageWait[index] += wait;

        customersServed[index]++;
        
    } 
    
    public static void displayStats() {
    	
    	double totalIdleTime = 0;
    	double totalBusyTime = 0;
    	double totalAverageServiceTime = 0;
    	double totalAverageWaitTime = 0;
    	double totalAverageQLength = 0;
    	int totalCustomersServed = 0;
    	int maxQueueLength = 0;
    	    	
        System.out.println("\n** Simulation Results for each teller having their own individual queue**\n");
        if(BankSim.EXPRESS_AVAILABLE){
        	numberOfTellers--;
        }
        for(int i = 0;i<numberOfTellers;i++){
        	System.out.println("Displaying results for Teller #"+(i+1)+ "\n");
        	
        	System.out.println(" Idle Time: " + idleTime[i]);

            System.out.println(" Busy Time: " + busyTime[i]);

            //System.out.println("(Busy Time based on service time: " + averageServiceTime[i]+")");
            
            System.out.println(" Average Service Time: " + averageServiceTime[i]/customersServed[i]);
            
            System.out.println(" Maximum Queue Length: " + maxQLength[i]);
                                                  
            System.out.println(" Average Wait Time:" + averageWait[i]/customersServed[i]+ "\n");
            
            totalIdleTime += idleTime[i];
            totalBusyTime += busyTime[i];
            totalAverageServiceTime += averageServiceTime[i];
            totalAverageWaitTime += averageWait[i];
            totalCustomersServed += customersServed[i];
            totalAverageQLength += averageQLength[i];
            if(maxQLength[i]>maxQueueLength)
            	maxQueueLength=maxQLength[i];
           // System.out.println(totalAverageWaitTime);
            //System.out.println(totalCustomersServed);
        }
        
        if(BankSim.EXPRESS_AVAILABLE){
        	System.out.println("Displaying results for Priority Queue Teller \n");
        	
        	System.out.println(" Idle Time: " + idleTime[numberOfTellers]);

            System.out.println(" Busy Time: " + busyTime[numberOfTellers]);

            //System.out.println("(Busy Time based on service time: " + averageServiceTime[i]+")");
            
            System.out.println(" Average Service Time: " + averageServiceTime[numberOfTellers]/customersServed[numberOfTellers]);
            
            System.out.println(" Maximum Queue Length: " + maxQLength[numberOfTellers]);
                                                  
            System.out.println(" Average Wait Time:" + averageWait[numberOfTellers]/customersServed[numberOfTellers]+ "\n");
            
            totalIdleTime += idleTime[numberOfTellers];
            totalBusyTime += busyTime[numberOfTellers];
            totalAverageServiceTime += averageServiceTime[numberOfTellers];
            totalAverageWaitTime += averageWait[numberOfTellers];
            totalCustomersServed += customersServed[numberOfTellers];
            totalAverageQLength += averageQLength[numberOfTellers];
            if(maxQLength[numberOfTellers]>maxQueueLength)
            	maxQueueLength=maxQLength[numberOfTellers];
        }
        
        System.out.println("Displaying OVERALL results for ALL tellers"+ "\n");

        System.out.println(" Calculated Simulation Time: " + totalTime);

        System.out.println(" Average Idle Time: " + totalIdleTime/numberOfTellers);

        System.out.println(" Average Busy Time: " + totalBusyTime/numberOfTellers);

       // System.out.println("(Busy Time based on service time: " + totalAverageServiceTime + ")\n");

        System.out.println(" Maximum Queue Length for any single Teller's Queue: " + maxQueueLength);

        System.out.println(" Average Queue Length: " + totalAverageQLength/numberOfTellers/totalTime);

        System.out.println(" Maximum Waiting Time: " + maxWait);
        
        System.out.println(" Number of Frustrated Customers: " + upsetcustomers);

        System.out.println(" Avg. Waiting Time for customers through the queue: " +

                                                 totalAverageWaitTime/totalCustomersServed);

        System.out.println(" Avg. Service Time: " + totalAverageServiceTime/totalCustomersServed);

        System.out.println(" Number of customers through bank: " + totalCustomersServed +"\n");

        System.out.println("\n");

    }  // displayStats

    public static void filestats(DataOutputStream file){
    	double totalIdleTime = 0;
    	double totalBusyTime = 0;
    	double totalAverageServiceTime = 0;
    	double totalAverageWaitTime = 0;
    	double totalAverageQLength = 0;
    	int totalCustomersServed = 0;
    	int maxQueueLength = 0;
    	    	
       
       
        for(int i = 0;i<numberOfTellers;i++){
        	totalIdleTime += idleTime[i];
            totalBusyTime += busyTime[i];
            totalAverageServiceTime += averageServiceTime[i];
            totalAverageWaitTime += averageWait[i];
            totalCustomersServed += customersServed[i];
            totalAverageQLength += averageQLength[i];
            if(maxQLength[i]>maxQueueLength)
            	maxQueueLength=maxQLength[i];
           // System.out.println(totalAverageWaitTime);
            //System.out.println(totalCustomersServed);
        }
        
        if(BankSim.EXPRESS_AVAILABLE){
        	totalIdleTime += idleTime[numberOfTellers];
            totalBusyTime += busyTime[numberOfTellers];
            totalAverageServiceTime += averageServiceTime[numberOfTellers];
            totalAverageWaitTime += averageWait[numberOfTellers];
            totalCustomersServed += customersServed[numberOfTellers];
            totalAverageQLength += averageQLength[numberOfTellers];
            if(maxQLength[numberOfTellers]>maxQueueLength)
            	maxQueueLength=maxQLength[numberOfTellers];
        }
        if(BankSim.EXPRESS_AVAILABLE)
        	numberOfTellers++;
        try {
			file.writeBytes(numberOfTellers+"\t"+BankSim.EXPRESS_AVAILABLE+"\t"+maxQueueLength+"\t"+totalAverageQLength/numberOfTellers/totalTime+"\t"+totalAverageServiceTime/totalCustomersServed+"\t"+totalAverageWaitTime/totalCustomersServed+"\t"+upsetcustomers+"\t"+totalCustomersServed+"\t"+totalBusyTime/numberOfTellers+"\t"+totalIdleTime/numberOfTellers+"\t"+System.getProperty("line.separator"));
		} catch (IOException e) {
			e.printStackTrace();
		}
        
    	
    } // filestats
    // private variables

    private static double[] lastUpdateTime;

    private static int[] oldQLength;

    private static double[] lastQUpdateTime;

    private static int numberOfTellers;
    
    private static int[] customersServed;

    private static double totalTime;

    private static double[] busyTime;

    private static double[] idleTime;

    private static double maxWait;

    private static double[] averageWait;

    private static int[] maxQLength;

    private static double[] averageQLength; 

    private static double[] averageServiceTime;
    
    private static int upsetcustomers;
    
}  // IndividualQStat class
