#ifndef MYVECTOR_H
#define MYVECTOR_H
#include <cstdlib>
typedef int Rank; // rank of the vector
#define DEFAULT_CAPACITY 3
#include<algorithm>
#include<ctime>
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
        Rank find_f(T const& e) {return find_f( e, 0, _size);}


        // COULD WRITE THE DATA
        T& operator[](Rank r) const {return _elem[r];};
        myVector<T>& operator= (myVector<T> const &);
        void unsort(Rank lo, Rank hi);
        void unsort(){unsort(0,_size-1);}


    protected:
        Rank _size; int _capacity; T *_elem;
        void copyFrom(T const* A , Rank lo, Rank hi);
        void expand();  // expand the storage space
        void shrink(); // shrink the storage space
        void swap(T &a, T &b){T c = a; a = b; b = c;}

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

    while((lo < hi--)&& (e != _elem[hi]));
    return hi;   // if return value lo greater than hi then failed
}


#endif // MYVECTOR_H
