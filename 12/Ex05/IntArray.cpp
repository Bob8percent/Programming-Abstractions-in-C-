#include "IntArray.h"
#include <iostream>

IntArray::IntArray(int n) {
	if (n <= 0) {
		std::cerr << "ERROR : IntArray::IntArray(int n) : "
			<< "nが0以下となっています" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	elements = new int[n];
	for (int i = 0; i < n; ++i)elements[i] = 0;
	this->n = n;
}

IntArray::~IntArray() {
	delete[] elements;
}

int IntArray::size() const {
	return n;
}

int IntArray::get(int k) const {
	if (k < 0 || n <= k) {
		std::cerr << "ERROR : int IntArray::get(int k) const : "
			<< "指定したインデックスkの値が範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return elements[k];
}

void IntArray::put(int k, int value) {
	if (k < 0 || n <= k) {
		std::cerr << "ERROR : int IntArray::put(int k, int value) : "
			<< "指定したインデックスkの値が範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	elements[k] = value;
}

int& IntArray::operator[](int k) {
	if (k < 0 || n <= k) {
		std::cerr << "ERROR : int& IntArray::operator[](int k) : "
			<< "指定したインデックスkの値が範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return elements[k];
}
