
public class ListArray<T extends Comparable<T>> {

		public ListArray() {
			larray = new ListNode[1];
			location = 0;
			size = 1;
		}
		
		public ListArray(int siz){
			larray = new ListNode[siz];
			location = 0;
			size=siz;
			sorted = false;
			duplicatesAllowed = true;
		}
		
		public ListArray(int siz,char st){
			larray = new ListNode[siz];
			location = 0;
			size=siz;
			sorted = true;
			sortType = st;
			duplicatesAllowed = true;
		}
		
		public ListArray(int siz,boolean d){
			larray = new ListNode[siz];
			location = 0;
			size=siz;
			sorted = false;
			duplicatesAllowed = d;
		}
		
		public ListArray(int siz, boolean d,char st){
			larray = new ListNode[siz];
			location = 0;
			size=siz;
			sorted = true;
			sortType = st;
			duplicatesAllowed = d;
		}
		
		private void resize(){
			size*=2;
			ListNode<T>[] temp = new ListNode[size];
			for (int i=0;i<size/2;i++)
				temp[i]=larray[i];
			larray = new ListNode[size];
			for (int i=0;i<size/2;i++)
				larray[i]=temp[i];
			
		}
		
		public void add(T obj){
			ListNode<T> newNode = new ListNode(obj);
			if (duplicatesAllowed == true){
				if (location==size)
					resize();
				}
			if (duplicatesAllowed == false){	
				if(location>0){
					for(int i=0;i<location;i++){
						if(larray[i].getData() == newNode.getData())
						return;
					}
				if (location==size)
					resize();
				}
			}
			if(sorted == false){
						larray[location] = newNode;
						location++;						
					}
			if(sorted == true){
				boolean inserted = false;
				if(sortType == 'a'){
					int i = location;						
					while(!inserted && i>0){
						int x = newNode.getData().compareTo(larray[i-1].getData());
						if(x > 0){
							larray[i]=newNode;
							inserted = true;
						}
						else{
							larray[i]=larray[i-1];
							i=i-1;
						}	
					}
					if(!inserted){
						larray[0] = newNode;
					}
					location++;
				}
				if(sortType == 'd'){
					int i = location;
					while(!inserted && i>0){
						int x = newNode.getData().compareTo(larray[i-1].getData());
						if (x<0){
							larray[i]=newNode;
							inserted = true;
						}
						else{
							larray[i]=larray[i-1];
							i=i-1;
						}
					}
					if(inserted == false){
						larray[0] = newNode;
					}
					location++;
				}
			}	
		return;
	}	   			
		public void print(){
			for (int i=0;i<location;i++)
				System.out.println(larray[i].getData());
		}
		
		private ListNode<T>[] larray;
		int location;
		int size;
		boolean sorted;
		char sortType; // 'a' for ascending sort, 'd' for descending sort
		boolean duplicatesAllowed;

	
public static void main(String[] args){
		Integer i4 = 4;
		Integer i5 = 5;
		Integer i6 = 6;
		Integer i7 = 7;
		
		System.out.println("Duplicates allowed, unsorted");
		ListArray du = new ListArray(1);
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
		ListArray da = new ListArray(10,'a');
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
		ListArray dd = new ListArray(1,'d');
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
		ListArray ndu = new ListArray(1,false);
		System.out.println("Printing blank");
		ndu.print();
		ndu.add(i5);
		System.out.println("Added 5");
		ndu.print();
		ndu.add(i5);
		System.out.println("Added duplicate 5");
		ndu.print();
		ndu.add(i4);
		System.out.println("Added 4");
		ndu.print();
		ndu.add(i6);
		System.out.println("Added 6");
		ndu.print();
		System.out.println("");

		System.out.println("Duplicates not allowed, ascending sorted");
		ListArray nda = new ListArray(10,false,'a');
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
		ListArray ndd = new ListArray(10,false,'d');
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

		System.out.println("Testing with characters, no duplicates, ascending");
		ListArray c = new ListArray(10,false,'a');
		System.out.println("blank");
		c.print();
		Character d = 'd';
		c.add(d);
		System.out.println("added d");
		c.print();
		Character f = 'f';
		c.add(f);
		System.out.println("added f");
		c.print();
		Character b = 'b';
		c.add(b);
		System.out.println("added b");
		c.print();
}		

		
}