
public class HanoiRecord extends ActivationRecord {
        
        // *1* formal parameters
        private int n;  // the value of parameter n for this instance 
        char source;
        char dest;
        char temp;

        // *2* no local variables used

        // *3* resume location
        private int line = 0;

        // constructor for new instance of an activation record
        public HanoiRecord(int newN,char s,char d,char t) {
            n = newN;
            source = s;
            temp = t;
            dest = d;
        }

        // *4* reference to code for fact is kept within the run() method
        public void run() {
            switch (line) {
                case 0:  // entry point
                         if (n == 1) {     
                        	 HanoiR.count++;
                        	 System.out.println("Step #"+HanoiR.count+": Move disk " + n+" from " + source + " to " + dest);
                        	 HanoiR.h.pop();  // this call done, remove frame from stack
                        	 
                        	 return;
                         }
                         // if we don't quit, we will fall into the "else" case below
                         // else clause from fact
                         line = 1;  // set resume point after recursive call beloW
                     	 HanoiR.h.push(new HanoiRecord(n-1,source,temp,dest));
                     	 return;
                case 1:  
                	HanoiR.count++;
               	 	System.out.println("Step #"+HanoiR.count+": Move disk " + n+" from " + source + " to " + dest);
                	line = 2;
                	HanoiR.h.push(new HanoiRecord(n-1,temp,dest,source));
            		return;
                case 2:
                	HanoiR.h.pop();
                    return;
                default: System.out.println("\nWe should not get here.");
            }

        }
}