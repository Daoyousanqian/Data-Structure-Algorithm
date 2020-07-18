#pragma once 
#include <iostream>
#include <string>
using namespace std;

template<class T>
class myArray{
	
public:

	myArray(int capacity){
		
		this->m_capacity = capacity;
		this->m_size = 0;
		this->pAddress =  new T[this->m_capacity];
		
		//used for test
		cout << "this is the struct function" << endl;  
		
	}
	
	myArray(const myArray& p)
	{
		this->m_capacity = p.m_capacity;
		this->m_size = p.m_size;
		this->pAddress =  new T[p.m_capacity];
		
		for(int i = 0; i <this->m_size; i++ )
		{
			this->pAddress[i] = p.pAddress[i];	
		}
		
		// used for debug
		cout << "this is the copy struct function" << endl;
	}
	
	//reload the operator to avoid shallow copy
	
	myArray& operator=(const myArray& otherArray)
	{
		
		// this is used to relase the data left; 
		if (this->pAddress != NULL)
		{
			delete[] this->pAddress;
			this-> m_size = 0;
			this-> m_capacity = 0;
			this-> pAddress = NULL;
		}
		
		this-> m_capacity = otherArray.m_capacity;
		this-> m_size = otherArray.m_size;
		this-> pAddress = new T [this->m_capacity];
		
		for(int i = 0; i < this->m_size; i++ )
		{
			this->pAddress[i] = otherArray.pAddress[i];	
		}
		
		// used for debug
		cout << "leftvalue operation" << endl;
		
		// need to retrun the pointer;
		return *this;
	}
	
	// use operator p[] to access the elements 
	// lvalue need to use reference & 
	T& operator[]( int ind){
		
		return this->pAddress[ind];
	}
	
	
	//some other functions 
	
	int getSize(){
		
		return m_size;
		
	}
	
	int getCapacity(){
		
		return this->m_capacity;
		
	}
	
	// append new element in the array;
	
	void append(const T & val){
		
		if (this->m_capacity == this->m_size){
			
			cout << "it is already full" << endl;
			return;
		}
		
		this->pAddress[this->m_size]= val;
		this->m_size++;
		
	}
	
	// remove the last one element
	void popBack(){
		
		if (this->m_size ==0)
		{	
			cout << "this already empty"<<endl;
			return;
		}
		this->m_size--;
	}
	
	//destructruct function
	~myArray(){
		
		if(this != NULL)
		{
			delete [] this->pAddress;
			
		}
		
		//used for debug
		cout << "destruct function" << endl;
	}
	
private:
	int m_size;
	int m_capacity;
	T *pAddress;
};