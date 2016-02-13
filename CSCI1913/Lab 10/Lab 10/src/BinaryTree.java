
public class BinaryTree<T> {
	
	public BinaryTree(){
	}
	
	public BinaryTree(T data){
		root = new TreeNode(data);
	}
	
	public void add(T data){
		TreeNode newTreeNode = new TreeNode(data);
		TreeNode current = new TreeNode();
		Q1Gen queue = new Q1Gen();
		current = root;
		boolean added = false;
		if(findDFS(data,root)==false)
			while(!added){
				if(current.getLeft() == null){
					current.setLeft(newTreeNode);
					added = true;
				}
				else if(current.getRight() == null){
					current.setRight(newTreeNode);
					added = true;
				}
				queue.add(current.getLeft());
				queue.add(current.getRight());
				current = (TreeNode)queue.remove();
		}		
	}
	public boolean findDFS(T data,TreeNode current){
		boolean found = false;
		if(current.getData() == data){
			return true;
		}
		else{
			if(current.getLeft()!=null){
			found = findDFS(data,current.getLeft());
			}
			if(found == true){}
			else if(current.getRight()!=null){
			found = findDFS(data,current.getRight());
			}
			if(found == true){}
		}
		return found;
	}
	
	public String toString(){
		String data1="";
		TreeNode current = new TreeNode();
		Q1Gen queue = new Q1Gen();
		current = root;
		if(current.getLeft() == null){
			data1+=current.getData()+",";
			return data1.substring(0,data1.length()-1);
		}
		else if(current.getRight() == null){
			data1+=current.getData()+",";
			data1+=current.getLeft().getData()+",";
			return data1.substring(0,data1.length()-1);
		}
		boolean added = false;
		while(!added){
			if(current.getLeft() == null){
				added = true;
			}
			else if(current.getRight() == null){
				added = true;
			}
			queue.add(current.getLeft());
			queue.add(current.getRight());
			data1+=current.getData()+",";
			current = (TreeNode)queue.remove();	
			}
		while(current != null){
			data1+=current.getData()+",";
			current = (TreeNode)queue.remove();
		}
		
		return data1.substring(0,data1.length()-1);
		}		
	
	public void print(){
		System.out.println(toString());
	}
	
	public TreeNode getRoot(){
		return root;
	}
	
	TreeNode root;
}