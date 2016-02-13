
public class ListNode<T>  {
	
	public ListNode (){
		next = null;
		
	}
	
	public ListNode (T d){
		data = d;
		next=null;
	}
	public ListNode (T d, ListNode<T> n){
		data = d;
		next = n;
	}
	
	public void setNext(ListNode<T> n){
		next = n;
	}
	
	public ListNode<T> getNext(){
		return next;
	}
	
	public void setData(T d){
		data = d;
	}
	
	public T getData(){
		return data;
	}
	
	
	
	private T data;
	private ListNode<T> next;
}