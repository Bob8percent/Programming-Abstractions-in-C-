#pragma once
#include "Library/vector.h"
#include <map>

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
	Set<ValueType> set = *this;
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
