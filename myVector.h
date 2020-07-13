#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <cstdlib>
typedef int Rank; // rank of the vector
#define DEFAULT_CAPACITY 3
#include<algorithm>
#include<ctime>
#include<stdio.h>
#include<iostream>
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
	switch (rand()%3){
		case 1: bubbleSort(lo, hi); break;
		case 2: selectSort(lo, hi); break;
	
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





























#endif // MYVECTOR_H
