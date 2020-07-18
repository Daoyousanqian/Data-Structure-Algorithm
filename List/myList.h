#include"listNode.h"
#include<iostream>
using namespace std;
template<typename T> class myList{

private: 	
	int _size; ListNodePosi(T) header; ListNodePosi(T) trailor;

protected:
	void init(); // create the list and initialization 
	int clear();
	
	ListNodePosi(T) last() {return trailor -> predecessor;}
	void copyNodes(ListNodePosi(T) p , int n);
	T remove(ListNodePosi(T) p);

public:
	myList() {init();}// default contructor function
	myList(myList<T> const& L); // copy the whole list
	myList(myList<T> const& L, Rank st, int n); // copy number n from psotion st);
	myList(ListNodePosi(T) p, int n); // copy number n from psotion p);
	~myList();
	
	// accessable functions
	T& operator[](Rank r) const;
	// header is not the first node.
	
	ListNodePosi(T) first() const{return header->succ;}
	Rank size() const {return _size;}
	bool empty() const {return (_size <=0);}  // empty or not
	// to judge the p is leagal or not 
	bool valid( ListNodePosi(T) p)
	{ return p && (trailor != p )&& (header != p);}
	ListNodePosi(T) find(T const& e);
	ListNodePosi(T) find(T const& e, int n, ListNodePosi(T)p);
	ListNodePosi(T) search( T const& e, int n, ListNodePosi(T)p);
	
	//mutable functions
	ListNodePosi(T) insertAsSucc(T const& e);
	ListNodePosi(T) insertAsPre(T const& e);
	ListNodePosi(T) insertAsFirst(T const& e);
	ListNodePosi(T) insertAsLast(T const& e);
	ListNodePosi(T) insertAsBefore(ListNodePosi(T)p,T const& e);
	ListNodePosi(T) insertAsAfter(ListNodePosi(T)p,T const& e);
	int deduplicate();
	int uniquify();
	int uniquify_1();
	void selectSort(ListNodePosi(T) p, int n);
	ListNodePosi(T) selectMax(ListNodePosi(T), int n);
	void insertionSort(ListNodePosi(T) p , int n);
	
};

template<typename T>
void myList<T> :: init()
{
	
	header = new ListNode<T>; // creat 
	trailor = new ListNode<T>;
	header -> succ = trailor;
	header -> predecessor = NULL ;// header has no predecessors;
	trailor -> predecessor = header;
	trailor -> succ = NULL;  // trailor has not successors;
	_size = 0; 
	
}

template<typename T>
T& myList<T> :: operator[](Rank r) const
{
	ListNodePosi(T) p = first();
	//ListNodePosi(T) p = header->succ;
	while (0 < r--) p = p->succ;
	return p -> data; 
	
}

template<typename T>
ListNodePosi(T) myList<T> :: insertAsFirst(T const& e)
{	
	// e will inserted as successor of header
	_size++; return header -> insertAsSucc(e);
}

// e will inserted as the predecessor as trailer
template<typename T>
ListNodePosi(T) myList<T> :: insertAsLast(T const& e)
{
	_size++; return trailor -> insertAsPred(e);
}

// insert e before the node position p
template<typename T>
ListNodePosi(T) myList<T> :: insertAsBefore(ListNodePosi(T) p, T const& e)
{
	_size++; return p->insertAsPred(e);
}

// insert e after the node position p
template<typename T>
ListNodePosi(T) myList<T> :: insertAsAfter(ListNodePosi(T) p, T const& e)
{
	_size++; return p->insertAsSucc(e);
}

template<typename T>
myList<T> :: ~myList(){
	
	clear(); delete header; delete trailor;
}

template<typename T>
int myList<T> :: clear()
{
	int Old_size;
	while (0 < _size) remove(header-> succ);
	
	return Old_size;  
}	

template<typename T>
T myList<T> :: remove(ListNodePosi(T) p)
{
	// copy the value
	T e = p-> data;
	p -> predecessor -> succ = p-> succ;
	p-> succ-> predecessor = p->predecessor;
	delete p; _size--;
	return e;
}

// find from the disordered list in predecessors of List Node p
template<typename T>
ListNodePosi(T) myList<T> :: find(T const& e, int n, ListNodePosi(T) p )
{
	while(0<n--) 
		if((p = p-> predecessor)->data == e) 
			return p;
		
	return NULL;
	
}

// from tailor to search the number e; 
template<typename T>
ListNodePosi(T) myList<T> :: find(T const& e)
{
	return find(e, _size, trailor-> predecessor);
}

// copy construction function
template<typename T>
void myList<T> :: copyNodes(ListNodePosi(T) p, int n)
{	
	init();
	while(0<n--) 
	{insertAsLast(p->data); p = p->succ;}
}

//copy construction functions
template<typename T>
myList<T> :: myList(ListNodePosi(T) p, int n)
{
	copyNodes(p, n);
}

template<typename T>
myList<T> :: myList(myList<T> const& L )
{
	copyNodes(L.first(), L.size());
}
/*
template<typename T>
myList<T> ::myList(myList<T> const& L, Rank st, int n)
{
	copyNodes(L[st], n);
}
*/

// this is in the ordered list.
template<typename T>
int myList<T> :: uniquify()
{
	int Old_size = _size;
	if (_size < 2)
		return 0;
	ListNodePosi(T) p =header; Rank r=0;
	while(r < _size-1)
		if(p->succ->data == p->succ->succ -> data )
			remove(p->succ);
		else 
			{ p = p->succ; r++;}
		
	return Old_size - _size;
}

// this is in the disordered list
// we have to pass through all the elements to find the same element; 

template<typename T>
int myList<T> :: uniquify_1()
{
	if(_size < 2) return 0 ;
	int Old_size; 
	ListNodePosi(T) p = first(); ListNodePosi(T) q;
	while (trailor != (q = p->succ))
		if(p->data == q->data)
			remove(q); 
		else
			p = q;
	return Old_size - _size;
}


// start from node p, and p->data, if there is node having
// the same value q, then remove q, 
// my question is that r would change
// r would not change, as p = p->succ 
// if there is one node are omitted, then p move to next one
// the predecessors numbers keep same 
template<typename T>
int myList<T> :: deduplicate()
{
	if(_size < 2 ) return 0;
	Rank r = 0; int Old_size = _size;
	ListNodePosi(T) p = header; 
	while ( trailor != (p = p->succ))
		{	
			ListNodePosi(T) q = find(p->data, r, p);
			q? remove(q): r++ ; 
			
		}
	return Old_size -_size;
}

// the differenc is that in each round 
// pick the max one 
// put it in the order
// sort n nodes from position p
template<typename T>
void myList<T> :: selectSort(ListNodePosi(T) p, int n)
{
	// head node is the starting point;
	// [p, p+n) the scope is (p->predecessor, p + n)
	ListNodePosi(T) head = p->predecessor;
	ListNodePosi(T) tail = p;
	for(int i =0; i<n; i++) tail = tail ->succ;
	while (1< n)
	{
		insertAsBefore(tail, remove(selectMax( head->succ, n)));
		tail = tail->predecessor;
		n--;
		// here n-- should be in the last,
		// otherwise the scope do not matach
		// {2,5,3,6,7} might become {7,2,3,5,6}
		
	}
	
}

template<typename T>
ListNodePosi(T) myList<T> :: selectMax(ListNodePosi(T)p, int n)
{
	ListNodePosi(T) max = p;
	ListNodePosi(T) cur_posi = p;
	for (int i = 0; i< n ; i++)
	{
		if((max->data) <= (cur_posi->data))
			max = cur_posi;
		cur_posi= cur_posi->succ;
	}
	return max;
}

// return the value that not greater than 
template<typename T>
ListNodePosi(T) myList<T> :: search( T const& e, int n, ListNodePosi(T)p)
{
	while(0<=n--)
	{
		if((p=p->predecessor)->data <= e)
			break;
	}
	cout<< "the data of p is " << p->data <<endl;
	return p;
	
}
// insertion sorting n nodes start from position p 
template<typename T>
void myList<T> :: insertionSort( ListNodePosi(T)p, int n)
{
	for(int r = 0; r< n; r++)
	{
		insertAsAfter(search(p->data, r, p), p->data);
		p = p->succ; remove(p->predecessor);
	}
}


