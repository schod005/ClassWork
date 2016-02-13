import java.util.LinkedList;
import java.util.Queue;


public class MaxHeap<T extends Comparable<T>> extends BinaryTree<T> {

	public void add(T data){
		T tempt = data;
		if(root == null){
			TreeNode<T> newTreeNode = new TreeNode<T>(tempt);
			root = newTreeNode;
			return;
		}
		TreeNode<T> current = root;
		if(data.compareTo((T)root.getData())>0){
			tempt = (T)root.getData();
			root.setData(data);
		}
		TreeNode<T> newTreeNode = new TreeNode<T>(tempt);
		Queue<TreeNode<T>> queue = new LinkedList<TreeNode<T>>();
		boolean added = false;
		while(!added){
			if(current.getLeft() == null){
				newTreeNode.setParent(current);
				current.setLeft(newTreeNode);
				added = true;
			}
			else if(current.getRight() == null){
				newTreeNode.setParent(current);
				current.setRight(newTreeNode);
				added = true;
			}
			queue.add(current.getLeft());
			queue.add(current.getRight());
			current = (TreeNode<T>)queue.remove();
		}
		heapSort(newTreeNode);
		}
	
	private void heapSort(TreeNode start){
		TreeNode temp = start;
		TreeNode parent = start.getParent();
		while(parent != null){
			T pdata = (T)parent.getData();
			if(((Comparable<T>) start.getData()).compareTo(pdata)>0){
				parent.setData(temp.getData());
				temp.setData(pdata);
				return;
			}
			temp=temp.getParent();
			parent=parent.getParent();
		}
		
	}
	
	public void heapify(){
		heapifyHelper(root);
	}
	
	private void heapifyHelper(TreeNode<T> top){
		if(top == null){
			return;
		}
		TreeNode left = top.getLeft();
		TreeNode right = top.getRight();
		if(right.getData()==null){
			top.setRight(null);
		}
		T largest = (T)top.getData();
		T temp = null;
		char leftOrRight = 'n';
		if(top.getLeft() != null){
			if(((Comparable<T>) left.getData()).compareTo((T) top.getData())<0){
				largest = (T)left.getData();
				leftOrRight = 'l';
			}
		}
		else largest = (T)top.getData();
		if(top.getRight() != null){
			if(((Comparable<T>) right.getData()).compareTo(largest)<0){
			largest = (T)right.getData();
			leftOrRight = 'r';
		}
		if(largest.compareTo((T)top.getData())!=0){
			temp = (T)top.getData();
			top.setData(largest);
			if(leftOrRight == 'l'){
				left.setData(temp);
				heapifyHelper(top.getLeft());
			}
			else{
				right.setData(temp);
				heapifyHelper(top.getRight());
			}
		}
		}
	}
	
	public TreeNode pop(){
		TreeNode rt = new TreeNode(root.getData());
		Queue queue = new LinkedList();
		TreeNode current = root;
		TreeNode prev = root;
		queue.add(root);
		boolean removed = false;
		while(!removed){
			prev = current;
			current=(TreeNode)queue.remove();
			if(current.getLeft() ==null && current.getRight() == null){
				root.setData((T)current.getData());
				removed = true;
			}
			queue.add(current.getLeft());
			queue.add(current.getRight());
		}
		current.setData(null);
		heapify();
		return rt;
	}
}