#pragma once

template <typename ValueType>
class Queue {
public:
	Queue();
	Queue(const Queue<ValueType>& src);
	~Queue();

	int size() const;
	bool isEmpty() const;

	void clear();
	void enqueue(ValueType value);
	ValueType dequeue();

	ValueType peek() const;

	void reverse();

	Queue<ValueType>& operator=(const Queue<ValueType>& src);

private:
	//	データ構造:配列
	ValueType* elements;
	static const int INITIAL_CAPACITY = 10;
	int capacity;
	//	ring Buffer
	int head;	//	配列の先頭のインデックス
	int count;

	void deepCopy(const Queue<ValueType>& src);
	void expandCapacity();
};

template <typename ValueType>
Queue<ValueType>::Queue() {
	capacity = INITIAL_CAPACITY;
	elements = new ValueType[capacity];
	head = 0;
	count = 0;
}

template <typename ValueType>
Queue<ValueType>::Queue(const Queue<ValueType>& src) {
	deepCopy(src);
}

template <typename ValueType>
Queue<ValueType>::~Queue() {
	delete[] elements;
}

template <typename ValueType>
int Queue<ValueType>::size() const {
	return count;
}

template <typename ValueType>
bool Queue<ValueType>::isEmpty() const {
	return count == 0;
}

template <typename ValueType>
void Queue<ValueType>::clear() {
	count = 0;
}

template <typename ValueType>
void Queue<ValueType>::enqueue(ValueType value) {
	if (count >= capacity)expandCapacity();

	elements[(head + count) % capacity] = value;
	++count;
}

template <typename ValueType>
ValueType Queue<ValueType>::dequeue() {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType Queue<ValueType>::dequeue() : キューが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	ValueType result = elements[head];
	head = (head + 1) % capacity;
	--count;
	return result;
}

template <typename ValueType>
ValueType Queue<ValueType>::peek() const {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType Queue<ValueType>::peek() : キューが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return elements[head];
}

template <typename ValueType>
void Queue<ValueType>::reverse() {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> void Queue<ValueType>::reverse() : キューが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	for (int i = 0; i < count / 2; ++i) {
		int i1 = (head + i) % capacity;
		int i2 = (head + count - i - 1) % capacity;
		ValueType tmp = elements[i1];
		elements[i1] = elements[i2];
		elements[i2] = tmp;
	}
}

template <typename ValueType>
Queue<ValueType>& Queue<ValueType>::operator=(const Queue<ValueType>& src) {
	if (this != &src) {
		delete[] elements;
		deepCopy();
	}
	return *this;
}

template <typename ValueType>
void Queue<ValueType>::deepCopy(const Queue<ValueType>& src) {
	capacity = src.capacity;
	elements = new ValueType[capacity];
	count = src.count;
	head = 0;
	for (int i = 0; i < count; ++i) {
		elements[i] = src.elements[(src.head + i) % src.capacity];
	}
}

template <typename ValueType>
void Queue<ValueType>::expandCapacity() {
	ValueType* newElements = new ValueType[capacity * 2];
	for (int i = 0; i < count; ++i) {
		newElements[i] = elements[(head + i) % capacity];
	}

	capacity *= 2;
	head = 0;
	delete[] elements;
	elements = newElements;
}


