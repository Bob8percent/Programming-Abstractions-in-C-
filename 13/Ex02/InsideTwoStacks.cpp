#include "InsideTwoStacks.h"
#include <iostream>

InsideTwoStacks::InsideTwoStacks() {
	capacity = INITIAL_CAPACITY;
	elements = new char[capacity];
	beforeCount = 0;
	afterCount = 0;
}

InsideTwoStacks::InsideTwoStacks(const InsideTwoStacks& src) {
	deepCopy(src);
}

InsideTwoStacks::~InsideTwoStacks() {
	delete[] elements;
}

InsideTwoStacks& InsideTwoStacks::operator=(const InsideTwoStacks& src) {
	if (this != &src) {
		delete[] elements;
		deepCopy(src);
	}
	return *this;
}

std::size_t InsideTwoStacks::size(STACK_TYPE type) const {
	if (type == BEFORE)return beforeCount;
	else if (type == AFTER) return afterCount;

	std::cerr << "ERROR : int InsideTwoStacks::size(STACK_TYPE type) const : "
		<< "引数typeにBEFOREまたはAFTER以外を指定しています" << std::endl;
	std::exit(EXIT_FAILURE);
}

bool InsideTwoStacks::isEmpty(STACK_TYPE type) const {
	if (type == BEFORE)return beforeCount <= 0;
	else if(type == AFTER)return afterCount <= 0;

	std::cerr << "ERROR : bool InsideTwoStacks::isEmpty(STACK_TYPE type) const : "
		<< "引数typeにBEFOREまたはAFTER以外を指定しています" << std::endl;
	std::exit(EXIT_FAILURE);
}

void InsideTwoStacks::clear(STACK_TYPE type){
	if(type==BEFORE)beforeCount = 0;
	else if(type==AFTER)afterCount = 0;
	else {
		std::cerr << "ERROR : void InsideTwoStacks::clear(STACK_TYPE type) : "
			<< "引数typeにBEFOREまたはAFTER以外を指定しています" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void InsideTwoStacks::push(char ch, STACK_TYPE type) {
	if (beforeCount + afterCount >= capacity) expandCapcity();
	if (type == BEFORE)elements[beforeCount++] = ch;
	else if (type == AFTER)elements[capacity - 1 - (afterCount++)] = ch;
	else {
		std::cerr << "ERROR : void InsideTwoStacks::push(char ch, STACK_TYPE type) : "
			<< "引数typeにBEFOREまたはAFTER以外を指定しています" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

char InsideTwoStacks::pop(STACK_TYPE type) {
	if (!isEmpty(type)) {
		if (type == BEFORE) return elements[--beforeCount];
		else if (type == AFTER)return elements[capacity - 1 - (--afterCount)];
		std::cerr << "ERROR : char InsideTwoStacks::pop(STACK_TYPE type) : "
			<< "引数typeにBEFOREまたはAFTER以外を指定しています" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	else {
		std::cerr << "ERROR : char InsideTwoStacks::pop(STACK_TYPE type) : "
			<< "指定したtypeのスタックは空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}
char InsideTwoStacks::peek(STACK_TYPE type) const {
	if (!isEmpty(type)) {
		if (type == BEFORE) return elements[beforeCount - 1];
		else if (type == AFTER) return elements[capacity - 1 - afterCount - 1];
		std::cerr << "ERROR : char InsideTwoStacks::peek(STACK_TYPE type) const : "
			<< "引数typeにBEFOREまたはAFTER以外を指定しています" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	else {
		std::cerr << "ERROR : char InsideTwoStacks::peek(STACK_TYPE type) const : "
			<< "指定したtypeのスタックは空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
}

void InsideTwoStacks::expandCapcity() {
	std::size_t oldCapacity = capacity;
	capacity *= 2;
	char* newElements = new char[capacity];
	for (std::size_t i = 0; i < beforeCount; ++i)newElements[i] = elements[i];
	for (std::size_t i = 0; i < afterCount; ++i)newElements[capacity - i - 1] = elements[oldCapacity - i - 1];
	delete[] elements;
	elements = newElements;
}

void InsideTwoStacks::deepCopy(const InsideTwoStacks& src) {
	capacity = src.capacity;
	elements = new char[capacity];
	beforeCount = src.beforeCount;
	afterCount = src.afterCount;
	for (std::size_t i = 0; i < beforeCount; ++i)elements[i] = src.elements[i];
	for (std::size_t i = 0; i < afterCount; ++i)elements[capacity - i - 1] = src.elements[capacity - i - 1];

}
