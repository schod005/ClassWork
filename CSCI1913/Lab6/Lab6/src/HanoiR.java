
public class HanoiR {
    public static Stack1Gen <HanoiRecord> h = new Stack1Gen<HanoiRecord>();

    public static int count = 0;
    
	public static void main(String args[]) {
		 h.push(new HanoiRecord(3,'a','c','b'));
	        while(!h.isEmpty()) 
	        {  // system loop goes until stack is empty
	            h.top().run();
	        }  // end system loop
	        System.out.println("Number of moves: "+HanoiR.count);
	} // main method
}