import static org.junit.Assert.*;

import org.junit.Test;


public class MinHeapTest {

	
	@Test
	public void testMinHeapAddEmptyHeap(){
		MinHeap test = new MinHeap();
		test.add(10);
		assertEquals("Checks that a single object can be added to the min heap","10",test.toString());
	}
	
	@Test
	public void testMinHeapAddNonMinimumObject(){
		MinHeap test = new MinHeap();
		test.add(10);
		test.add(12);
		assertEquals("Checks that when adding a non-minimum object that it is placed below the already present minimum object","10,12",test.toString());
	}
	@Test
	public void testMinHeapAddNewMinimumObject(){
		MinHeap test = new MinHeap();
		test.add(10);
		test.add(8);
		test.add(7);
		test.add(6);
		test.add(3);
		assertEquals("Checks that objects are added in a manner that perserves the Min traits of the Min heap","3,6,8,10,7",test.toString());
	}
	
	@Test
	public void testMinHeapPop(){
		MinHeap test = new MinHeap();
		test.add(10);
		test.add(8);
		test.add(7);
		test.add(6);
		assertEquals("Calling pop on a Min heap will remove the largest (head) data point",6,test.pop().getData());
	}
	
	@Test
	public void testMinHeapHeapify(){
		MinHeap test = new MinHeap();
		test.add(10);
		test.add(8);
		test.add(7);
		test.add(6);
	}

}