public class SharedQTellerEvent implements Event {
	
	public SharedQTellerEvent(){
		serviceTime = 0;
	}
	
	public SharedQTellerEvent(double st){
		serviceTime = st;
	}
	
	public SharedQTellerEvent(SharedQTeller p,double st){
		parent = p;
		serviceTime = st;
	}
	
	public void run(){
		Customer customer;
		
		if(parent.isBusy()){
			SharedQStat.updateServiceTimeStats(parent,serviceTime);
			SharedQStat.updateBusyTimeStats(parent,BankSim.agenda.getCurrentTime());
		}
		else
			SharedQStat.updateIdleTimeStats(parent,BankSim.agenda.getCurrentTime());
		
		if(SharedQTeller.waitline.length() == 0)
			parent.setBusy(false);
		else{
			parent.setBusy(true);
			customer = (Customer) SharedQTeller.waitline.remove();
			SharedQStat.updateQueueStats(BankSim.agenda.getCurrentTime(),SharedQTeller.waitline.length());
			SharedQStat.updateWaitTimeStats(parent,BankSim.agenda.getCurrentTime(),customer.getArrivalTime());
			serviceTime = customer.getServiceTime();
			BankSim.agenda.add(new SharedQTellerEvent(parent,serviceTime),serviceTime);
		}	
	}
	
	private double serviceTime;
	private SharedQTeller parent;
}
