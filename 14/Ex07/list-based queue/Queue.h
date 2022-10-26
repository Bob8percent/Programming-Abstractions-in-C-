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
	//	データ構造:線形リスト
	struct Cell {
		ValueType value;
		Cell* link;
	};
	Cell* head;
	Cell* tail;
	int count;

	void deepCopy(const Queue<ValueType>& src);
};

template <typename ValueType>
Queue<ValueType>::Queue() {
	count = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename ValueType>
Queue<ValueType>::Queue(const Queue<ValueType>& src) {
	deepCopy(src);
}

template <typename ValueType>
Queue<ValueType>::~Queue() {
	clear();
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
	while (head) {
		Cell* cp = head;
		head = head->link;
		delete cp;
	}
	head = nullptr;
	tail = nullptr;

	count = 0;
}

template <typename ValueType>
void Queue<ValueType>::enqueue(ValueType value) {
	Cell* newCell = new Cell;
	newCell->value = value;
	newCell->link = nullptr;
	if (isEmpty()) head = newCell;
	else tail->link = newCell;

	++count;
	tail = newCell;
}

template <typename ValueType>
ValueType Queue<ValueType>::dequeue() {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType Queue<ValueType>::dequeue() : キューが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	--count;
	Cell* cp = head;
	ValueType result = cp->value;
	head = head->link;
	delete cp;
	cp = nullptr;	//	head==tailだったときのため
	return result;
}

template <typename ValueType>
ValueType Queue<ValueType>::peek() const {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType Queue<ValueType>::peek() : キューが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return head->value;
}

template <typename ValueType>
void Queue<ValueType>::reverse() {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> void Queue<ValueType>::reverse() : キューが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Cell* cp = head;
	Cell* oldCell = nullptr;
	while (cp) {
		Cell* next = cp->link;

		if (!oldCell)cp->link = nullptr;	//	cp == head
		else cp->link = oldCell;

		oldCell = cp;
		cp = next;
	}

	Cell* tmp = head;
	head = tail;
	tail = tmp;
}

template <typename ValueType>
Queue<ValueType>& Queue<ValueType>::operator=(const Queue<ValueType>& src) {
	if (this != &src) {
		clear();
		deepCopy();
	}
	return *this;
}

template <typename ValueType>
void Queue<ValueType>::deepCopy(const Queue<ValueType>& src) {
	Cell* cp = src.head;
	tail = nullptr;
	while (cp) {
		Cell* newCell = new Cell;
		newCell->value = cp->value;
		newCell->link = nullptr;
		if (!tail)head = newCell;
		else tail->link = newCell;

		tail = newCell;
		cp = cp->link;
	}

	count = src.count;
}



