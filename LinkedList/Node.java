package core;

/**
 * The class Node.
 *
 * @author  Vladimir Plagov
 * @version 9/25/2018 v1
 */

public class Node<T> {
	 
T value;
Node<T> next;
 
public Node(T v, Node<T> n) {
value = v;
next = n;
}
    
}
 