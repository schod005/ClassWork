public class CustomerMaker implements Event {
	public CustomerMaker(int i, int[] servDist){
		interval = i;
		serviceDistribution = new int[servDist.length];
		System.arraycopy(servDist,0,serviceDistribution,0,servDist.length);
	}
	
	private double getArrivalTime(){
		double x = Math.random(); // x is a random double from 0.0 to 1.0
		if(x<0.1) //10% of the time - 75% above average arrival interval
			return interval+0.75*interval;
		else if(x<0.3) //20% of the time - 50% above average arrival interval
			return interval+0.50*interval;
		else if(x<0.5) //20% of the time - 20% above average arrival interval
			return interval+0.20*interval;
		else if(x<0.7) //20% of the time - 20% below average arrival interval
			return interval-0.20*interval;
		else if(x<0.9) //20% of the time - 50% below average arrival interval
			return interval-0.50*interval;
		else // 10% of the time - 75% below average arrival interval
			return interval-0.75*interval;
		}
	
	private double chooseServiceTime(){
		return serviceDistribution[(int)Math.floor((serviceDistribution.length-1)*Math.random()+0.5)];
	}
	
	
	public void run() {
		
		BankSim.agenda.add(new CustomerMaker(interval,serviceDistribution),getArrivalTime());
		Customer newCustomer = new Customer(BankSim.agenda.getCurrentTime(),chooseServiceTime());
		
	}
	
	private int interval;
	private int[] serviceDistribution;
}
