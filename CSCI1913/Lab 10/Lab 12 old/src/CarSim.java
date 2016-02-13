// Carsim.java
// Priority Queue and Simulation
// CarSim is the driver routine for the Car Wash Simulation
// Uses PQ.java, Washer.java, Stat.java
public class CarSim {
    // public variables
    static PQ agenda = new PQ();
    static Washer washer;  // the car washer
    // methods
    public static void main(String args[]) {
        int distArray[] = {20, 40};
        
        agenda.add(new CarMaker(40, distArray), 10);
//      washer = new Washer();
        
        while (agenda.getCurrentTime() <= 1500000)
            agenda.remove().run();
        Stat.displayStats();
    }  // main method
    
}  // CarSim class
 