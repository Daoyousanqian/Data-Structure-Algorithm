#include <iostream>
#include "myVector.h"
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
#include "myList.h"
//#include <random>
//#include"myVector.cpp"
using namespace std;

void display(myVector<int> vec)
{
	for (int i = 0; i < vec.size(); i++)
		cout << vec[i] << endl;
}

void test01(){

    myVector<int> vec1;
    myVector<int>vect2 = vec1;
    vec1[0] = 1;
    vec1[1] = 2;

    vector<int> v1;
    v1[0]=10;
    myVector<int> vect3 = vec1;

    //pause(10);
    system("Pause");
}

// used to checkout the function of
void test02(){
 //   default_random_engine e;
    int arr[4] = {1,3,4,5};
    srand((unsigned)time(NULL));
    myVector<int> vect3(arr,0,4);
    myVector<int> vect1;
    vect1 = vect3;
    std::cout << vect3.size() << std::endl;
    std::cout << vect3.find_f(3, 0, 3) << std::endl;
    
	display(vect3);
    
    //std::cout << rand() << std::endl;
	vect3.unsort();
	cout<< "this is the vector4" << endl;
	myVector<int> vector4(vect3, 0,4);
	display(vector4);
    //std::cout << rand() << std::endl;
}

/*
Here is the function to test the insert function;
*/

void test03()
{
	srand((unsigned)time(NULL));
	int arr[4] = {1,3,4,5};
	// construct one vector1 
	myVector<int> vect1(arr,0,4);
	vect1.insert(4,10);
	vect1.unsort();
	vect1.insert(101);
	display(vect1);
	
	// this is used to test how to remove the elements;
	
	vect1.remove(4);
	std::cout << "this is the output after remove" << std::endl;
	
	display(vect1);
	
	vect1.remove(10);
}

void test04()
{
	// used to test deduplicate functions
	int arr[7] = {10,2,9,3};
	myVector<int> vect1(arr,0,4);
	display(vect1);
	//std::cout << "find one value from the vectoe " <<vect1.find_f(3) << std::endl;
	
	//vect1.remove(3);
	//std::cout << "the size is " <<vect1.size() << std::endl;
	// here confront the problem that always remove all the data;
	vect1.deduplicate();
	std::cout << "the size is " <<vect1.size() << std::endl;
	display(vect1);
	std::cout << "do the sortING " <<vect1.size() << std::endl;
	// here is to test the sort function;
	vect1.mergeSort(0,4);
	display(vect1);
}

void test05(){
	// here is to test the merge sort
	// and the uniquify function;
	int arr[8] = {10,2,9,3,3,72,2,6};
	myVector<int> vect1(arr,0,8);
	display(vect1);
	vect1.mergeSort(0,8);
	display(vect1);
	// no problem
	vect1.uniquify();
	display(vect1);
	//vect1.traverse();
}

void test06(){
	int arr[8] = {10,2,9,3,3,72,2,6};
	myVector<int> vect1(arr,0,8);
	vect1.mergeSort(0,vect1.size());
	vect1.uniquify();
	display(vect1);
	//increase(std::vect1 );
	//increase(std::vect1 );
	cout<< vect1.search(9, 0, vect1.size()) << vect1.search(1, 0, vect1.size()) << endl;
}

void test07()
{
	// this is used to test the list
	// create the first 
	//myList<int> list_1;
	myList<int> mylist;
	
	for(int i = 0 ; i < 11; i++)
		mylist.insertAsLast(i+1);
	int a = mylist[2];
	cout << mylist.size() << endl;
	cout << mylist.find(1)->data << endl;
	myList<int> mylist2(mylist);
	cout << mylist2.size() << endl;
	cout << mylist2[0] << endl;
	mylist2[1] = 0;
	mylist2[7] = 0;
	//mylist2.deduplicate();
	cout << mylist2.size() << endl;
	cout << mylist2[0] << mylist2[1] << mylist2[2]<< endl;
	mylist2.insertionSort(mylist2.first(),mylist2.size());
	//myList<int> mylist3(mylist, 3, 3);
	cout << mylist2[0] << mylist2[1] << mylist2[2]<< mylist2[3]<<endl;
}

int main()
{


    //test02();
	//test03();
	//test04();
	//test05();
	//test06();
	test07();
    return 0;
}
