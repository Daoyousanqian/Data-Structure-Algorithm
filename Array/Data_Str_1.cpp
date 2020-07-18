#include"myArray.hpp"
#include<iostream>

using namespace std;

void testfunc_1(){
	
	myArray<int> Arr1(10);
	
	Arr1.popBack();
	
	myArray<int> Arr2(Arr1);
	Arr2.append(3);
	Arr2[0] = 20; 
	cout << "the size is:" << Arr2.getSize()<< endl;
	
	cout << "the capacity is:" << Arr2.getCapacity()<< endl;
	
	//cout << "the capacity is:" << Arr1.m_capacity<< endl;
	
}

// test the customized data 

class Company {

public:
	
	Company(){}
	Company(string name , int year){
		
		this->m_name = name;
		this->m_year = year;
		
	}
	
	~Company(){
		
	}
	
public:
	string m_name;
	int m_year;
	
};

void printCustomizeArray(myArray<Company> & arr){
	
	for(int i = 0; i < arr.getSize(); i ++ )
	{
		cout<< "the name of company is : " <<arr[i].m_name << " the year is" << arr[i].m_year<<endl;
	} 
}

void testFunc02(){
	
	Company comp1("FACEBOOK", 1990);
	Company comp2("NOKIA", 1910);
	Company comp3("KONE", 1920);
	Company comp4("BMW", 1910);
	Company comp5("NVDIA", 1992);
	
	myArray<Company> compArr(5);
	compArr.append(comp1);
	compArr.append(comp2);
	compArr.append(comp3);
	compArr.append(comp4);
	compArr.append(comp5);
	
	printCustomizeArray(compArr);
	
}


int main(){

	testfunc_1();
	testFunc02();
	return true;

}
