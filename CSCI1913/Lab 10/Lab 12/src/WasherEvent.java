
public class WasherEvent implements Event{

	public WasherEvent() {
        servTime = 0;

    }
	
	public WasherEvent(double st){
		servTime = st;
	}
	
	public WasherEvent(Washer a,double st){
		servTime = st;
		parent = a;
	}
	 
	    
    public void run() {

        Car car;

        if (parent.isBusy()) {  // this instance invoked because a wash finished

          Stat.updateServiceTimeStats(servTime);

          Stat.updateBusyTimeStats(CarSim.agenda.getCurrentTime());

        }
        
        else
        	Stat.updateIdleTimeStats(CarSim.agenda.getCurrentTime());
        
        if(Washer.waitline.length() == 0){
        	parent.setBusy(false);
        }
        
        else{

        parent.setBusy(true);   // start on next car in queue

        car = (Car) Washer.waitline.remove();

        Stat.updateQueueStats(CarSim.agenda.getCurrentTime(),

                                Washer.waitline.length());

        Stat.updateWaitTimeStats(CarSim.agenda.getCurrentTime(),

                                   car.getArrivalTime());

        servTime = car.getServiceTime();

        CarSim.agenda.add(new WasherEvent(parent,servTime), 

                            servTime);
        }

    }  // run method

		private double servTime;
		
		private Washer parent;


	
}
