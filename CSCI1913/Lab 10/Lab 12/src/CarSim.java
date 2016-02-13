

// Carsim.java

// Priority Queue and Simulation

// CarSim is the driver routine for the Car Wash Simulation

// Uses PQ.java, Washer.java, Stat.java

public class CarSim {

    // public variables

    static PQ agenda = new PQ();

    public static Washer[] washerBay;  // the car washer
    
	public static int NUM_OF_WASHERS = 1;

    // methods

    public static void main(String args[]) {
    	
        int distArray[] = {20,40};

        washerBay = Washer.initialize(NUM_OF_WASHERS);    

        agenda.add(new CarMaker(40, distArray), 10
        		);

//      washer = new Washer();

        

        while (agenda.getCurrentTime() <= 15000000)

            agenda.remove().run();

        Stat.displayStats();

    }  // main method

    

}  // CarSim class
 