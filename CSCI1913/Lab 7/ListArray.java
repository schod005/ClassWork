
public class ListArray<T> {

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
			if (sorted == true && sortType == 'a' && duplicatesAllowed == true){
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
			return true;
		}
		
		public void print(){
			for (int i=0;i<location;i++)
				System.out.println(data[i]);
		}
		
		private ListNode<T>[] data;
		int location;
		int size;
		boolean sorted;
		char sortType; // 'a' for ascending sort, 'd' for descending sort
		boolean duplicatesAllowed;

	public static void main(String[] args){
		Integer i1 = 5;
		ListArray blank = new ListArray();
		blank.print();
		blank.add(new ListNode(i1));	
		
		ListArray test = new ListArray(5);
		test.add(new ListNode(i1));
		test.add(new ListNode());
		test.print();
		
		ListArray duplicates = new ListArray(5,false);
		System.out.println(duplicates.add(new ListNode(i1)));
		System.out.println(duplicates.add(new ListNode(i1)));
		duplicates.print();
		
}
}