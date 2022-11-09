#pragma once
#include <utility>
#include "Library/vector.h"

template <typename ValueType>
class Heap
{
public:
	struct Cell {
		int priority;	//	小さいほど優先度高い
		ValueType value;
	};

	int parentIndex(int n) const;
	int leftChildIndex(int n) const;
	int rightChildIndex(int n) const;

	void add(int priority, const ValueType& value);
	ValueType removeRoot();
	ValueType peekRoot() const;

	void clear();

	int size() const;
	bool isEmpty() const;

	void display() const;
	void display(int idx, int height) const;

private:
	//	簡単のためベクターを使う
	Vector<Cell> elements;

	void reBalace();
};

template <typename ValueType>
int Heap<ValueType>::parentIndex(int n) const {
	return (n - 1) / 2;
}

template <typename ValueType>
int Heap<ValueType>::leftChildIndex(int n) const{
	return 2 * n + 1;
}

template <typename ValueType>
int Heap<ValueType>::rightChildIndex(int n) const{
	return 2 * n + 2;
}

template <typename ValueType>
void Heap<ValueType>::add(int priority, const ValueType& value) {
	Cell cell;
	cell.priority = priority;
	cell.value = value;
	elements.add(cell);
	
	int n = elements.size() - 1;
	while (n > 0) {
		int parent = parentIndex(n);
		if (elements[parent].priority > elements[n].priority) {
			std::swap(elements[parent], elements[n]);
			n = parent;
		}
		else break;
	}
}

template <typename ValueType>
ValueType Heap<ValueType>::removeRoot() {
	if (elements.size() <= 0) {
		std::cerr << "ERROR : void Heap<ValueType>::removeRoot() : "
			<< "要素が空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	//	0の要素とnの要素を入れ替え、nの要素を削除
	int n = elements.size() - 1;
	ValueType result = elements[0].value;
	elements[0] = elements[n];
	elements.remove(n);

	reBalace();

	return result;
}

template <typename ValueType>
ValueType Heap<ValueType>::peekRoot() const {
	return elements[0].value;
}

template <typename ValueType>
void Heap<ValueType>::reBalace() {
	int n = 0;
	while (1) {
		int left = leftChildIndex(n);
		int right = leftChildIndex(n);
		
		bool isEnd = true;

		if ((left < elements.size()) && (elements[left].priority < elements[n].priority)) {
			std::swap(elements[left], elements[n]);
			n = left;
			isEnd = false;
		}
		if ((right < elements.size()) && (elements[right].priority < elements[n].priority)) {
			std::swap(elements[right], elements[n]);
			n = right;
			isEnd = false;
		}

		if (isEnd)break;
	}
}

template <typename ValueType>
void Heap<ValueType>::clear() {
	elements.clear();
}

template <typename ValueType>
int Heap<ValueType>::size() const {
	return elements.size();
}

template <typename ValueType>
bool Heap<ValueType>::isEmpty() const {
	return elements.isEmpty();
}

template <typename ValueType>
void Heap<ValueType>::display() const {
	display(0, 0);
}

template <typename ValueType>
void Heap<ValueType>::display(int idx, int height) const {
	if (idx >= elements.size())return;

	display(rightChildIndex(idx), height + 1);
	for (int i = 0; i < height; ++i)std::cout << "  ";
	std::cout << elements[idx].value << "(" << elements[idx].priority << ")" << std::endl;
	display(leftChildIndex(idx), height + 1);
}
