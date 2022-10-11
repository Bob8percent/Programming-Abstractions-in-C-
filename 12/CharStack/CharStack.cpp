#include "CharStack.h"
CharStack::CharStack() {
	capacity = INITIAL_CAPACITY;
	elements = new char[capacity];
	count = 0;
}

CharStack::CharStack(const CharStack& src) {
	deepCopy(src);
}

CharStack::~CharStack() {
	delete[] elements;
}

CharStack& CharStack::operator=(const CharStack& src) {
	if (this != &src) {	
		//	右辺と左辺が同じとき、ここでelementsをdeleteしてしまうとdeepCopy()で解放したアドレスを参照してしまう事故が起こる
		delete[] elements;
		deepCopy(src);
	}
	return *this;
}

int CharStack::size() const {
	return count;
}

bool CharStack::isEmpty() const {
	return count <= 0;
}

void CharStack::clear() {
	count = 0;
}

void CharStack::push(char ch) {
	if (count >= capacity) expandCapacity();
	elements[count++] = ch;
}

char CharStack::pop() {
	if (isEmpty()) {
		std::cerr << "ERROR : char CharStack::pop() : スタックが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return elements[--count];
}

char CharStack::peek() const {
	if (isEmpty()) {
		std::cerr << "ERROR : char CharStack::peek() : スタックが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return elements[count - 1];
}

void CharStack::expandCapacity() {
	char* oldElements = elements;
	capacity *= 2;
	elements = new char[capacity];
	for (int i = 0; i < count; ++i) {
		elements[i] = oldElements[i];
	}
	delete[] oldElements;
}

void CharStack::deepCopy(const CharStack& src) {
	elements = new char[src.capacity];
	for (int i = 0; i < src.count; ++i) {
		elements[i] = src.elements[i];
	}
	count = src.count;
	capacity = src.capacity;
}
