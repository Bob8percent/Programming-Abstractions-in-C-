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

#if 0
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

	std::cout << newStr1 + newStr2 << std::endl;
	newStr1 += newStr3;
	std::cout << newStr1 << std::endl;
	assert(newStr1.length() == 14);

	std::cout << std::endl << "MyString unit test is succeeded." << std::endl;
}
#endif

#if 0
#include "Rational.h"

void rationalTest() {
	Rational a(1, 3);
	Rational b(1, 4);

	std::cout << "--debug1--" << std::endl;
	std::cout << a + b << "==7/12" << std::endl;
	std::cout << a - b << "==1/12" << std::endl;
	std::cout << b + b << "==1/2" << std::endl;
	std::cout << a / b << "==4/3" << std::endl;
	std::cout << a * b << "==1/12" << std::endl;
	std::cout << a + 4 << "==13/3" << std::endl;
	std::cout << a - 4 << "==-11/3" << std::endl;
	std::cout << a * 4 << "==4/3" << std::endl;
	std::cout << a / 4 << "==1/12" << std::endl;
	std::cout << a * 3 << "==1/1" << std::endl;
	std::cout << 4 + a << "==13/3" << std::endl;
	std::cout << 4 - a << "==-11/3" << std::endl;
	std::cout << 4 * a << "==4/3" << std::endl;
	std::cout << 4 / a << "==1/12" << std::endl;
	std::cout << 3 * a << "==1/1" << std::endl;
	std::cout << ++a << "==4/3" << std::endl;
	std::cout << a++ << "==4/3" << std::endl;
	std::cout << a << "==7/3" << std::endl;
	std::cout << --b << "==-3/4" << std::endl;
	std::cout << b-- << "==-3/4" << std::endl;
	std::cout << b << "==-7/4" << std::endl;
	//a += b;
	//a /= b;
	//a -= b;
	//a *= b;
	//a += 2;
	//a /= 2;
	//a -= 2;
	//a *= 3;
	//std::cout << a << std::endl;

	Rational c(1, -3);
	Rational d(-1, 4);
	std::cout << "--debug2--" << std::endl;
	std::cout << c + d << "==-7/12" << std::endl;
	std::cout << c - d << "==-1/12" << std::endl;
	std::cout << d + d << "==-1/2" << std::endl;
	std::cout << c / d << "==4/3" << std::endl;
	std::cout << c * d << "==1/12" << std::endl;
	std::cout << c + 4 << "==11/3" << std::endl;
	std::cout << c - 4 << "==-13/3" << std::endl;
	std::cout << c * 4 << "==-4/3" << std::endl;
	std::cout << d / 4 << "==-1/16" << std::endl;
	std::cout << d * 3 << "==-3/4" << std::endl;
	std::cout << 4 + c << "==11/3" << std::endl;
	std::cout << 4 - c << "==-13/3" << std::endl;
	std::cout << 4 * c << "==-4/3" << std::endl;
	std::cout << 4 / d << "==-1/16" << std::endl;
	std::cout << 3 * d << "==-3/4" << std::endl;
	//c += d;
	//c /= d;
	//c -= d;
	//c *= d;
	//std::cout << c << std::endl;

	assert(c < d);
	assert(c <= d);
	assert(!(c > d));
	assert(!(c >= d));
	assert(c != d);
	Rational e(1, 4);
	d *= -1;
	assert(e == d);

	std::cout << "Rational unit test is succeeded." << std::endl;
	
}
#endif

#if 0
#include "EditorBuffer.h"

void editorBufferTest() {
	EditorBuffer eb;
	eb.deleteCharacter();

	for (char ch = 'a'; ch <= 'z'; ++ch) {
		eb.insertCharacter(ch);
	}
	assert(eb.getCursor() == 26);
	assert(eb.getText() == "abcdefghijklmnopqrstuvwxyz");
	
	for (int i = 0; i < 50; ++i)eb.moveCursorForward();
	for (int i = 0; i < 50; ++i)eb.moveCursorBackward();
	for (int i = 0; i < 20; ++i)eb.moveCursorForward();
	for (int i = 0; i < 10; ++i)eb.moveCursorBackward();
	assert(eb.getCursor() == 10);
	assert(eb.getText() == "abcdefghijklmnopqrstuvwxyz");

	for (int i = 0; i < 50; ++i)eb.deleteCharacter();
	assert(eb.getText() == "abcdefghij");
	for (char ch = 'k'; ch <= 'z'; ++ch)eb.insertCharacter(ch);
	assert(eb.getText() == "abcdefghijklmnopqrstuvwxyz");

	for (int i = 0; i < 10; ++i)eb.moveCursorBackward();
	assert(eb.getCursor() == 16);
	eb.moveCursorToEnd();
	assert(eb.getCursor() == 26);
	eb.moveCursorToStart();
	assert(eb.getCursor() == 0);

	////	一時的にprivate部分をpublicにして解放テスト
	////	これを行うとデストラクタが呼ばれたときに当然エラーになる
	//eb.moveCursorToEnd();
	//int len = eb.getCursor();
	//eb.deleteBuffer();
	//int trueNum = 0;
	//for (int i = 0; i < eb.debugArray.size(); ++i)if (eb.debugArray[i])++trueNum;
	//assert(1 + len == trueNum);

	//	以下 succeeded.
	//EditorBuffer eb2;
	//for (char ch = 'a'; ch <= 'h'; ++ch) {
	//	eb2.insertCharacter(ch);
	//}
	//assert(eb2.twoStacks.size(BEFORE) == 8);
	//assert(eb2.twoStacks.size(AFTER) == 0);
	//assert(eb2.twoStacks.capacity == 10);

	//eb2.moveCursorToStart();
	//assert(eb2.twoStacks.size(BEFORE) == 0);
	//assert(eb2.twoStacks.size(AFTER) == 8);
	//assert(eb2.twoStacks.capacity == 10);


	std::cout << "editorBuffer unit test is succeeded." << std::endl;
}
#endif

#if 0
#include "_Stack.h"
void stackTest() {
	//	char型
	Stack<char> stk;
	assert(stk.size() == 0);
	assert(stk.isEmpty());

	stk.push('A');
	assert(!stk.isEmpty());
	assert(stk.size() == 1);
	assert(stk.peek() == 'A');
	stk.push('B');
	assert(stk.peek() == 'B');
	assert(stk.size() == 2);
	assert(stk.pop() == 'B');
	assert(stk.size() == 1);
	assert(stk.peek() == 'A');
	stk.push('C');
	assert(stk.size() == 2);
	assert(stk.pop() == 'C');
	assert(stk.peek() == 'A');
	assert(stk.pop() == 'A');
	assert(stk.size() == 0);

	for (char ch = 'A'; ch <= 'Z'; ++ch) {
		stk.push(ch);
	}
	assert(stk.size() == 26);

	for (char ch = 'Z'; ch >= 'A'; --ch) {
		assert(stk.pop() == ch);
	}
	assert(stk.isEmpty());

	for (char ch = 'A'; ch <= 'Z'; ++ch) {
		stk.push(ch);
	}
	assert(stk.size() == 26);

	stk.clear();
	assert(stk.size() == 0);
	stk.clear();
	assert(stk.size() == 0);

	//	int型
	Stack<int> s;
	assert(s.size() == 0);
	assert(s.isEmpty());

	s.push(0);
	assert(!s.isEmpty());
	assert(s.size() == 1);
	assert(s.peek() == 0);
	s.push(1);
	assert(s.peek() == 1);
	assert(s.size() == 2);
	assert(s.pop() == 1);
	assert(s.size() == 1);
	assert(s.peek() == 0);
	s.push(2);
	assert(s.size() == 2);
	assert(s.pop() == 2);
	assert(s.peek() == 0);
	assert(s.pop() == 0);
	assert(s.size() == 0);

	for (int i = 1; i <= 26; ++i) {
		s.push(i);
	}
	assert(s.size() == 26);

	for (int i = 26; i >= 1; --i) {
		assert(s.pop() == i);
	}
	assert(s.isEmpty());

	for (int i = 1; i <= 26; ++i) {
		s.push(i);
	}
	assert(s.size() == 26);

	s.clear();
	assert(s.size() == 0);
	s.clear();
	assert(s.size() == 0);

	std::cout << "Stack unit test succeeded." << std::endl;

}
#endif

#if 1
#include "_Queue.h"
void queueTest() {
	//	char型
	Queue<char> qc;
	assert(qc.size() == 0);
	assert(qc.isEmpty());

	qc.enqueue('A');
	assert(!qc.isEmpty());
	assert(qc.size() == 1);
	assert(qc.peek() == 'A');
	qc.enqueue('B');
	assert(qc.peek() == 'A');
	assert(qc.size() == 2);
	assert(qc.dequeue() == 'A');
	assert(qc.size() == 1);
	assert(qc.peek() == 'B');
	qc.enqueue('C');
	assert(qc.size() == 2);
	assert(qc.dequeue() == 'B');
	assert(qc.peek() == 'C');
	assert(qc.dequeue() == 'C');
	assert(qc.size() == 0);

	for (char ch = 'A'; ch <= 'Z'; ++ch) {
		qc.enqueue(ch);
	}
	assert(qc.size() == 26);

	for (char ch = 'A'; ch <= 'Z'; ++ch) {
		assert(qc.dequeue() == ch);
	}
	assert(qc.isEmpty());

	for (char ch = 'A'; ch <= 'Z'; ++ch) {
		qc.enqueue(ch);
	}
	assert(qc.size() == 26);

	qc.clear();
	assert(qc.size() == 0);
	qc.clear();
	assert(qc.size() == 0);

	//	int型
	Queue<int> qi;
	assert(qi.size() == 0);
	assert(qi.isEmpty());

	qi.enqueue(0);
	assert(!qi.isEmpty());
	assert(qi.size() == 1);
	assert(qi.peek() == 0);
	qi.enqueue(1);
	assert(qi.peek() == 0);
	assert(qi.size() == 2);
	assert(qi.dequeue() == 0);
	assert(qi.size() == 1);
	assert(qi.peek() == 1);
	qi.enqueue(2);
	assert(qi.size() == 2);
	assert(qi.dequeue() == 1);
	assert(qi.peek() == 2);
	assert(qi.dequeue() == 2);
	assert(qi.size() == 0);

	for (int i = 1; i <= 26; ++i) {
		qi.enqueue(i);
	}
	assert(qi.size() == 26);

	for (int i = 1; i <= 26; ++i) {
		assert(qi.dequeue() == i);
	}
	assert(qi.isEmpty());

	for (int i = 1; i <= 26; ++i) {
		qi.enqueue(i);
	}
	assert(qi.size() == 26);

	qi.clear();
	assert(qi.size() == 0);
	qi.clear();
	assert(qi.size() == 0);

	std::cout << "Queue unit test succeeded." << std::endl;

}
#endif


