#include "UnitTest.h"
#include <cassert>
#include <iostream>

#if 0
#include "CharStack.h"

void charStackTest() {
	CharStack cstk;
	assert(cstk.size() == 0);
	assert(cstk.isEmpty());

	cstk.push('A');
	assert(!cstk.isEmpty());
	assert(cstk.size() == 1);
	assert(cstk.peek() == 'A');
	cstk.push('B');
	assert(cstk.peek() == 'B');
	assert(cstk.size() == 2);
	assert(cstk.pop() == 'B');
	assert(cstk.size() == 1);
	assert(cstk.peek() == 'A');
	cstk.push('C');
	assert(cstk.size() == 2);
	assert(cstk.pop() == 'C');
	assert(cstk.peek() == 'A');
	assert(cstk.pop() == 'A');
	assert(cstk.size() == 0);

	for (char ch = 'A'; ch <= 'Z'; ++ch) {
		cstk.push(ch);
	}
	assert(cstk.size() == 26);

	for (char ch = 'Z'; ch >= 'A'; --ch) {
		assert(cstk.pop() == ch);
	}
	assert(cstk.isEmpty());

	for (char ch = 'A'; ch <= 'Z'; ++ch) {
		cstk.push(ch);
	}
	assert(cstk.size() == 26);

	cstk.clear();
	assert(cstk.size() == 0);
	cstk.clear();
	assert(cstk.size() == 0);

	std::cout << "CharStack unit test succeeded." << std::endl;
}
#endif

#if 0
#include "IntArray.h"

void intArrayTest() {
	//IntArray zero();

	IntArray a(10);
	
	//a1 = a;

	assert(a.size() == 10);
	assert(a.get(5) == 0);

	//a.get(10);

	a.put(6, 66);
	assert(a.get(6) == 66);

	//a.put(10, 100);

	//a[10] = 100;

	a[5] = 55;
	assert(a[5] == 55);
	assert(a.get(5) == 55);

	IntArray ca(15);
	ca = a;
	assert(ca[5] == 55);
	assert(ca[6] == 66);
	//ca[14];

	std::cout << "IntArray unit test succeeded." << std::endl;
}
#endif

#if 1
#include "MyString.h"

void myStringTest() {
	std::string s = "abcde";
	MyString str(s);
	std::cout << "--debug0--" << std::endl;
	std::cout << str << std::endl;
	assert(str.length() == 5);

	std::cout << "--debug1--" << std::endl;
	MyString cstr(str);
	std::cout << cstr << std::endl;
	std::cout << cstr.toString() << std::endl;
	MyString astr;
	astr = str;
	std::cout << astr << std::endl;
	std::cout << astr.toString() << std::endl;

	std::cout << "--debug2--" << std::endl;
	std::cout << str.substr(0) << std::endl;
	std::cout << str.substr(1, 2) << std::endl;
	std::cout << str.substr(2, 3) << std::endl;
	std::cout << str.substr(2, 10) << std::endl;
	std::cout << str.substr(1, 0) << std::endl;
	//std::cout << str.substr(-1, 1) << std::endl;

	assert(str.substr(0).length() == 5);
	assert(str.substr(1, 2).length() == 2);
	assert(str.substr(2, 3).length() == 3);
	assert(str.substr(2, 10).length() == 3);

	std::cout << "--debug3--" << std::endl;
	std::cout << str + astr << std::endl;
	cstr += astr;
	//std::cout << cstr << std::endl;
	//assert(cstr[5] == 'a');
	//assert(cstr[6] == 'b');
	//cstr[11];

	assert(str == astr);
	assert(!(str != astr));
	MyString newStr1("ABfjl");
	MyString newStr2("abcdf");
	MyString newStr3("abcdeffff");
	assert(str > newStr1);
	assert(!(str <= newStr1));
	assert(str < newStr2);
	assert(!(str >= newStr2));
	assert(str < newStr3);
	assert(!(str >= newStr3));

	std::cout << std::endl << "MyString unit test is succeeded." << std::endl;
}
#endif
