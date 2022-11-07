#pragma once
#include "BinarySearchTree.h"

template<typename KeyType, typename ValueType>
class Map
{
public:
	Map();
	Map(const Map<KeyType, ValueType>& src);
	~Map();

	ValueType get(const KeyType& key) const;
	void put(const KeyType& key, const ValueType& value);

	int size() const;

	void remove(const KeyType& key);
	bool containsKey(const KeyType& key);

	void clear();

	void debug();

	Map<KeyType, ValueType>& operator=(const Map<KeyType, ValueType>& src);
	ValueType& operator[](const KeyType& key);

private:
	BinarySearchTree<KeyType, ValueType> elements;
};

template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map() {
}

template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::Map(const Map<KeyType, ValueType>& src) {
	elements = src.elements;
}

template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>::~Map() {
}

template<typename KeyType, typename ValueType>
ValueType Map<KeyType, ValueType>::get(const KeyType& key) const {
	return elements.getValue(key);
}

template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::put(const KeyType& key, const ValueType& value) {
	elements.insertNode(key, value);
}

template<typename KeyType, typename ValueType>
int Map<KeyType, ValueType>::size() const {
	return elements.size();
}

template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::remove(const KeyType& key) {
	elements.removeNode(key);
}

template<typename KeyType, typename ValueType>
bool Map<KeyType, ValueType>::containsKey(const KeyType& key) {
	return elements.containsKey(key);
}

template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::clear() {
	elements.clear();
}

template<typename KeyType, typename ValueType>
Map<KeyType, ValueType>& Map<KeyType, ValueType>::operator=(const Map<KeyType, ValueType>& src) {
	if (this != &src) {
		elements = src.elements;
	}
	return *this;
}

template<typename KeyType, typename ValueType>
ValueType& Map<KeyType, ValueType>::operator[](const KeyType& key) {
	return elements.getValue(key);
}

template<typename KeyType, typename ValueType>
void Map<KeyType, ValueType>::debug() {
	elements.displayKey();
}
