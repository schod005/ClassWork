

// QGen.java

// Generic Queue Interface

public interface QGen <T> {

// Interface for a Queue

    void add(T o);

    /* adds an object o to a queue placing it in the order of arrival 

       relative to other items added to the queue--first in, first out

       (FIFO) */

    T remove();

 

    /* removes and returns the object placed in a queue prior

       to any other items presently in the queue */

    int length();

    /* returns the integer quantity of items currently present in the 

       queue */ 

}  // QGen Interface
