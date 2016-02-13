
public class ListArray<T> implements List<T> {

		public ListArray() {
			data = new ListNode[1];
			location = 0;
			size = 1;
		}
		
		public ListArray(int siz){
			data = new ListNode[siz];
			location = 0;
			size=siz;
			sorted = false;
			duplicatesAllowed = true;
		}
		
		public ListArray(int siz,char st){
			data = new ListNode[siz];
			location = 0;
			size=siz;
			sorted = true;
			sortType = st;
			duplicatesAllowed = true;
		}
		
		public ListArray(int siz,boolean d){
			data = new ListNode[siz];
			location = 0;
			size=siz;
			sorted = false;
			duplicatesAllowed = d;
		}
		
		public ListArray(int siz,char st, boolean d){
			data = new ListNode[siz];
			location = 0;
			size=siz;
			sorted = true;
			sortType = st;
			duplicatesAllowed = d;
		}
		
		private void resize(){
			size*=2;
			ListNode<T>[] Temp = new ListNode[size];
			for (int i=0;i<size/2;i++)
				Temp[i]=data[i];
			data=Temp;
			
		}
		
		public boolean add(ListNode<T> obj){
			if (sorted == false && duplicatesAllowed == true){	
				if (location==size)
					resize();
				data[location] = obj;
				location++;
			}
			if (sorted == false && duplicatesAllowed == false){	
				if (location==size)
					resize();
				for(int i=0;i<location;i++){
					if (data[i].data == obj.data)
						return false;		
				}
				data[location] = obj;
				location++;
			}
			if (sorted == true && sortType == 'a' && duplicatesAllowed == true)
			{
				if (location==size)
					resize();
				data[location] = obj;
				location++;
			}
			if (sorted == true && sortType == 'd' && duplicatesAllowed == true)
			{
				if (location==size)
					resize();
				data[location] = obj;
				location++;
			}
			if (sorted == true && sortType == 'a' && duplicatesAllowed == false)
			{
				if (location==size)
					resize();
				for(int i=0;i<location;i++){
					if (data[i].data == obj.data)
						return false;		
				}
				data[location] = obj;
				location++;
			}
			if (sorted == true && sortType == 'd' && duplicatesAllowed == false)
			{
				if (location==size)
					resize();
				for(int i=0;i<location;i++){
					if (data[i].data == obj.data)
						return false;		
				}
				data[location] = obj;
				location++;
			}
		/*	if (sorted == true && sortType == 'a' && duplicatesAllowed == true){
				boolean inserted = false;
				ListNode<T>[] newdata;
				if (location==size)
					resize();
				for(int i=0;i<location;i++)
				{
					if (inserted == false && something)
					{
						
					}
				}
				for(int i=0;i<location;i++)
				{
					data[i]=newdata[i];
				}
			}
			if (sorted == true && sortType == 'd' && duplicatesAllowed == true){
				boolean inserted = false;
				ListNode<T>[] newdata;
				if (location==size)
					resize();
				for(int i=0;i<location;i++)
				{
					if (inserted == false && something)
					{
						
					}
				}
				for(int i=0;i<location;i++)
				{
					data[i]=newdata[i];
				}
				
			}
			if (sorted == true && sortType == 'a' && duplicatesAllowed == false){
				for(int i=0;i<location;i++)
				{
					if (data[location]==obj)
						return false;
				}
				boolean inserted = false;
				ListNode<T>[] newdata;
				if (location==size)
					resize();
				for(int i=0;i<location;i++)
				{
					if (inserted == false && something)
					{
						
					}
				}
				for(int i=0;i<location;i++)
				{
					data[i]=newdata[i];
				}
				
			}
			if (sorted == true && sortType == 'd' && duplicatesAllowed == false){
				for(int i=0;i<location;i++)
				{
					if (data[location]==obj)
						return false;
				}
				boolean inserted = false;
				ListNode<T>[] newdata;
				if (location==size)
					resize();
				for(int i=0;i<location;i++)
				{
					if (inserted == false && something)
					{
						
					}
				}
				for(int i=0;i<location;i++)
				{
					data[i]=newdata[i];
				}
				
			}   
			*/
			return true;
		}
		
		public void print(){
			for (int i=0;i<location;i++)
				System.out.println(data[i].data);
		}
		
		private ListNode<T>[] data;
		int location;
		int size;
		boolean sorted;
		char sortType; // 'a' for ascending sort, 'd' for descending sort
		boolean duplicatesAllowed;

	public static void main(String[] args){
		Integer i1 = 5;
		String s1 = "Bob";
		ListArray blank = new ListArray();
		System.out.println("print blank");
		blank.print();
		System.out.println("End test\n");
		System.out.println("add blank");
		System.out.println(blank.add(new ListNode(i1)));
		System.out.println("End test\n");
		
		ListArray test = new ListArray(5);
		System.out.println("add same item, duplicates allowed");
		System.out.println(test.add(new ListNode(i1)));
		System.out.println(test.add(new ListNode(i1)));
		System.out.println("End test\n");
		System.out.println("print add same item, duplicates allowed");
		test.print();
		System.out.println("End test\n");
		
		ListArray duplicates = new ListArray(5,false);
		System.out.println("add same item, duplicates not allowed");
		System.out.println(duplicates.add(new ListNode(i1)));
		System.out.println(duplicates.add(new ListNode(i1)));
		System.out.println("End test\n");
		System.out.println("print add same item, duplicates not allowed");
		duplicates.print();
		System.out.println("End test\n");
		
		/*System.out.println("add same item, sorted ascending, duplicates allowed");
		ListArray sortatrue = new ListArray(5,'a',true);
		System.out.println(sortatrue.add(new ListNode(i1)));
		System.out.println(sortatrue.add(new ListNode(i1)));
		System.out.println("End test\n");
		
		System.out.println("add same item, sorted descending, duplicates allowed");
		ListArray sortdtrue = new ListArray(5,'d',true);
		System.out.println(sortdtrue.add(new ListNode(i1)));
		System.out.println(sortdtrue.add(new ListNode(i1)));
		System.out.println("End test\n");
		
		System.out.println("add same item, sorted ascending, duplicates not allowed");
		ListArray sortafalse = new ListArray(5,'a',false);
		System.out.println(sortafalse.add(new ListNode(i1)));
		System.out.println(sortafalse.add(new ListNode(i1)));
		System.out.println("End test\n");
		
		System.out.println("add same item, sorted descending, duplicates not allowed");
		ListArray sortdfalse = new ListArray(5,'d',false);
		System.out.println(sortdfalse.add(new ListNode(i1)));
		System.out.println(sortdfalse.add(new ListNode(i1)));
		System.out.println("End test\n");
		*/
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
		// TODO Auto-generated method stub
		
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
}