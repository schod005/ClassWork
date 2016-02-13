
// Washer.java
// Priority Queue and Simuluation
// Washer is the class that models the car washer and it's waiting line
// The method run() simulates the behavior of the washer.
// This implements the Event interface (Event.java)
public class Washer implements Event {
    // constructors
    public Washer() {
        servTime = 0;
    }
    public Washer(double st) {
        servTime = st;
    }
    // public variables
    static Q1Gen <Car> waitline = new Q1Gen <Car>();  // one queue for the washer's waiting cars
    // methods
    public static void enter(Car c) {
        waitline.add(c);
        Stat.updateQueueStats(CarSim.agenda.getCurrentTime(),
                              waitline.length());
    }
    public static boolean isBusy() {
        return busy;
    }
    public void run() {
        Car car;
        if (busy) {  // this instance invoked because a wash finished
          Stat.updateServiceTimeStats(servTime);
          Stat.updateBusyTimeStats(CarSim.agenda.getCurrentTime());
        }
        else  // this instance invoked because a new car arrived at idle wash
          Stat.updateIdleTimeStats(CarSim.agenda.getCurrentTime());
        if (waitline.length() == 0) {
          busy = false;  // do nothing until notified of a new car arrival
        }
        else {
          busy = true;  // start on next car in queue
          car = (Car) waitline.remove();
          Stat.updateQueueStats(CarSim.agenda.getCurrentTime(),
                                waitline.length());
          Stat.updateWaitTimeStats(CarSim.agenda.getCurrentTime(),
                                   car.getArrivalTime());
          servTime = car.getServiceTime();
          CarSim.agenda.add(new Washer(servTime), 
                            servTime);
        }
    }  // run method
          
    // private variables
    private static boolean busy;  // one status for the washer 
    private double servTime;  // instance variable has current car's service
                              // time
}  // Washer class
 