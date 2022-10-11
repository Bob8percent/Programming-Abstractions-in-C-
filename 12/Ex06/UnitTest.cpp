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

#if 1
#include "IntArray.h"

void intArrayTest() {
	//IntArray zero(0);

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


