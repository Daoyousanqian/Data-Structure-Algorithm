#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <cstdlib>
typedef int Rank; // rank of the vector
#define DEFAULT_CAPACITY 3
#include<algorithm>
#include<ctime>
#include<stdio.h>
#include<iostream>
//#include<fib.h>
//#include"myVector.cpp"

template <typename T> class myVector
{
    public:
        myVector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
        {
            _elem = new T [_capacity = c ]; for (_size = 0; _size < s; _elem[_size++] = v );
        }

        myVector(T const* A , Rank lo, Rank hi){copyFrom(A, lo, hi);}  // copy from array;
        myVector(T const* A, Rank n){copyFrom(A, 0, n);}   // copy the whole

        // below is the copy from other vectors;

        myVector(myVector<T> & V, Rank lo, Rank hi){ copyFrom(V._elem, lo, hi);}

        myVector(myVector<T> & V){copyFrom(V._elem, 0, V._size);} // copy constructor from other Vectors


        ~myVector(){delete [] _elem;} // destructor release the internal space


        // read only access the DATA
        T get(Rank r){if(0<=r && r <_size)return _elem[r];}
        Rank size() const {return _size;}  // read only function should add const after the functions
        Rank find_f(T const& e, Rank lo, Rank hi) const;
        Rank find_f(T const& e) {return find_f( e, 0, _size-1);}
		int  disordered() const;
		static Rank binSearch(T const& e, T*A, Rank lo, Rank hi);
		static Rank binSearch_A(T const& e, T*A, Rank lo, Rank hi);
		Rank search (T const& e, Rank lo, Rank hi) const;
		
		
        // COULD WRITE THE DATA
        T& operator[](Rank r) const {return _elem[r];};
        myVector<T>& operator= (myVector<T> const &);
        void unsort(Rank lo, Rank hi);
        void unsort(){unsort(0,_size-1);}
		Rank insert(Rank r, T const& e); // insert one element e at Rank r; 
		Rank insert(T const& e) {return insert(_size, e);}
		int remove(Rank lo, Rank hi); // remove the elements from [lo,hi);
		Rank remove(Rank r); // remove only one element
		
		int deduplicate();
		
		void sort(Rank lo, Rank hi);
	
		void bubbleSort(Rank lo, Rank hi){while(!bubble(lo, hi--));}
		void mergeSort(Rank lo, Rank hi);
		
		void traverse(void (*visit)(T&));
		int uniquify();
		int uniquify_h();
		void increase(myVector<T> &V);
	protected:
        Rank _size; int _capacity; T *_elem;
        void copyFrom(T const* A , Rank lo, Rank hi);
        void expand();  // expand the storage space
        void shrink(); // shrink the storage space
        void swap(T &a, T &b){T c = a; a = b; b = c;}
		//void bubbleSort(Rank lo, Rank hi){while(!bubble(lo, hi--));}
		bool bubble(Rank lo, Rank hi);
		void selectSort(Rank lo, Rank hi);
		Rank max(Rank lo, Rank hi);
		void merge(Rank lo, Rank mi, Rank hi);
		struct Increase{};
		
    private:
};


template<typename T>
void myVector<T>::copyFrom(T const* A , Rank lo, Rank hi)
{
    _elem = new T [_capacity = 2*(hi - lo)]; _size = 0;
    while(lo < hi)
        _elem[_size++] = A[lo++]; // copy the elements from to A

}

template<typename T>
myVector<T>& myVector<T>::operator=(myVector<T> const& V)
{
    // if there are already elements then delete them
    if(_elem) delete [] _elem;
    //copy the elements from other vectors
    copyFrom(V._elem, 0, V._size );
    return *this;
}

// when the space is full this function is used to expand
template<typename T>
void myVector<T>::expand()
{
    if(_size < _capacity) return;
    if(_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;

    T * old_elem = _elem; // the old storage space;
    _elem = new T [_capacity << 1]; // double the size of storage space.
    for(int i = 0; i < _size ; i++ ){

        _elem[i] = old_elem[i];
    }

    delete [] old_elem; // release the original space.
}

template<typename T>
void myVector<T>::shrink(){

    if(_capacity < DEFAULT_CAPACITY <<1 ) return; // do not make the capacity less than Default_capacity
    if(_size<<2 > _capacity) return; // if size/capacity > 25%
    T* old_elem = _elem; _elem = new T [_capacity >>=1] ;// decrease half of the space;
    for(int i = 0; i <_size; i++) _elem[i] = old_elem[i]; // copy the data to new storage space.
    delete[] old_elem;

}

template<typename T>
void myVector<T>::unsort(Rank lo, Rank hi){

    T *V = _elem + lo;
    for (int i = hi-lo; i>0; i--){
        swap(V[i], V[rand()%i]);  // swap the elements in the vectors;
    }
}

template<typename T>
Rank myVector<T>:: find_f(T const &e, Rank lo, Rank hi) const
{
	//std::cout<< "enter the find function" << std::endl;
    while((lo <= hi)&& (e != _elem[hi]))
		hi--;
    //std::cout<< "the value of hi is  " << hi << std::endl;
	return hi;   // if return value lo greater than hi then failed
}


template <typename T>
Rank myVector<T> :: insert(Rank r, T const& e)
{
	expand();
	for (Rank i = _size; i > r; i--) _elem[i] = _elem[i-1]; // copy the elements one by one after r;
	_elem[r] = e;
	_size ++; 
	return r; // return the rank; 
	
}

template <typename T>
int myVector<T> :: remove(Rank lo, Rank hi)
{
	
	//std::cout<< "enter the remove function" << std::endl;
	if(lo == hi) return 0; //  remove nothing
	if(lo > _size) {std::cout<< "the lower bound exceed"<<std::endl; return 0;} // 
	
	while( hi < _size) _elem[lo++] = _elem[hi++];
	_size = lo;
	shrink();
	return hi-lo; 
	
}

template <typename T>
Rank myVector<T> :: remove(Rank r)
{
	T e = _elem[r];
	remove(r,r+1);
	return e;
}

// used to remove the same elements 

template <typename T>
int myVector<T> :: deduplicate()
{
	int old_Size = _size;
	Rank i = 0;
	while(i<_size){
		
		(find_f(_elem[i])<=i)? i++: remove(i);
		/*Rank r = find_f(_elem[i]);
		std::cout << r << " r value" << std::endl;
		if ( r <= i)
		{
			i++;
		}
		else
			remove(i);*/
	}
	return old_Size - _size;
}

template <typename T>
void myVector<T> :: sort(Rank lo, Rank hi){
	switch (rand()%4){
		case 1: bubbleSort(lo, hi); break;
		case 2: selectSort(lo, hi); break;
		case 3: mergeSort(lo, hi); break;
		default: mergeSort(lo, hi); break;
	
	}
}

// sort the vector from [lo, hi)
template <typename T>
bool myVector<T> :: bubble(Rank lo, Rank hi)
{
	bool sorted_flag = true;
	
	while( ++lo < hi)
	{
		if (_elem[lo-1] > _elem[lo])
		{
			sorted_flag = false;
			swap(_elem[lo-1] , _elem[lo]);
		}
		
	}
	return sorted_flag;
}

template <typename T>
void myVector<T> :: selectSort(Rank lo, Rank hi)
{
	// select the maximum one and change with _elem[hi]
	while(lo < --hi)
		swap(_elem[max(lo,hi)], _elem[hi]);
}

template <typename T>
Rank myVector<T> :: max(Rank lo, Rank hi)
{
	// get the maximal value and return the rank 
	Rank temp = hi;
	while(lo< hi--)
		if(_elem[temp] < _elem[hi])
			temp = hi;
	return temp;
}


// merge sort use the divide and solve stratergy 
template <typename T>
void myVector<T> :: mergeSort(Rank lo, Rank hi)    
{
	if(hi - lo < 2) return;
	
	// here I made a mistake the middle value should be the hi+lo shift to right
	int mi = (hi+lo) >> 1;
	mergeSort(lo, mi); 
	mergeSort(mi, hi);
	merge(lo, mi, hi);	
}

template <typename T>
void myVector<T> :: merge(Rank lo, Rank mi, Rank hi)
{
	int l_left = mi-lo;
	int l_right = hi - mi;
	T* A = _elem + lo;  // assign the address to A 
	T* D = _elem + mi;
	T* B = new T[l_left];// allocation new memery B to copy A;
	T* C = new T[l_right];
	// copy elements to B
	//std::cout  <<"left part length is "<< l_left << std::endl;
	//std::cout  <<"right part length is "<< l_right << std::endl;
	//std::cout  <<"right part length is "<< lo << mi << std::endl;
	for(int i = 0; i < l_left; i++ )
	{	
		B[i] = A[i];
		//std::cout  <<"the value of B"<< std::endl;
		//std::cout  <<B[i] << std::endl;
	}
	
	for(int i = 0; i < l_right; i++ )
	{	
		C[i] = D[i];
		//std::cout  <<C[i] << std::endl;
	}
	// 1, the logic here is to put the left part and right part
	// in B and C, 
	// 2, and select the smaller one to do i++;
	// 3, and also avoid B or C could be empty ;
	for(int i = 0, j = 0, k = 0; ((j<l_left) || (k < l_right));)
	{
		//std::cout  << i << j << k << std::endl;
		if ((j<l_left)&&((B[j] <= C[k]) || !(k < l_right)))
			A[i++] = B[j++];
		if((k < l_right) && ((C[k]< B[j])|| !(j < l_left)))
			A[i++] = C[k++];
		//std::cout  <<"the value of A" << std::endl;
		//std::cout  <<A[i] << std::endl;
		//std::cout  << j << std::endl;
	}
	delete [] B;
	delete [] C; 
}

//traverse all the element to do computation
template <typename T>
void myVector<T> :: traverse(void (*visit)(T&))
{
	for(int i = 0; i < _size; i++) visit(_elem[i]);
}

template <typename T>
struct Increase{
	virtual void operator()(T& e){e++; } 
};

template <typename T> void increase(myVector<T> &V)
{
	V.traverse(Increase<T>());
}

// this function is used to count the number that disordered;
template <typename T>
int myVector<T> :: disordered()const
{
	
	int count =0;
	for (int i = _size - 1 ; i > 0; i--)
		if(_elem[i] < _elem[i-1]) count++;
	
	return count; // when it is in order retrun 0;
	
}

// this function is used to remove repeated elements 
// it is not efficient
template <typename T>
int myVector<T> :: uniquify(){
	int old_Size = _size, i = 1;
	while(i< _size)
		(_elem[i-1] == _elem[i])? remove(i): i++;
	return old_Size - _size;
		
}

template <typename T>
int myVector<T> :: uniquify_h()
{	// the idea is that copy the different element one by one;
	
	int i = 0 , j = 1;
	for(; j < _size ;j++)
		if(_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	_size = ++i; shrink();
	return i; 
}

// to write the search function

// binSearch is a static function which is not dependent on class,
// it should be stored in global variable 
// that is why T* A is one arguement
// static function are not in the scope of class
template <typename T>
 Rank myVector<T>:: binSearch (T const &e, T *A, Rank lo, Rank hi)
{
	while(lo < hi )
	{
		Rank mi = (hi + lo) >>1;
		if (e == A[mi]) return mi;
		else if (e < A[mi]) hi = mi  ;
		else lo = mi +1;
		
	}
	return -1; // serach failed
}

template <typename T>
Rank myVector<T> :: search (T const& e, Rank lo, Rank hi) const
{
	return (rand()%2) ? \
	binSearch(e , _elem, lo, hi) : binSearch(e , _elem, lo, hi);
	
}


template <typename T>
Rank myVector<T>:: binSearch_A (T const &e, T *A, Rank lo, Rank hi)
{
	while( hi - lo > 1)
	{
		Rank mi = (hi + lo ) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi;
	}
	return (e == A[lo])? lo: -1; // make the lo is the value we search
}














#endif // MYVECTOR_H
