

// Car.java

// Priority Queue and Simulation

// Car class the represents cars in the carwash simulation

// Car objects contain the time they were created and their service time.

// Car objects are immediately queued in the washer queue.

// Car objects are passive except in constructor (creation)

public class Car {

    // constructor

    public Car(double t, double servTime) {

        arrivalTime = t;

        serviceTime = servTime;

        Washer.enter(this);
        Washer currentWasher = Washer.findOpen();
       if (currentWasher!=null){
        // Stat.updateIdleTimeStats(CarSim.agenda.getCurrentTime());
         // currentWasher.setBusy(true);
          CarSim.agenda.add(new WasherEvent(currentWasher,servTime),0);
       }

    }

    public double getArrivalTime() {

        return arrivalTime;

    }

    public double getServiceTime() {

        return serviceTime;

    }

    // private variables

         

    private double arrivalTime;

    private double serviceTime;

}  // Car class
