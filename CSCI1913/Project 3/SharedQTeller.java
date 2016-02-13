public class SharedQTeller {

	public SharedQTeller(){
		busy = false;
	}
	
	public SharedQTeller(int n){
		busy = false;
		index = n;
	}
	
	public static SharedQTeller[] initialize (int n){
		SharedQTeller[] temp = new SharedQTeller[n];
		for(int i = 0; i<n;i++)
			temp[i] = new SharedQTeller(i);
		numberOfNonPriorityTellers = n;
		if(BankSim.EXPRESS_AVAILABLE){
			priority = temp[n-1];
			numberOfNonPriorityTellers--;
		}
		currentIndex = 0;
		return temp;
	}
	
	public static void enter(Customer c){
		if(BankSim.EXPRESS_AVAILABLE&&c.getServiceTime()<=BankSim.PRIORITY_LINE_MAXIMUM_TIME && findOpenTeller()==null&&priorityWaitline.length()<=waitline.length()){
			priorityWaitline.add(c);
			SharedQStat.updateQueueStats(BankSim.agenda.getCurrentTime(),priorityWaitline.length());
		}
		else{
			waitline.add(c);
			SharedQStat.updateQueueStats(BankSim.agenda.getCurrentTime(),waitline.length());
		}
	}
	
	public static SharedQTeller findOpenTeller(){
		int count = 0;
		while(count<numberOfNonPriorityTellers&&BankSim.sTellerList[currentIndex].isBusy()){
			count++;
			currentIndex++;
			if(currentIndex==numberOfNonPriorityTellers){
				currentIndex = 0;
			}
		}
		if(count<numberOfNonPriorityTellers)
			return BankSim.sTellerList[currentIndex];
		else return null;
	}
	
	public boolean isBusy(){
		return busy;
	}
	
	static public boolean isPriorityBusy(){
		return priority.busy;
	}
	
	static public SharedQTeller getPriority(){
		return priority;
	}
	
	public void setBusy(boolean b){
		busy = b;
	}
	
	public int getIndex(){
		return index;
	}
	
	static Q1Gen <Customer> waitline = new Q1Gen <Customer>();
	static Q1Gen <Customer> priorityWaitline = new Q1Gen <Customer>();
	private static SharedQTeller priority;
	private static int numberOfNonPriorityTellers;
	private static int currentIndex;
	private boolean busy;
	private int index;
	
	
}
