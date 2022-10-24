#pragma once

template <typename ValueType>
class Stack {
public:
	Stack();
	Stack(const Stack<ValueType>& src);
	~Stack();

	int size() const;
	bool isEmpty() const;

	void clear();
	void push(ValueType value);
	ValueType pop();

	ValueType peek() const;

	Stack<ValueType>& operator=(const Stack<ValueType>& src);

private:
	static const int INITIAL_CAPACITY = 10;
	ValueType* elements;
	int capacity;
	int count;

	void deepCopy(const Stack<ValueType>& src);
	void expandCapacity();

};

template <typename ValueType>
Stack<ValueType>::Stack() {
	capacity = INITIAL_CAPACITY;
	elements = new ValueType[capacity];
	count = 0;
}

template <typename ValueType>
Stack<ValueType>::Stack(const Stack<ValueType>& src) {
	deepCopy(src);
}

template <typename ValueType>
Stack<ValueType>::~Stack() {
	delete[] elements;
}

template <typename ValueType>
int Stack<ValueType>::size() const {
	return count;
}

template <typename ValueType>
bool Stack<ValueType>::isEmpty() const {
	return count == 0;
}

template <typename ValueType>
void Stack<ValueType>::clear() {
	count = 0;
}

template <typename ValueType>
void Stack<ValueType>::push(ValueType value) {
	if (count >= capacity) expandCapacity();
	elements[count++] = value;
}

template <typename ValueType>
ValueType Stack<ValueType>::pop() {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType Stack<ValueType>::pop() : スタックが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return elements[--count];
}

template <typename ValueType>
ValueType Stack<ValueType>::peek() const {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType Stack<ValueType>::peek() const : スタックが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return elements[count - 1];
}

template <typename ValueType>
Stack<ValueType>& Stack<ValueType>::operator=(const Stack<ValueType>& src) {
	if (this != &src) {
		delete[] elements;
		deepCopy();
	}

	return *this;
}

template <typename ValueType>
void Stack<ValueType>::expandCapacity() {
	ValueType* oldElements = elements;
	capacity *= 2;
	elements = new ValueType[capacity];
	for (int i = 0; i < count; ++i) {
		elements[i] = oldElements[i];
	}
	delete[] oldElements;
}

template <typename ValueType>
void Stack<ValueType>::deepCopy(const Stack<ValueType>& src) {
	elements = new ValueType[src.capacity];
	for (int i = 0; i < src.count; ++i) {
		elements[i] = src.elements[i];
	}
	count = src.count;
	capacity = src.capacity;
}
