// Segment.java
// Priority Queue and Simulation
// Segment class used in priority queue (PQ.java)
// Uses queue class Q1Gen.java
public class Segment {
    private double time;
    private Q1Gen <Event> q;
    private Segment next;
    // constructor
    public Segment(double t) {
        time = t;
        q = new Q1Gen <Event> ();
        next = null;
    }
    // methods
    public double getTime() {
        return time;
    }
    public Q1Gen <Event> getEvents() {
        return q;
    }
    public Segment getNext() {
        return next;
    }
    public void setNext(Segment nextSegment) {
        next = nextSegment;
    }
}  // Segment class
 