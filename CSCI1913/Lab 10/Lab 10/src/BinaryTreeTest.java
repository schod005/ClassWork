import static org.junit.Assert.*;

import org.junit.Test;


public class BinaryTreeTest {

	@Test
	public void AddTest() {
		BinaryTree test = new BinaryTree(1);
		test.add(2);
		test.add(3);
		test.add(4);
		test.add(4);
		test.add(5);
		test.add(6);
		test.add(7);
		test.add(8);
		test.add(9);
		test.add(10);
		test.add(11);
		test.add(12);
		test.add(13);
		test.add("dog");
		test.add(15);
		test.add("dog");
		assertEquals("1,2,3,4,5,6,7,8,9,10,11,12,13,dog,15 must be added","1,2,3,4,5,6,7,8,9,10,11,12,13,dog,15",test.toString());
	}
	@Test
	public void findTest(){
		BinaryTree test = new BinaryTree(1);
		test.add(2);
		test.add(3);
		test.add(4);
		test.add(5);
		test.add(6);
		test.add(7);
		test.add(8);
		test.add(9);
		test.add(10);
		test.add(11);
		test.add(12);
		test.add(13);
		test.add(14);
		test.add(15);
		assertEquals("Checks if 2 is found in binary tree",true,test.findDFS(2,test.getRoot()));
		assertEquals("Checks if 56 is found in binary tree",false,test.findDFS(56,test.getRoot()));

	}
	@Test
	public void BinarySearchTreeadd(){
		BinarySearchTree test= new BinarySearchTree();
		test.add(3);
		test.add(1);
		test.add(5);
		test.add(4);
		test.print();
		assertEquals("adsadsfdsf","1,3,4,5",test.toString());
	}
	
	@Test
	public void BinarySearchTreedelete(){
		BinarySearchTree test= new BinarySearchTree();
		test.add(3);
		test.add(1);
		test.add(5);
		test.add(4);
		test.delete(4);
		test.print();
		assertEquals("adsadsfdsf","1,3,5",test.toString());
	}
	

}