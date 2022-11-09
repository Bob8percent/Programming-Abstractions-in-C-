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

	friend std::ostream& operator<<(std::ostream& os, const Set<ValueType>& set);
		
	void debug() {
		for (auto p : elements) {
			std::cout << p.first << ", ";
		}
		std::cout << std::endl;
	}

private:
	//	列挙型や文字、範囲のある整数の集合についてはmapを使わずともbool配列として扱える。
	std::map<ValueType, bool> elements;
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

//	汎用性のある処理は書かないので部分的特殊化を行わない
void operator>>(std::istream& is, Set<char>& set) {
	std::string str;
	std::getline(is, str);
	
	int cp = 0;
	while (str.at(cp++) != '{'){}

	while (1) {
		while (str.at(cp) == ' ') { ++cp; }
		
		set.add(str.at(cp++));

		while (str.at(cp) == ' ') { ++cp; }

		if (str.at(cp) == '}')break;

		if (str.at(cp++) != ',') {
			std::cerr << "ERROR : std::istream& operator>>(std::istream& is, Set<char>& set) : "
				<< "入力が不適です" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
}

void operator>>(std::istream& is, Set<std::string>& set) {
	std::string str;
	std::getline(is, str);

	int cp = 0;
	while (str.at(cp++) != '{') {}

	while (1) {
		std::string s;
		while ((str.at(cp) != ','))s += str.at(cp++);
		set.add(s);

		if (str.at(cp) == '}')break;
	}
}

void operator>>(std::istream& is, Set<int>& set) {
	std::string str;
	std::getline(is, str);

	int cp = 0;
	while (str.at(cp++) != '{') {}

	while (1) {
		while (str.at(cp) == ' ') { ++cp; }

		std::string snum;
		while (isdigit(str.at(cp))) {
			snum += str.at(cp++);
			if (str.at(cp) == ' ' || str.at(cp) == ',')break;
		}

		int num = 0;
		int digit = 1;
		for (int i = 0; i < snum.length(); ++i) {
			num += (snum.at(snum.length() - i - 1) - '0') * digit;
			digit *= 10;
		}
		set.add(num);

		while (str.at(cp) == ' ') { ++cp; }

		if (str.at(cp) == '}')break;

		if (str.at(cp++) != ',') {
			std::cerr << "ERROR : std::istream& operator>>(std::istream& is, Set<char>& set) : "
				<< "入力が不適です" << std::endl;
			std::exit(EXIT_FAILURE);
		}
	}
}

std::ostream& operator<<(std::ostream& os, const Set<char>& set) {
	os << "{";
	int count = 0;
	for (std::pair<char, bool> p : set.elements) {
		os << p.first;
		if ((++count) < set.size())os << ", ";
	}
	os << "}";
	return os;
}


