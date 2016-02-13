import static org.junit.Assert.*;

import org.junit.Test;


public class MaxHeapTest {
	
	public void testMaxHeapAddToEmptyHeap(){
		MaxHeap test = new MaxHeap();
		test.add(10);
		assertEquals("Checks that a single object can be added to the max heap","10",test.toString());
	}
	
	@Test
	public void testMinHeapAddNonMaximumObject(){
		MaxHeap test = new MaxHeap();
		test.add(10);
		test.add(8);
		assertEquals("Checks that when adding a non-maximum object that it is placed below the already present maximum object","10,8",test.toString());
	}
	
	@Test
	public void testMaxHeapAddNewMaximumObject(){
		MaxHeap test = new MaxHeap();
		test.add(10);
		test.add(8);
		test.add(7);
		test.add(6);
		test.add(55);
		assertEquals("Checks that objects are added in a manner that preserves the max traits of the max heap","55,10,7,6,8",test.toString());
	}
	
	@Test
	public void testMaxHeapPop(){
		MaxHeap test = new MaxHeap();
		test.add(10);
		test.add(8);
		test.add(7);
		test.add(6);
		assertEquals("Calling pop on a max heap will remove the largest (head) data point",10,test.pop().getData());
	}
	
	@Test
	public void testMaxHeapHeapify(){
		MaxHeap test = new MaxHeap();
		test.add(10);
		test.add(8);
		test.add(7);
		test.add(6);

	}

}