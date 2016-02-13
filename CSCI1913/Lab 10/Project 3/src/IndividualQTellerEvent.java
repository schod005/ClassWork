public class IndividualQTellerEvent implements Event {
	
	public IndividualQTellerEvent(){
		serviceTime = 0;
	}
	
	public IndividualQTellerEvent(double st){
		serviceTime = st;
	}

	public IndividualQTellerEvent(IndividualQTeller p,double st){
		parent = p;
		serviceTime = st;
	}
	
	public void run(){
		Customer customer;
		
		if(parent.isBusy()){
			IndividualQStat.updateServiceTimeStats(parent,serviceTime);
			IndividualQStat.updateBusyTimeStats(parent,BankSim.agenda.getCurrentTime());
		}
		else
			IndividualQStat.updateIdleTimeStats(parent,BankSim.agenda.getCurrentTime());
		
		if(parent.waitline.length() == 0)
			parent.setBusy(false);
		else{
			parent.setBusy(true);
			customer = (Customer) parent.waitline.remove();
			IndividualQStat.updateQueueStats(parent,BankSim.agenda.getCurrentTime(),parent.waitline.length());
			IndividualQStat.updateWaitTimeStats(parent,BankSim.agenda.getCurrentTime(),customer.getArrivalTime());
			serviceTime = customer.getServiceTime();
			BankSim.agenda.add(new IndividualQTellerEvent(parent,serviceTime),serviceTime);
		}	
	}
	
	private double serviceTime;
	private IndividualQTeller parent;
}
