// StackGen.java
// A Possible Generic Stack Interface
// Which of the methods are absolutely necssary, which are nice to have,
// and which are redundant?
public interface StackGen <T> {
// Interface for a Generic Stack
    public void push(T o);
    /* adds an object o to the top of a stack by placing it in the 
       reverse order of arrival relative to other items added to the 
       stack; that is, last in, first out (LIFO) */
    public T pop();
 
    /* removes and returns the object placed in a stack most recentlt
       relative to any other items presently in the stack */
    public T top();
    /* returns the Object placed in a stack most recently, or null
       if the stack contains no items */
    public boolean isEmpty();
    /* returns true when a stack currently contains no items, false 
       otherwise */
}  // StackGen Interface