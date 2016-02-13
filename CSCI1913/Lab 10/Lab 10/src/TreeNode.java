
public class TreeNode<T> {
	
	public TreeNode(){
	}
	
	public TreeNode(T data){
		this.data = data;
		right = null;
		left = null;
	}
	
	public T getData(){
		return data;
	}
	
	public void setData(T data){
		this.data=data;
	}
	
	public void setRight(TreeNode right){
		this.right = right;
	}
	
	public TreeNode getRight(){
		return right;
	}
	
	public void setLeft(TreeNode left){
		this.left = left;
	}
	
	public TreeNode getLeft(){
		return left;
	}
	
	public TreeNode getParent(){
		return parent;
	}
	
	public void setParent(TreeNode a){
		parent=a;
	}
	
	T data;
	TreeNode right;
	TreeNode left;
	TreeNode parent;
}