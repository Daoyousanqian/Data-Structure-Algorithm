// in this file we will write our own list and 
// the difference between vector and list is that
// one is "call- by - Rank" 
// one is " call -by - position"
// 1, Vector is easy to find the element but is needs linear
// time to remove and insert
// 2, List takes linear time to search but constant time to
// insert and remove. 
// 

#ifndef List_Node_Str
#define List_Node_Str
typedef int Rank; // define rank
#define ListNodePosi(T) ListNode<T>* 


template <typename T> struct ListNode {
	
	// members 
	T data; ListNodePosi(T) predecessor; ListNodePosi(T) succ; 
	ListNode() {}
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL) : data(e), predecessor(p), succ(s) {}
	ListNodePosi(T) insertAsPred(T const& e);  // insert as predecessor
	ListNodePosi(T) insertAsSucc(T const& e); // insert as successor
	
	
}; // need a ; after struct definition

template<typename T>
ListNodePosi(T) ListNode<T> :: insertAsSucc(T const& e)
{
	ListNodePosi(T) x = new ListNode(e, this, succ);
	succ -> predecessor = x;
	succ = x ;
	return x; // return node's pointer.
	
}

template<typename T>
ListNodePosi(T) ListNode<T> :: insertAsPred(T const& e)
{	
	// construct a new node and assign the predecessor and successor
	ListNodePosi(T) x = new ListNode(e, predecessor, this);
	predecessor ->succ = x;
	predecessor = x; 
	return x; 
	
}

#endif