import static org.junit.Assert.*;

import org.junit.Test;


public class BinarySearchTreeTest {

	@Test
	public void testBinarySearchTreeAdd(){
		BinarySearchTree test= new BinarySearchTree();
		test.add(3);
		test.add(1);
		test.add(5);
		test.add(4);
		assertEquals("The four data fields should be added to the tree and toString should return them in increasing order.","1,3,4,5",test.toString());
	}
	
	@Test
	public void testBinarySearchTreeDeleteRoot(){
		BinarySearchTree test = new BinarySearchTree();
		test.add(3);
		test.add(1);
		test.add(5);
		test.add(4);
		test.delete(3);
		assertEquals("Calling delete on the root 3 should remove it and replace the root with root.getLeft() (1) in this case.","1,4,5",test.toString());
	}
	
	@Test
	public void testBinarySearchTreeDeleteNodeWithNoChildren(){
		BinarySearchTree test = new BinarySearchTree();
		test.add(3);
		test.add(1);
		test.add(5);
		test.add(4);
		test.delete(1);
		assertEquals("Calling delete on a node with no children should simply delete that root","3,4,5",test.toString());
	}
	
	@Test
	public void testBinarySearchTreeDeleteNodeWithOneChild(){
		BinarySearchTree test = new BinarySearchTree();
		test.add(3);
		test.add(1);
		test.add(5);
		test.add(4);
		test.delete(5);
		assertEquals("Calling delete on a node with one child will delete that node and replace it with its only child","1,3,4",test.toString());
	}
	
	@Test
	public void testBinarySearchTreeDeleteNodeWithTwoChildren(){
		BinarySearchTree test = new BinarySearchTree();
		test.add(3);
		test.add(1);
		test.add(5);
		test.add(4);
		test.add(6);
		test.delete(5);
		assertEquals("Calling delete on a node with two children will replace its data with the rightmost child on its left branch and delete that child","1,3,4,6",test.toString());
	}
	
}