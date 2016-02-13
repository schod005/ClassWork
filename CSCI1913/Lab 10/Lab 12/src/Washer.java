

// Washer.java

// Priority Queue and Simuluation

// Washer is the class that models the car washer and it's waiting line

// The method run() simulates the behavior of the washer.

// This implements the Event interface (Event.java)

public class Washer {

    // constructors
	
	public Washer(){
		busy = false;
	}

    public Washer(int n) {
    	busy = false;    	
    }
    
    public static Washer[] initialize (int num){
    	Washer[] temp = new Washer[num];
    	for(int i = 0;i<num;i++){
    		temp[i]=new Washer(i);
    	}
    	numWashers=num;
    	return temp;
    }

    static Q1Gen <Car> waitline = new Q1Gen <Car>();  // one queue for the washer's waiting cars

    // methods

    public static void enter(Car c) {

        waitline.add(c);
        Stat.updateQueueStats(CarSim.agenda.getCurrentTime(),waitline.length());       
    }

    public boolean isBusy() {
        return busy;
    }
    
    public static Washer findOpen(){
    	int i = 0;
    	while(i<numWashers&&CarSim.washerBay[i].isBusy()){
    		i++;
    	}
    	if(i<numWashers){
    		return CarSim.washerBay[i];
    	}
    	else return null;
    
    }
    
    // public variables
    public void setBusy(boolean b){
    	busy = b;
    }

 // instance variable has current car's service
    private static int numWashers;
    private boolean busy; 

}  // Washer class
