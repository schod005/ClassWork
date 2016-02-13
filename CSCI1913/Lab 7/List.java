
public interface List<T> {
	int length(); //returns the count of data nodes currently in the list
	T first(); // returns the data from the first data node in the List
	T last(); // returns the data from the last data node in the List
	
	boolean lookup(T obj);
	// searches the List for an Object equal to obj and returns
	// true if found, false otherwise.

	T find(int n);
	// counting from the start of the List, returns the *data* from the
	// nth node in the List; if the List is not at least n long, 
	// null is returned; find(1) returns the first data; 
	// find(0) and find(-n) return null

	int find(T obj);
	// returns the position where the obj is found in the List.
	// 0 is returned if obj is not present in the List. 
	// The two find() methods are inverses of each other, that is
	// db.find(db.find(5)) --> 5

	void delete(T obj);
	// removes the node containing the data in obj from the List;
	// if no such node exists, nothing happens

	void delete(int n);
	// removes the nth node from the List; if there are not at least
	// n nodes, nothing happens; delete(0) and delete(-n) do nothing

	void add(T obj);
	// inserts a new node with data obj into the List according to the
	// parameters set at the construction of this List instance.

	T getNext();
	// using an internally maintained pointer, getNext()
	// returns the *data* Object at the start of the List the first
	// time it is called, the next item the second time it is called,
	// and so on; if the List is empty or the last item in the List
	// has already been returned, null is returned.

	T getPrevious();
	// using an the same internally maintained pointer as getNext(),
	// getPrevious() returns the *data* object in the List immediately 
	// preceding the *data* object that was returned previously by
	// either getNext() or getPrevious(); if there is no previous 
	// *data* object returned or the first *data* object was most 
	// recently returned, null is returned.

	void reset();
	// resets the internal List pointer used by getNext() and
	// getPrevious() so that getNext() returns the first *data* 
	// object in the List the next time it is called.
}
