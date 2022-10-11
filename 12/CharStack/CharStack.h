#pragma once
#include "Library/vector.h"

class CharStack
{
public:
	CharStack();
	CharStack(const CharStack& src);
	~CharStack();

	CharStack& operator=(const CharStack& src);

	int size() const;
	bool isEmpty() const;
	void clear();
	
	void push(char ch);
	char pop();

	char peek() const;	//	最上の要素を返すが、それはスタックから除外しない

private:
	static const int INITIAL_CAPACITY = 10;	//	CharStackオブジェクトすべてに共通している定数なのでstatic
	char* elements;
	int count;		//	要素数
	int capacity;	//	メモリを確保せずに格納できる要素数の最大

	void expandCapacity();
	void deepCopy(const CharStack& src);
};

