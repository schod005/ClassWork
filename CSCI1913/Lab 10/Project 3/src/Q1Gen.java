

// Q1Gen.java

// Queue implementation using a linked list of nodes (see NGen.java)

public class Q1Gen <T> implements QGen <T> {

    // constructor

    public Q1Gen () {}

    // selectors

    public void add(T o) {

        if (size == 0) {

          front = new NGen <T> (o, null);

          rear = front;

        }

        else {

          rear.setNext(new NGen <T> (o, null));

          rear = rear.getNext();

        }

        size++;

    }

    public T remove() {

        T answer;

        if (size == 0)

          return null;

        

        answer = front.getData();

        front = front.getNext();

        size--;

        if (size == 0)

          rear = null;

        return answer;

    }

    public int length() {

        return size;

    }

    private int size;

    private NGen <T> front;

    private NGen <T> rear;

}  // Q1Gen class
