#include "CharStack.h"
CharStack::CharStack() {
	capacity = INITIAL_CAPACITY;
	elements = new char[capacity];
	count = 0;
}
CharStack::~CharStack() {
	delete[] elements;
}

int CharStack::size() {
	return count;
}

bool CharStack::isEmpty() {
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

char CharStack::peek() {
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

