package core;

/**
 * The class LList.
 *
 * @author  Vladimir Plagov
 * @version 9/25/2018 v1
 * IT WOOOORKS!!!
 */

public class LList<T>
{
    Node<T> head;
    Node<T> last;
    
    public LList()
    {
        head = null;
        last = null;
    }
    
    public void add(T value)
    {
        if (head == null)
        {
            Node<T> a = new Node<T>(value, head);
            head = a;
            last = a;
        }
        else
        {
            Node<T> a = new Node<T>(value, null);
            last.next = a;
            last = a;
        }
    }
    
    public void addFirst(T value){
    	
    	 if (head == null)
         {
             Node<T> a = new Node<T>(value, head);
             head = a;
             last = a;
         }
    	 else
    	 {
    		 Node<T> a = new Node<T>(value, head);
             head = a;
    	 }
    }
    
    public void addLast(T value) {
        if (head == null)
        {
            Node<T> a = new Node<T>(value, head);
            head = a;
            last = a;
        }
        else
        {
            Node<T> a = new Node<T>(value, null);
            last.next = a;
            last = a;
        }
    }
    
    public int size()
    {
        // Start at first Node
        Node<T> current = head;
        int count = 0;
        
        // Loop until last Node, counting as
        // we go.
        while (current != null)
        {
            current = current.next;
            count++;
        }
        
        return count;
    }
    
    public void clear()
    {
        head = null;
        last = null;
    }
    
    // insert
    public void insert(int index, T value)
    {
    Node<T> current = head;
    int count = 0;
    
    if (index > size()-1 || index < 0) throw new Party();
            else {
            	while (count < index-1) {
                	current = current.next;
                	count++;
                }
               if (index == 0) addFirst(value);
               else {
            	   Node<T> a = new Node<T>(value, current.next);
            	   current.next = a;
               }
            }      
    }
    
    // remove
    public void remove(int index)
    {
    	if (index < 0 || index > size()-1) throw new Party();
    	else
    	{
    		Node<T> current = head;
    		int count = 0;
    		
    		if (size() == 1) clear();
    		else if (index == 0) {head = current.next;}
    		else
    			while (count < index-1 ) {
    				current = current.next;
    				count++;
    			}
    		if (current.next == last){
    			last = current;
    			current.next = null;}
    		else current.next = current.next.next;    		
    	}
    }
    
    // toString
    public String toString()
    {
    	Node<T> current = head;
    	String out = "";
    	
    	while (current != null) {
    		if (current == last) out += current.value;
    		else out += current.value + ", ";
    		current = current.next;
    	}
    	
    	return "["+out+"]";
       
    }
    
    // get
    public T get(int index)
    {
        Node<T> current = head;
        int count = 0;
        
        if (index > size()-1 || index < 0) throw new Party();
            else
              while(current != null) {
                  if (count == index) break;
                  else {
                      current = current.next;
                      count++;
                  }
              }
        return current.value;
    }
    
    // set
    public void set(int index, T value)
    {
    	 Node<T> current = head;
         int count = 0;
         
         if (index > size()-1 || index < 0) throw new Party();
         else 
        	 while (current != null) {
        		 if (count == index) break;
        		 else {
        			 current = current.next;
        			 count++;
        		 }
        	 }
         current.value = value;
    }
 
    // indexOf
    public int indexOf(T value)
    {	
    	Node<T> current = head;
    	int count = 0;
    	int index = -1;
    	while(current != null)
    		if (current.value.equals(value)) {
    			index = count; 
    			break;}
    		 else
    		 {
    			current = current.next;
			 	count++;
    		 }   
    		return index;
    	}
        
    
    
    // contains
    public boolean contains(T value)
    {
        if (indexOf(value) != -1) return true; else return false;
    }
}