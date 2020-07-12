#include <iostream>
#include "myVector.h"
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <time.h>
//#include <random>
//#include"myVector.cpp"
using namespace std;

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
    vect3.unsort();
    std::cout << vect3[0] << std::endl;
    std::cout << vect3[1] << std::endl;
    std::cout << vect3[2] << std::endl;
    std::cout << vect3[3] << std::endl;
    std::cout << vect3[4] << std::endl;
    std::cout << rand() << std::endl;
}

int main()
{


    test02();
    return 0;
}
