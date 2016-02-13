
public class BinarySearchTree<T extends Comparable<T>> extends BinaryTree<T> {

	public void add(T data){
		TreeNode newTreeNode = new TreeNode(data);
		TreeNode current = new TreeNode();
		boolean added = false;
		if(root==null){
			root=newTreeNode;
			added=true;
		}
		current = root;
			while(!added){
				if(data.compareTo((T)current.getData())<=0){
					if(current.getLeft()==null){
						current.setLeft(newTreeNode);
						added=true;
					}
					else
						current=current.getLeft();
				}
				else{
					if(current.getRight()==null){
						current.setRight(newTreeNode);
						added=true;
					}
					else
						current=current.getRight();
				}
		}		
	}

	public void delete(T data){
		TreeNode current=root;
		TreeNode temp = null;
		boolean done = false;
		if(findDFS(data,root)==true){
			while (!done){
				if (data.compareTo((T)current.getData())>0){
					temp = current;
					current = current.getRight();
					if(current==null){
						done = true;
					}
					else if(data.compareTo((T)current.getData())==0 && current.getLeft()==null && current.getRight()==null){
						temp.setRight(null);
						done = true;
					}
				}
				else if (data.compareTo((T)current.getData())<0){
					temp = current;
					current = current.getLeft();
					if(current==null){
						done = true;
					}
					else if(data.compareTo((T)current.getData())==0 && current.getLeft()==null && current.getRight()==null){
						temp.setLeft(null);
						done = true;
					}
				}
				else if(data.compareTo((T)current.getData())==0){
					if(current.getLeft()==null && current.getRight()!=null){
						current = current.getRight();
						done = true;
					}
					else{
						temp = getRightMost(current);
						current.setData(temp.getData());
						done = true;
					}
				}
			}
		}
	}
	
	private TreeNode<T> getRightMost(TreeNode t){
		TreeNode prev = t;
		if(t.getLeft()== null){
			return null;
		}
		TreeNode current = t.getLeft();
		while(current.getRight()!=null){
			prev=current;
			current=current.getRight();
		}
		if(prev == t){
			prev.setLeft(null);
			return current;
		}
		else{
		prev.setRight(current.getLeft());
		return current;
		}
	}
	
	private String toStringHelper(TreeNode current){
		String s = "";
			if(current.getLeft()!=null){
			s+=toStringHelper(current.getLeft());
			}
			s+=current.getData()+",";
			if(current.getRight()!=null){
			s+=toStringHelper(current.getRight());
			}	
		
			return s;
	}
	
	public String toString(){
		String s = "";
		s=toStringHelper(root);
		return s.substring(0,s.length()-1);
	}
	
	public void print(){
		System.out.println(toString());
	}
}