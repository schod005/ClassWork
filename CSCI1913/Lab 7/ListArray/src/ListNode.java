
public class ListNode<T>  {
	
	public ListNode (){
		next = null;
		
	}
	
	public ListNode (T d){
		data = d;
		next= null;
	}
	
	public ListNode (T d, ListNode<T> p){
		data=d;
		next=p;
	}
	
	public T data;
	private ListNode<T> next;
}