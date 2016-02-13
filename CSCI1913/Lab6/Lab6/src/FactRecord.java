// FactRecord.java

public class FactRecord extends ActivationRecord {
        
        // *1* formal parameters
        private int n;  // the value of parameter n for this instance of factorial

        // *2* no local variables for factorial

        // *3* resume location
        private int line = 0;

        // constructor for new instance of an activation record
        public FactRecord(int newN) {
            n = newN;
        }

        // *4* reference to code for fact is kept within the run() method
        public void run() {

            switch (line) {
                case 0:  // entry point
                         if (n == 0) {
                           FactR.returnedValue = 1;  // set return global return value
                         FactR.s.pop();  // this call done, remove frame from stack
                           return;
                         }
                         // if we don't quit, we will fall into the "else" case below
                         // else clause from fact
                         FactR.s.push(new FactRecord(n - 1));
                         line = 1;  // set resume point after recursive call below
                         return;
                case 1:  // resume point after we have a factorial value for the n-1 case
                         // no need to set resume line, because this call is done after this
                         FactR.returnedValue = n * FactR.returnedValue;  // set global return value
                         FactR.s.pop();  // this call done, remove frame from stack
                         return;
                default: System.out.println("\nWe should not get here.");
            }
        }
}