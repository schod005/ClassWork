public class Customer {
	public Customer(double at,double st){
		arrivalTime = at;
		serviceTime = st;
		IndividualQTeller.enter(this);
		SharedQTeller.enter(this);
		IndividualQTeller openIndividualTeller = IndividualQTeller.findOpenTeller(); // checks to see if a teller is idle
		if(openIndividualTeller != null) //if no teller is open, findOpenTeller returns null, else it returns the first open teller
			BankSim.agenda.add(new IndividualQTellerEvent(openIndividualTeller,st),0);
		else if(BankSim.EXPRESS_AVAILABLE&&serviceTime<=BankSim.PRIORITY_LINE_MAXIMUM_TIME&&!IndividualQTeller.isPriorityBusy())
			BankSim.agenda.add(new IndividualQTellerEvent(IndividualQTeller.getPriority(),st),0);
		SharedQTeller openSharedTeller = SharedQTeller.findOpenTeller();
		if(openSharedTeller != null)
			BankSim.agenda.add(new SharedQTellerEvent(openSharedTeller,st),0);
		else if(BankSim.EXPRESS_AVAILABLE&&serviceTime<=BankSim.PRIORITY_LINE_MAXIMUM_TIME&&!SharedQTeller.isPriorityBusy())
			BankSim.agenda.add(new SharedQTellerEvent(SharedQTeller.getPriority(),st),0);

	}
	
	public double getArrivalTime(){
		return arrivalTime;
	}
	
	public double getServiceTime(){
		return serviceTime;
	}
	private double arrivalTime;
	private double serviceTime;
}
