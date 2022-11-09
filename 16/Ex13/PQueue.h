#pragma once
#include "Heap.h"

template <typename ValueType>
class PQueue {
public:
	PQueue();
	~PQueue();

	int size() const;
	bool isEmpty() const;

	void clear();
	void enqueue(ValueType value, int priority);	//	priorityが小さいほど優先度高い
	ValueType dequeue();

	ValueType peek() const;

	void debug();

private:
	Heap<ValueType> elements;
};

template <typename ValueType>
PQueue<ValueType>::PQueue() {
}

template <typename ValueType>
PQueue<ValueType>::~PQueue() {
}

template <typename ValueType>
int PQueue<ValueType>::size() const {
	return elements.size();
}

template <typename ValueType>
bool PQueue<ValueType>::isEmpty() const {
	return elements.isEmpty();
}

template <typename ValueType>
void PQueue<ValueType>::clear() {
	elements.clear();
}

template <typename ValueType>
void PQueue<ValueType>::enqueue(ValueType value, int priority) {
	elements.add(priority, value);
}

template <typename ValueType>
ValueType PQueue<ValueType>::dequeue() {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType PQueue<ValueType>::dequeue() : キューが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return elements.removeRoot();
}

template <typename ValueType>
ValueType PQueue<ValueType>::peek() const {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType PQueue<ValueType>::peek() : キューが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return elements.peekRoot();
}

template <typename ValueType>
void PQueue<ValueType>::debug() {
	elements.display();
}

