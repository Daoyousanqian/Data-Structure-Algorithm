#include <iostream>
#include <string>
using namespace std;

class Person{
	
public:

	int m_Age;
	int* m_Height;
	
public: 
		Person(){
			
			cout << " this the construct" << endl;
		}
		
		Person(int age, int height)
		{
			
			m_Age = age; 
			
			// memeroy allocation, allocation for new parameters; 
			m_Height = new int (height); 
			// it is a pointer; 
			
			
			cout << " this the construct" << endl;
		}
		
		// deep copy to allocate the memory again
		// copy construct function; 
		Person(const Person &p)
		{
			
			m_Age = p.m_Age; 
			
			m_Height = new int (*p.m_Height); 
			
			cout << " this the construct" << endl;
		}
		
		~Person(){
		
			// release the space of stack
			if (m_Height != NULL){
					delete m_Height;
					m_Height = NULL; 
			}
			cout << " this the destruct function" << endl;
		}

	
};

class Dog {
	
public: 
	int color;
	int length;
	int height;
	int *day;
public:
	
	
	Dog(int a, int b, int c):color(a),length(b),height(c){
	
	}
	~Dog(){
		
	}
	
};

class Phone{
	
public:
	Phone(string Name):m_Brand(Name)
	{
		cout << " this is Phone construct" << endl;
//		m_Brand = Name;

	}
	~Phone(){
		
		cout << " this is Phone destruct" << endl;
		
	}
	
public:

	string m_Brand;

};

class Boss{

public:

	Boss(string name, string phone):m_Name(name),m_Phone(phone)
	{
		cout << " this is boss construct" << endl;
	}
	
	~Boss(){
		
		cout << " this is Boss destruct" << endl;
	}
	
public:
	string m_Name;
	Phone m_Phone; 
};


void test_01()
{
	
	// Person p1(20, 160);
	//this is one pointer *p1.m_Height not "p1.*m_Height" 
	
	// cout << " this is the age " << p1.m_Age << "this is the height: " << *p1.m_Height << endl;
	
	// Person p2(p1);
	// cout << " this is the age " << p2.m_Age << "this is the height: " << *p2.m_Height << endl;
	
	// Dog Haski(10,3,2);
	// cout << " Dog: " << Haski.color << Haski.length<< Haski.height  << endl;
	
	Boss b1("Tahm", "Samsung");
	cout << " Boss: " << b1.m_Name << "use phone: "<< b1.m_Phone.m_Brand  << endl;
	

}




class Static_Person {
	
	// static function
	// All object share the same function.
	// static function can only access static members 
public:
	// static members; 
	static void func1()
	{
		m_A = 100; // 
		// this can not be accessed 
		//m_B = 20;
		cout << " Use th static function "  << endl;
		
	}
	
private:
	// can not be accessed directly;
	static void func2()
	{
		
		cout << " static function2 "  << endl;
		
	}

public:	
	static int m_A;
	int m_B;
};

// need to be declared before use; 
int Static_Person::m_A = 10;

void test_02(){

    //1, call by object
	Static_Person p3;
	p3.func1();
	//2, directly call the function 
	Static_Person::func1();
	
	// can not be accessed directly;
	//Static_Person::func2();
	
}


class Worm{
	
	// this is an empty class to test the space it take
	int m_A;  // take 4 Bytes;
	static int m_B; // static member does not take the space of class.
	
	void func4(){}  // function and variables are in the object space. this is an interface.
	
};

void test_03(){
	Worm W;
	// the empty class would take only 1 byte space. 
	cout << " the size of empty " << sizeof(W) << endl;
}



class Cat {
// learn how to use this pointer; 

public:
	Cat(int age, int weight){
	
		age = age;
		// this pointer will point  to the object member variables;
		this -> weight = weight;
	}

	Cat& AddWeight(const Cat &p){
		
		this -> weight += p.weight;
		return *this;
		// return the the object itself.
	}
public:
	int age;
	int weight;
};

void test_05(){
	
	// can not output the real age; 
	Cat miao(18,400);
	Cat miao1(12, 500);
	miao.AddWeight(miao1).AddWeight(miao);
	cout << " the age of the cat is " << miao.age << "  weight " << miao.weight << endl;
}

class Monkey{

public:
	void showtheName(){
		cout << " this is an empty pointer"  << endl;
	}
	void showtheMember(){
		// to judge whether this is an empty pointer. Robust.
		if(this == NULL)
			return;
		
		cout << " the pointer age is :"<< this->m_Age << endl;
	}
	
	int m_Age; 
};

void test_06(){
	
	Monkey *M =NULL;
	M -> showtheName();
	// cannt access the member variables as there is no object;
	M -> showtheMember();
}


class Building {

	// use friend global to access the private property;
	friend void RoomGuest(Building *building);
	friend class GoodFriend;
	// declare one friend class to access the private properties;
	
public:
	Building(){
		
		SittingRoom = "Super big Sitting room with sunshine";
		BathRoom = "very comfortable bathroom";
		
	}
	~Building(){
		
	}
	
public:
	string SittingRoom;
	
private:
	string BathRoom;
	
};

void RoomGuest(Building *building){
	
	cout << " Guest visit your :"<< building->SittingRoom << endl;
	
	// cannot access directly;
	cout << " Guest visit your :"<< building->BathRoom << endl;
	
}

void test_07(){
	
	Building Super;
	RoomGuest(&Super);
	
}


class GoodFriend{
	
public:
	
	GoodFriend();
	
	void visit(); // access the properties in Building;

	Building * building; 
	
};

GoodFriend::GoodFriend(){
	
	building = new Building;
	
}


void GoodFriend::visit(){
	
	cout << " Good Friend visit :"<< building->SittingRoom << endl;
	cout << " Good Friend visit :"<< building->BathRoom << endl;
	
}

void test_08(){
	
	GoodFriend GF;
	GF.visit();
}

// Here is to test the operator reload; 
class Bird{
public:
	// Bird operator+(Bird &p)
	// {
		// Bird temp;
		// temp.m_Height = this->m_Height + p.m_Height;
		// temp.m_Length = this->m_Length + p.m_Length;
		// return temp;
	// }
	int m_Height;
	int m_Length;
};

Bird operator+(Bird &p1, Bird &p2){
	
	Bird temp;
	temp.m_Height = p1.m_Height + p2.m_Height;
	temp.m_Length = p1.m_Length + p2.m_Length;
	return temp;
	
}

Bird operator+(Bird &p1, int a ){
	
	Bird temp;
	temp.m_Height = p1.m_Height + a;
	//temp.m_Length = p1.m_Length + p2.m_Length;
	return temp;
	
}

ostream & operator<< (ostream &cout, Bird &p){
	
	cout << "the height is: " << p.m_Height << "the weight is: " << p.m_Length;
	// shift left reload;
	return cout;
	
}

void test_09(){
	
	Bird Goss;
	Goss.m_Height = 120;
	Goss.m_Length = 80;
	
	Bird Duck;
	Duck.m_Height = 68;
	Duck.m_Length = 70; 
	
	// it is member function in nature;
	//Bird Rou = Goss.operator+(Duck);
	
	Bird Rou = Goss + Duck;
	
	Bird Ruby = Goss + 10;
	// global operator+ function is 
	// Bird Rou = operator+(Goss , Duck);
	
	cout << "the height of the rou is "<< Rou.m_Height<<endl;
	cout << "the length of the rou is "<< Rou.m_Length<<endl;
	
	cout << "the height of the Ruby is "<< Ruby.m_Height<<endl;
	
	cout << Goss << endl; 
}



int main(){
	
	//test_01();
	//test_02();
	//test_03();
	//test_05();
	//test_06();
	//test_07();
	//test_08();
	test_09();
	system("pause");
	return 0;
	
}