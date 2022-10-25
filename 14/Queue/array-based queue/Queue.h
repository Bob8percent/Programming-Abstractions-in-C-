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

	Queue<ValueType>& operator=(const Queue<ValueType>& src);

private:
	//	データ構造:配列
	ValueType* elements;
	static const int INITIAL_CAPACITY = 10;
	int capacity;
	//	ring Buffer
	int head;	//	配列の先頭のインデックス
	int tail;	//	配列の末尾のインデックス

	void deepCopy(const Queue<ValueType>& src);
	void expandCapacity();
};

template <typename ValueType>
Queue<ValueType>::Queue() {
	capacity = INITIAL_CAPACITY;
	elements = new ValueType[capacity];
	head = 0;
	tail = 0;
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
	return (tail + capacity - head) % capacity;
}

template <typename ValueType>
bool Queue<ValueType>::isEmpty() const {
	return head == tail;
}

template <typename ValueType>
void Queue<ValueType>::clear() {
	head = 0;
	tail = 0;
}

template <typename ValueType>
void Queue<ValueType>::enqueue(ValueType value) {
	if (size() + 1 >= capacity)expandCapacity();

	elements[tail] = value;
	tail = (tail + 1) % capacity;
}

template <typename ValueType>
ValueType Queue<ValueType>::dequeue() {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType Queue<ValueType>::dequeue() : キューが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	ValueType result = elements[head];
	head = (head + 1) % capacity;
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
	int count = src.size();
	for (int i = 0; i < count; ++i) {
		elements[i] = src.elements[(src.head + i) % src.capacity];
	}
	head = 0;
	tail = count;
}

template <typename ValueType>
void Queue<ValueType>::expandCapacity() {
	ValueType* newElements = new ValueType[capacity * 2];
	int count = size();
	for (int i = 0; i < count; ++i) {
		newElements[i] = elements[(head + i) % capacity];
	}

	capacity *= 2;
	head = 0;
	tail = count;
	delete[] elements;
	elements = newElements;
}



