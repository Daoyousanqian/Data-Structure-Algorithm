#include <iostream>
#include <string>
using namespace std;

class BasePage{
public:
	void header()
	{
		cout << " FIrst page, public courses, login, register(common header) " << endl;
		
	}
	
	void footer()
	{
		cout << " Help center, comminication, career, telephone" << endl;
		
	}
	
	void left()
	{
		cout << " Java, python, C++" << endl;
		
	}
};

class Java : public BasePage
{
public:
	void content(){
		
		cout << "Java education video " << endl;
	}

};

class Python : public BasePage
{
public:
	void content(){
		
		cout << "python education video " << endl;
	}

};

void test_01(){
	
	Java ja;
	ja.header();
	ja.footer();
	ja.left();
	ja.content();
	
	Python py;
	py.header();
	py.footer();
	py.left();
	py.content();
	
	
}

int main(){
	
	test_01();
	
	return 0 ;
}

