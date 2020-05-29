
#include <iostream>
#include "hxlstr.h"

using namespace hxl;
using namespace std;

int main()
{
	char16_t char16Array[] = u"Hexellence";
	char16_t char16ArrayTrim[] = u"   Hexellence    ";
	char char8Array[] = "   Hexellence    ";

	uint8_t memorySim[150];

	memorySim[30] = 'T';
	memorySim[31] = 'T';
	memorySim[32] = '$';
	memorySim[33] = 'T';
	memorySim[34] = 'T';


	//hxlstr();
	hxlstr test1;
	cout << "test1: " << test1 << endl;

	//hxlstr(const char* init);
	hxlstr test2("Tunca");
	cout << "test2: " << test2 << endl;
	
	hxlstr test3(char8Array);
	cout << "test3: " << test3 << endl;

	//hxlstr(const uint8_t * init, int size, ENC enc);
	hxlstr test4(&memorySim[30], 5, hxlstr::ENC::ASCII);
	cout << "test4: " << test4 << endl;
	cout << "test4: " << test4.c_str() << endl;
	cout << "test4: " << test4 << endl;

	//drop $
	test4.drop('$');
	cout << "test4 after dropping $: " << test4 << endl;

	//hxlstr(const hxlstr & other);
	hxlstr test5 = test2;
	cout << "test5: " << test5 << endl;

	//hxlstr(const char16_t* init);
	hxlstr test6(char16Array);
	cout << "test6: " << test6 << endl;

	//hxlstr(char init, int size = 1);
	hxlstr test7('$', 3);
	cout << "test7: " << test7 << endl;

	//hxlstr(int number);
	hxlstr test8(42);
	cout << "test8: " << test8 << endl;
	
	hxlstr test9(-42);
	cout << "test9: " << test9 << endl;
	
	hxlstr test10(2147483647);
	cout << "test10: " << test10 << endl;
	
	//const hxlstr& operator=(const hxlstr& other);
	test1 = test2;
	cout << "test1: " << test1 << endl;
	
	//const hxlstr& operator=(const char* str);
	test1 = "Hexellence";
	cout << "test1: " << test1 << endl;

	//const hxlstr& operator=(const char16_t* str);
	test1 = char16ArrayTrim;
	cout << "test1: " << test1 << endl;

	test1.ltrim();
	cout << "test1: " << test1 << endl;
	
	test1.rtrim();
	cout << "test1: " << test1 << endl;

	test1 = char16ArrayTrim;
	cout << "test1: " << test1 << endl;
	test1.trim();
	cout << "test1: " << test1 << endl;

	if (test1 == test6) {
		cout << test1 << " is equal to " << test6 << endl;
	}

	if (test1 != test2) {
		cout << test1 << " is not equal to " << test2 << endl;
	}
	else {
		cout << test1 << " is equal to " << test2 << endl;
	}

	if (test1 != test2) {
		cout << test1 << " is not equal to " << test6 << endl;
	}

	hxlstr test12 = test1 + test2;
	cout << test12 << endl;



	/*		
		const uint8_t* raw() const;
		const char* c_str();
		const char16_t* c16_str() const;		
		int size() const;
		int len() const;
		ENC enc();
		int rtrim();
		int ltrim();
		int trim();
		void drop(const char16_t chars);
		void drop(const char chars);
		friend std::ostream& operator<<(std::ostream& out, const hxlstr& obj);
		friend bool operator==(const hxlstr& obj1, const hxlstr& obj2);
		friend hxlstr operator+(const hxlstr& obj1, const hxlstr& obj2);
		friend bool operator!=(const hxlstr& obj1, const hxlstr& obj2);*/




    std::cout << "Hello World!\n";
}