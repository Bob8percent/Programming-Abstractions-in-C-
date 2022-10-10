#pragma once
#include "Library/vector.h"

class CharStack
{
public:
	CharStack();
	~CharStack();

	int size();
	bool isEmpty();
	void clear();
	
	void push(char ch);
	char pop();

	char peek();	//	最上の要素を返すが、それはスタックから除外しない

private:
	static const int INITIAL_CAPACITY = 10;
	char* elements;
	int count;		//	要素数
	int capacity;		//	メモリを確保せずに格納できる要素数の最大

	void expandCapacity();
};

