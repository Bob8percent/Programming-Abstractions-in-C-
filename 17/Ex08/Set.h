#pragma once
#include "Library/vector.h"
#include <map>
#include <iostream>
#include <string>

template <typename ValueType>
class Set {
public:
	Set();
	~Set();

	int size() const;
	bool isEmpty() const;
	void add(const ValueType& value);
	void remove(const ValueType& value);

	bool contains(const ValueType& value) const;
	
	void clear();

	//	set2に含まれているかどうか
	bool isSubsetOf(const Set<ValueType>& set2) const;

	bool operator==(const Set<ValueType>& set2) const;
	bool operator!=(const Set<ValueType>& set2) const;

	//	和集合
	Set<ValueType> operator+(const Set<ValueType>& set2) const;
	Set<ValueType> operator+(const ValueType& value) const;
	Set<ValueType>& operator+=(const Set<ValueType>& set2);
	Set<ValueType>& operator+=(const ValueType& value);

	//	積集合
	Set<ValueType> operator*(const Set<ValueType>& set2) const;
	Set<ValueType>& operator*=(const Set<ValueType>& set2);

	//	差集合
	Set<ValueType> operator-(const Set<ValueType>& set2) const;
	Set<ValueType> operator-(const ValueType& value) const;
	Set<ValueType>& operator-=(const Set<ValueType>& set2);
	Set<ValueType>& operator-=(const ValueType& value);
		
	void debug() {
		for (auto p : elements) {
			std::cout << p.first << ", ";
		}
		std::cout << std::endl;
	}

private:
	//	列挙型や文字、範囲のある整数の集合についてはmapを使わずともbool配列として扱える。
	std::unordered_map<ValueType, bool> elements;
};

template <typename ValueType>
Set<ValueType>::Set() {
}

template <typename ValueType>
Set<ValueType>::~Set() {
}

template <typename ValueType>
int Set<ValueType>::size() const {
	return elements.size();
}

template <typename ValueType>
bool Set<ValueType>::isEmpty() const {
	return elements.empty();
}

template <typename ValueType>
void Set<ValueType>::add(const ValueType& value) {
	elements.insert(std::pair(value, true));
}

template <typename ValueType>
void Set<ValueType>::remove(const ValueType& value) {
	elements.erase(value);
}

template <typename ValueType>
bool Set<ValueType>::contains(const ValueType& value) const {
	return elements.contains(value);
}

template <typename ValueType>
void Set<ValueType>::clear() {
	elements.clear();
}

//	set2に含まれているかどうか
template <typename ValueType>
bool Set<ValueType>::isSubsetOf(const Set<ValueType>& set2) const {
	for (std::pair<ValueType, bool> p : elements) {
		if (!set2.contains(p.first))return false;
	}
	return true;
}

template <typename ValueType>
bool Set<ValueType>::operator==(const Set<ValueType>& set2) const {
	return isSubsetOf(set2) && set2.isSubsetOf(*this);
}

template <typename ValueType>
bool Set<ValueType>::operator!=(const Set<ValueType>& set2) const {
	return !((*this) == set2);
}

//	和集合
template <typename ValueType>
Set<ValueType> Set<ValueType>::operator+(const Set<ValueType>& set2) const {
	Set<ValueType> set = *this;
	for (std::pair<ValueType, bool> p : set2.elements) {
		set.add(p.first);
	}
	return set;
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator+(const ValueType& value) const {
	Set<ValueType> set = *this;
	set.add(value);
	return set;
}

template <typename ValueType>
Set<ValueType>& Set<ValueType>::operator+=(const Set<ValueType>& set2) {
	for (std::pair<ValueType, bool> p : set2.elements) {
		add(p.first);
	}
	return *this;
}

template <typename ValueType>
Set<ValueType>& Set<ValueType>::operator+=(const ValueType& value) {
	add(value);
	return *this;
}

//	積集合
template <typename ValueType>
Set<ValueType> Set<ValueType>::operator*(const Set<ValueType>& set2) const {
	Set<ValueType> set;
	for (std::pair<ValueType, bool> p : set2.elements) {
		if (contains(p.first))set.add(p.first);
	}
	return set;
}

template <typename ValueType>
Set<ValueType>& Set<ValueType>::operator*=(const Set<ValueType>& set2) {
	Vector<ValueType> removeVec;
	for (std::pair<ValueType, bool> p : elements) {
		if (!set2.contains(p.first))removeVec += p.first;
	}
	for (int i = 0; i < removeVec.size(); ++i)remove(removeVec[i]);

	return *this;
}

//	差集合
template <typename ValueType>
Set<ValueType> Set<ValueType>::operator-(const Set<ValueType>& set2) const {
	Set<ValueType> set = *this;
	for (std::pair<ValueType, bool> p : set2.elements) {
		if (contains(p.first))set.remove(p.first);
	}
	return set;
}

template <typename ValueType>
Set<ValueType> Set<ValueType>::operator-(const ValueType& value) const {
	Set<ValueType> set = *this;
	if (contains(value))set.remove(value);
	return set;
}

template <typename ValueType>
Set<ValueType>& Set<ValueType>::operator-=(const Set<ValueType>& set2) {
	for (std::pair<ValueType, bool> p : set2.elements) {
		if (contains(p.first))remove(p.first);
	}
	return *this;
}

template <typename ValueType>
Set<ValueType>& Set<ValueType>::operator-=(const ValueType& value) {
	if (contains(value))remove(value);
	return *this;
}

//	================================================================================================
//	char型のときを特殊化
//	================================================================================================
const int RANGE_SIZE = 256;
const int BITS_PER_SIZE = 8;
const int BITS_PER_LONG = BITS_PER_SIZE * sizeof(long);
const int CVEC_WORDS = (RANGE_SIZE + BITS_PER_LONG - 1) / BITS_PER_LONG;
template <>
class Set<char> {
public:
	Set();
	~Set();

	int size() const;
	bool isEmpty() const;
	void add(const char value);
	void remove(const char value);

	bool contains(const char value) const;

	void clear();

	//	set2に含まれているかどうか
	bool isSubsetOf(const Set<char>& set2) const;

	bool operator==(const Set<char>& set2) const;
	bool operator!=(const Set<char>& set2) const;

	//	和集合
	Set<char> operator+(const Set<char>& set2) const;
	Set<char> operator+(const char value) const;
	Set<char>& operator+=(const Set<char>& set2);
	Set<char>& operator+=(const char value);

	//	積集合
	Set<char> operator*(const Set<char>& set2) const;
	Set<char>& operator*=(const Set<char>& set2);

	//	差集合
	Set<char> operator-(const Set<char>& set2) const;
	Set<char> operator-(const char value) const;
	Set<char>& operator-=(const Set<char>& set2);
	Set<char>& operator-=(const char value);

	friend std::ostream& operator<<(std::ostream& os, const Set<char>& set);

	void debug() {
		for (int ch = 0; ch < 128; ++ch) {
			std::cout << size() << "個：";
			if (testBit(ch))std::cout << ch << ", ";
		}
	}

private:
	struct CVector {
		unsigned long words[CVEC_WORDS];
	};

	bool testBit(const char ch) const;	//	chは集合内に存在するか
	void setBit(const char ch);
	void clearBit(const char ch);

	CVector cvector;
	int count;
};


Set<char>::Set() {
	clear();
}

Set<char>::~Set() {
}

int Set<char>::size() const {
	return count;
}

bool Set<char>::isEmpty() const {
	return count == 0;
}

void Set<char>::add(const char value) {
	if (!testBit(value))++count;
	setBit(value);
}

void Set<char>::remove(const char value) {
	clearBit(value);
}

bool Set<char>::contains(const char value) const {
	return testBit(value);
}

bool Set<char>::testBit(const char ch) const {
	if (ch < 0) {
		std::cerr << "ERROR : bool Set<char>::testBit(const char ch) const : "
			<< "chが負です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return cvector.words[ch / BITS_PER_LONG] & (unsigned long(1) << (ch % BITS_PER_LONG));
}

void Set<char>::setBit(const char ch) {
	if (ch < 0) {
		std::cerr << "ERROR : bool Set<char>::setBit(const char ch) const : "
			<< "chが負です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	cvector.words[ch / BITS_PER_LONG] |= (unsigned long(1) << (ch % BITS_PER_LONG));
}

void Set<char>::clearBit(const char ch) {
	if (ch < 0) {
		std::cerr << "ERROR : bool Set<char>::clearBit(const char ch) const : "
			<< "chが負です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	cvector.words[ch / BITS_PER_LONG] &=  ~(unsigned long(1) << (ch % BITS_PER_LONG));
}

void Set<char>::clear() {
	for (int i = 0; i < CVEC_WORDS; ++i) {
		cvector.words[i] = 0;
	}
	count = 0;
}

//	set2に含まれているかどうか
bool Set<char>::isSubsetOf(const Set<char>& set2) const {
	for (int ch = 0; ch < 128; ++ch) {
		if (testBit(ch) && !set2.testBit(ch)) {
			return false;
		}
	}
	return true;
}

bool Set<char>::operator==(const Set<char>& set2) const {
	return isSubsetOf(set2) && set2.isSubsetOf(*this);
}

bool Set<char>::operator!=(const Set<char>& set2) const {
	return !((*this) == set2);
}

//	和集合
Set<char> Set<char>::operator+(const Set<char>& set2) const {
	Set<char> set = *this;
	for (int ch = 0; ch < 128; ++ch) {
		if (set2.testBit(ch)) {
			set.add(ch);
		}
	}
	return set;
}

Set<char> Set<char>::operator+(const char value) const {
	Set<char> set = *this;
	set.add(value);
	return set;
}

Set<char>& Set<char>::operator+=(const Set<char>& set2) {
	for (int ch = 0; ch < 128; ++ch) {
		if (set2.testBit(ch)) {
			add(ch);
		}
	}
	return *this;
}

Set<char>& Set<char>::operator+=(const char value) {
	add(value);
	return *this;
}

//	積集合
Set<char> Set<char>::operator*(const Set<char>& set2) const {
	Set<char> set;
	for (int ch = 0; ch < 128; ++ch) {
		if (contains(ch) && set2.contains(ch)) {
			set.add(ch);
		}
	}
	return set;
}

Set<char>& Set<char>::operator*=(const Set<char>& set2) {
	Vector<char> removeVec;
	for (int ch = 0; ch < 128; ++ch) {
		if (contains(ch) && !set2.contains(ch)) {
			removeVec += ch;
		}
	}
	for (int i = 0; i < removeVec.size(); ++i)remove(removeVec[i]);

	return *this;
}

//	差集合
Set<char> Set<char>::operator-(const Set<char>& set2) const {
	Set<char> set = *this;
	for (int ch = 0; ch < 128; ++ch) {
		if (set2.contains(ch)) {
			set.remove(ch);
		}
	}
	return set;
}

Set<char> Set<char>::operator-(const char value) const {
	Set<char> set = *this;
	if (contains(value))set.remove(value);
	return set;
}

Set<char>& Set<char>::operator-=(const Set<char>& set2) {
	for (int ch = 0; ch < 128; ++ch) {
		if (set2.contains(ch)) {
			remove(ch);
		}
	}
	return *this;
}

Set<char>& Set<char>::operator-=(const char value) {
	if (contains(value))remove(value);
	return *this;
}

