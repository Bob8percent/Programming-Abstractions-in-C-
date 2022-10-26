#pragma once

template <typename ValueType>
class PQueue {
public:
	PQueue();
	PQueue(const PQueue<ValueType>& src);
	~PQueue();

	int size() const;
	bool isEmpty() const;

	void clear();
	void enqueue(ValueType value, double priority);	//	priorityが小さいほど優先度高い
	ValueType dequeue();

	ValueType peek() const;

	void reverse();

	PQueue<ValueType>& operator=(const PQueue<ValueType>& src);

private:
	//	データ構造:線形リスト
	struct Cell {
		ValueType value;
		double priority;
		Cell* link;
	};
	Cell* head;
	Cell* tail;
	int count;

	void deepCopy(const PQueue<ValueType>& src);
};

template <typename ValueType>
PQueue<ValueType>::PQueue() {
	count = 0;
	head = nullptr;
	tail = nullptr;
}

template <typename ValueType>
PQueue<ValueType>::PQueue(const PQueue<ValueType>& src) {
	deepCopy(src);
}

template <typename ValueType>
PQueue<ValueType>::~PQueue() {
	clear();
}

template <typename ValueType>
int PQueue<ValueType>::size() const {
	return count;
}

template <typename ValueType>
bool PQueue<ValueType>::isEmpty() const {
	return count == 0;
}

template <typename ValueType>
void PQueue<ValueType>::clear() {
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
void PQueue<ValueType>::enqueue(ValueType value, double priority) {
	Cell* newCell = new Cell;
	newCell->value = value;
	newCell->priority = priority;
	newCell->link = nullptr;
	if (isEmpty()) {
		head = newCell;
		tail = newCell;
	}
	else {
		Cell* cp = head;
		Cell* oldCell = nullptr;
		while (cp) {
			if (cp->priority > priority) {
				if (oldCell)oldCell->link = newCell;
				else head = newCell;
				newCell->link = cp;
				break;
			}

			oldCell = cp;
			cp = cp->link;
		}
		if (!cp) {
			oldCell->link = newCell;
			tail = newCell;
		}
	}

	++count;
}

template <typename ValueType>
ValueType PQueue<ValueType>::dequeue() {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType PQueue<ValueType>::dequeue() : キューが空です" << std::endl;
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
ValueType PQueue<ValueType>::peek() const {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType PQueue<ValueType>::peek() : キューが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return head->value;
}

template <typename ValueType>
void PQueue<ValueType>::reverse() {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> void PQueue<ValueType>::reverse() : キューが空です" << std::endl;
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
PQueue<ValueType>& PQueue<ValueType>::operator=(const PQueue<ValueType>& src) {
	if (this != &src) {
		clear();
		deepCopy();
	}
	return *this;
}

template <typename ValueType>
void PQueue<ValueType>::deepCopy(const PQueue<ValueType>& src) {
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



