
public class ListList<T extends Comparable<T>> implements List<T> {
	
	public ListList() {
		head = new ListNode<T>();
		head.setNext(null);
		sorted = false;
		duplicatesAllowed = true;
	}
	

	
	public ListList(char st){
		head = new ListNode<T>();
		head.setNext(null);
		sorted = true;
		sortType = st;
		duplicatesAllowed = true;
	}
	
	public ListList(boolean d){
		head = new ListNode<T>();
		head.setNext(null);
		sorted = false;
		duplicatesAllowed = d;
	}
	
	public ListList(boolean d,char st){
		head = new ListNode<T>();
		head.setNext(null);
		sorted = true;
		sortType = st;
		duplicatesAllowed = d;
	}

	@Override
	public int length() {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public T first() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public T last() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean lookup(T obj) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public T find(int n) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int find(T obj) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public void delete(T obj) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void delete(int n) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void add(T obj) {
		ListNode<T> newNode = new ListNode(obj);
		ListNode<T> temp = head;
		if (head.getNext()==null){
			head.setNext(newNode);
			return;
		}
		if(duplicatesAllowed == false){
			while(temp.getNext() != null){
				temp=temp.getNext();
				if(newNode.getData() == temp.getData()){
					return;
				}
			}
		}
		if (sorted == false)
		{
			while(temp.getNext() != null){
				temp=temp.getNext();
			}
			temp.setNext(newNode);
		}
		
		else if(sorted == true){
			boolean inserted = false;
			if(sortType == 'd'){
				temp=head.getNext();
				ListNode<T> prev = head;
				while(!inserted){
					int x = newNode.getData().compareTo(temp.getData());
					if(x>0){
						prev.setNext(newNode);
						newNode.setNext(temp);
						inserted = true;
					}
					else if(temp.getNext()==null){
						temp.setNext(newNode);
						inserted = true;
					}
					prev=prev.getNext();
					temp=temp.getNext();
				}
			}
			else if(sortType == 'a'){
				temp=head.getNext();
				ListNode<T> prev = head;
				while(!inserted){
					int x = newNode.getData().compareTo(temp.getData());
					if(x<0){
						prev.setNext(newNode);
						newNode.setNext(temp);
						inserted = true;
					}
					else if(temp.getNext()==null){
						temp.setNext(newNode);
						inserted = true;
					}
					prev=prev.getNext();
					temp=temp.getNext();
				}
			}
		}
	}

	@Override
	public T getNext() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public T getPrevious() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public void reset() {
		// TODO Auto-generated method stub
		
	}
	public void print(){
		ListNode<T> temp = head;
		while(temp.getNext() != null){
			temp=temp.getNext();
			System.out.println(temp.getData());
		}
	}
	boolean sorted;
	char sortType; // 'a' for ascending sort, 'd' for descending sort
	boolean duplicatesAllowed;
	private ListNode<T> head;
	
	public static void main(String[] args){
		Integer i4 = 4;
		Integer i5 = 5;
		Integer i6 = 6;
		Integer i7 = 7;
		
		System.out.println("Duplicates allowed, unsorted");
		ListList du = new ListList();
		System.out.println("Printing blank");
		du.print();
		du.add(i5);
		System.out.println("Added 5");
		du.print();
		du.add(i5);
		System.out.println("Added duplicate 5");
		du.print();
		du.add(i4);
		System.out.println("Added 4");
		du.print();
		du.add(i6);
		System.out.println("Added 6");
		du.print();
		System.out.println("");

		System.out.println("Duplicates allowed, ascending sorted");
		ListList da = new ListList('a');
		System.out.println("Printing blank");
		da.print();
		da.add(i5);
		System.out.println("Added 5");
		da.print();
		da.add(i5);
		System.out.println("Attempted to add duplicate of 5");
		da.print();
		da.add(i7);
		System.out.println("Added 7");
		da.print();
		da.add(i6);
		System.out.println("Added 6");
		da.print();
		da.add(i4);
		System.out.println("Added 4");
		da.print();
		System.out.println("");
		
		System.out.println("Duplicates allowed, descending sorted");
		ListList dd = new ListList('d');
		System.out.println("Printing blank");
		dd.print();
		dd.add(i5);
		System.out.println("Added 5");
		dd.print();
		dd.add(i5);
		System.out.println("Attempted to add duplicate of 5");
		dd.print();
		dd.add(i7);
		System.out.println("Added 7");
		dd.print();
		dd.add(i6);
		System.out.println("Added 6");
		dd.print();
		dd.add(i4);
		System.out.println("Added 4");
		dd.print();
		System.out.println("");
		
		System.out.println("Duplicates not allowed, unsorted");
		ListList ndu = new ListList(false);
		System.out.println("Printing blank");
		ndu.print();
		ndu.add(i5);
		System.out.println("Added 5");
		ndu.print();
		ndu.add(i5);
		System.out.println("Attempted to add duplicate of 5");
		ndu.print();
		ndu.add(i7);
		System.out.println("Added 7");
		ndu.print();
		ndu.add(i6);
		System.out.println("Added 6");
		ndu.print();
		ndu.add(i4);
		System.out.println("Added 4");
		ndu.print();
		System.out.println("");
		
		System.out.println("Duplicates not allowed, ascending sorted");
		ListList nda = new ListList(false,'a');
		System.out.println("Printing blank");
		nda.print();
		nda.add(i5);
		System.out.println("Added 5");
		nda.print();
		nda.add(i5);
		System.out.println("Attempted to add duplicate of 5");
		nda.print();
		nda.add(i7);
		System.out.println("Added 7");
		nda.print();
		nda.add(i6);
		System.out.println("Added 6");
		nda.print();
		nda.add(i4);
		System.out.println("Added 4");
		nda.print();
		System.out.println("");
		
		System.out.println("Duplicates not allowed, descending sorted");
		ListList ndd = new ListList(false,'d');
		System.out.println("Printing blank");
		ndd.print();
		ndd.add(i5);
		System.out.println("Added 5");
		ndd.print();
		ndd.add(i5);
		System.out.println("Attempted to add duplicate of 5");
		ndd.print();
		ndd.add(i7);
		System.out.println("Added 7");
		ndd.print();
		ndd.add(i6);
		System.out.println("Added 6");
		ndd.print();
		ndd.add(i4);
		System.out.println("Added 4");
		ndd.print();
		System.out.println("");
}
}