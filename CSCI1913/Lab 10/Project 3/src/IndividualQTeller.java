public class IndividualQTeller {

	public IndividualQTeller(){
		busy = false;
	}
	
	public IndividualQTeller(int n){
		busy = false;
		index = n;
	}
	
	public static IndividualQTeller[] initialize (int n){
		IndividualQTeller[] temp = new IndividualQTeller[n];
		for(int i = 0; i<n;i++)
			temp[i] = new IndividualQTeller(i);
		numberOfNonPriorityTellers = n;
		if(BankSim.EXPRESS_AVAILABLE){
			priority = temp[n-1];
			numberOfNonPriorityTellers--;
		}
		currentShortIndex = 0;
		currentEmptyIndex = 0;
		return temp;
	}
	
	public static void enter(Customer c){
		IndividualQTeller openTeller = findOpenTeller();
		if(openTeller!=null){
			openTeller.waitline.add(c);
			IndividualQStat.updateQueueStats(openTeller,BankSim.agenda.getCurrentTime(),openTeller.waitline.length());
		}
		else if (BankSim.EXPRESS_AVAILABLE&&c.getServiceTime()<=BankSim.PRIORITY_LINE_MAXIMUM_TIME&&priority.waitline.length()<=findShortestLine().waitline.length()){
			priority.waitline.add(c);
			SharedQStat.updateQueueStats(BankSim.agenda.getCurrentTime(),priority.waitline.length());
		}
		else{
			openTeller=findShortestLine();
			openTeller.waitline.add(c);
			IndividualQStat.updateQueueStats(openTeller,BankSim.agenda.getCurrentTime(),openTeller.waitline.length());
		}
	}
	
	public static IndividualQTeller findShortestLine(){
		IndividualQTeller shortest = BankSim.iTellerList[0];
		IndividualQTeller current = null;
		int count = 0;
		while(count<numberOfNonPriorityTellers){
			current = BankSim.iTellerList[currentShortIndex];
			if(current.waitline.length()<shortest.waitline.length()){
				shortest = current;
			}
			count++;
			currentShortIndex++;
			if(currentShortIndex==numberOfNonPriorityTellers){
				currentShortIndex=0;
			}
		}
		return shortest;
	}
	
	public static IndividualQTeller findOpenTeller(){
		int count = 0;
		while(count<numberOfNonPriorityTellers&&BankSim.iTellerList[currentEmptyIndex].isBusy()){
			count++;
			currentEmptyIndex++;
			if(currentEmptyIndex==numberOfNonPriorityTellers){
				currentEmptyIndex = 0;
			}
		}
		if(count<numberOfNonPriorityTellers)
			return BankSim.iTellerList[currentEmptyIndex];
		else return null;
	}
	
	public boolean isBusy(){
		return busy;
	}
	
	public static boolean isPriorityBusy(){
		return priority.busy;
	}
	
	public static IndividualQTeller getPriority(){
		return priority;
	}
	public void setBusy(boolean b){
		busy = b;
	}
	
	public int getIndex(){
		return index;
	}
	
	Q1Gen <Customer> waitline = new Q1Gen <Customer>();
	private static IndividualQTeller priority;
	private static int numberOfNonPriorityTellers;
	private static int currentEmptyIndex;
	private static int currentShortIndex;
	private boolean busy;
	private int index;
	
	
}
