// Stat.java

// Priority Queue and Simulation

// Statistics class for Car Simulation

public class Stat {

    // public methods

    public static void updateQueueStats(double time, int qlen) {

        

        if (qlen > maxQLength)

          maxQLength = qlen;

        averageQLength += oldQLength * (time - lastQUpdateTime);

        totalTime += time - lastQUpdateTime;

        lastQUpdateTime = time;

        oldQLength = qlen;

    }

    public static void updateBusyTimeStats(double time) {

        busyTime += time - lastUpdateTime;

        lastUpdateTime = time;

    }        

    public static void updateIdleTimeStats(double time) {

        

        idleTime += time - lastUpdateTime;

        lastUpdateTime = time;

    }

    public static void updateServiceTimeStats(double st) {

   

        averageServiceTime += st;

    }

    public static void updateWaitTimeStats(double time, double enterTime) {

    

        double wait = time - enterTime;

        if (wait > maxWait)

          maxWait = wait;

        averageWait += wait;

        count++;  // another leaves the waiting queue

    } 

    public static void displayStats() {

        System.out.println("\n** Simulation Results **\n");

        System.out.println(" Calculated Simulation Time: " + totalTime);

        System.out.println(" Idle Time: " + idleTime);

        System.out.println(" Busy Time: " + busyTime);

        System.out.println(" (Busy Time based on service time: " + 

                                               averageServiceTime + ")\n");

        System.out.println(" Maximum Queue Length: " + maxQLength);

        System.out.println(" Avg. Queue Length: " + averageQLength/totalTime);

        System.out.println(" Maximum Waiting Time: " + maxWait);

        System.out.println(" Avg. Waiting Time for cars through the queue: " +

                                                 averageWait/count);

        System.out.println(" Avg. Service Time: " + averageServiceTime/

                                                       count);

        System.out.println(" Number of cars through system: " + count);

        System.out.println("\n");

    }  // displayStats

    // private variables

    private static double lastUpdateTime;

    private static int oldQLength;

    private static double lastQUpdateTime;

    

    private static int count;

    private static double totalTime;

    private static double busyTime;

    private static double idleTime;

    private static double maxWait;

    private static double averageWait;

    private static int maxQLength;

    private static double averageQLength; 

    private static double averageServiceTime;

}  // Stat class