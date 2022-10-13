#include "MyString.h"
#include <iostream>

MyString::MyString() {
	elements = new char[INITIAL_CAPACITY];
	elements[0] = '\0';
	capacity = INITIAL_CAPACITY;
	count = 0;
}

MyString::MyString(const std::string& str) {
	capacity = INITIAL_CAPACITY;
	std::size_t strSize = str.length();
	while (strSize >= capacity) {
		capacity *= 2;
	}

	elements = new char[capacity];
	for (std::size_t i = 0; i < strSize; ++i) {
		elements[i] = str.at(i);
	}
	elements[strSize] = '\0';
	count = strSize;
}

MyString::MyString(const MyString& src) {
	deepCopy(src);
}

MyString::~MyString() {
	delete[] elements;
}

std::string MyString::toString() const {
	if (count == 0)return "";

	std::string str;
	for (std::size_t i = 0; elements[i] != '\0'; ++i) {
		str += elements[i];
	}
	return str;
}

std::size_t MyString::length() const {
	return count;
}

MyString MyString::substr(std::size_t start, std::size_t n/* = 0*/) {
	if (!(0 <= start && start < count)) {
		std::cerr << "ERROR : MyString MyString::substr(std::size_t start, std::size_t n = std::string::npos) : "
			<< "startが範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::size_t end = n + start;
	//	nの引数を指定しないときは末尾までにする
	//	また、startからn文字は末尾を超えてしまうときはend=countにする
	if (n == 0 || (end > count))end = count;

	MyString str;
	std::size_t strLen = end - start;
	while (strLen >= str.capacity) {
		str.capacity *= 2;
	}
	delete[] str.elements;
	str.elements = new char[str.capacity];
	str.count = strLen;
	for (std::size_t i = start; i < end; ++i) {
		str[i - start] = elements[i];
	}
	str.elements[end - start] = '\0';
	return str;
}

MyString MyString::operator+(const MyString& src) const {
	std::size_t len = length();
	std::size_t strLen = len + src.length();

	MyString str;
	std::size_t strCapacity = INITIAL_CAPACITY;
	while (strLen >= strCapacity) {
		strCapacity *= 2;
	}
	str.elements = new char[strCapacity];
	str.count = strLen;
	str.capacity = strCapacity;
	for (std::size_t i = 0; i < strLen; ++i) {
		if (i < len)str[i] = elements[i];
		else str[i] = src[i - len];
	}
	str.elements[strLen] = '\0';
	return str;
}

MyString& MyString::operator+=(const MyString& src) {
	std::size_t newLen = count + src.count;
	

	if (newLen >= capacity) {
		while(newLen >= capacity) capacity *= 2;
		char* newElements = new char[capacity];
		for (std::size_t i = 0; i < newLen; ++i) {
			if (i < count)newElements[i] = elements[i];
			else newElements[i] = src[i - count];
		}
		newElements[newLen] = '\0';
		
		delete[] elements;
		elements = newElements;
	}
	else {
		for (std::size_t i = count; i < newLen; ++i) {
			elements[i] = src[i - count];
		}
	}

	count = newLen;

	return *this;
}

MyString& MyString::operator=(const MyString& src) {
	if (this != &src) {
		delete[] elements;
		deepCopy(src);
	}

	return *this;
}

char& MyString::operator[](std::size_t i) const {
	if (!(0 <= i && i < count)) {
		std::cerr << "ERROR : char& MyString::operator[](std::size_t i) const : "
			<< "iが範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return elements[i];
}

bool MyString::operator==(const MyString& src) const {
	if (count != src.count)return false;

	for (std::size_t i = 0; i < count; ++i) {
		if (elements[i] != src[i])return false;
	}

	return true;
}

bool MyString::operator!=(const MyString& src) const {
	return !((*this) == src);
}

bool MyString::operator>(const MyString& src) const {
	std::size_t minLen = (count < src.count) ? count : src.count;

	//	各文字のASCIIコードの大小を比較する
	for (std::size_t i = 0; i < minLen; ++i) {
		if (elements[i] > src[i])return true;
		if (elements[i] < src[i])return false;
	}

	//	minLenまで同じ文字のときは文字列が長い方が大きい
	return count > src.count;
}

bool MyString::operator>=(const MyString& src) const {
	return !(src > (*this));
}

bool MyString::operator<(const MyString& src) const {
	return src > (*this);
}

bool MyString::operator<=(const MyString& src) const {
	return !((*this) > src);
}

void MyString::deepCopy(const MyString& src){
	elements = new char[src.capacity];
	for (std::size_t i = 0; i <= src.count; ++i) {
		elements[i] = src.elements[i];
	}

	count = src.count;
	capacity = src.capacity;
}

std::ostream& operator<<(std::ostream& os, const MyString& src) {
	return os << src.elements;
}
