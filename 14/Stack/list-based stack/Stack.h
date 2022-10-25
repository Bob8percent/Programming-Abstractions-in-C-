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
	//	データ構造：線形リスト
	struct Cell {
		ValueType value;
		Cell* link;	//	前のcellへのポインタ
	};
	int count;
	Cell* list;	//	末尾のcellへのポインタ

	void deepCopy(const Stack<ValueType>& src);
};

template <typename ValueType>
Stack<ValueType>::Stack() {
	count = 0;
	list = nullptr;
}

template <typename ValueType>
Stack<ValueType>::Stack(const Stack<ValueType>& src) {
	deepCopy(src);
}

template <typename ValueType>
Stack<ValueType>::~Stack() {
	clear();
}

template <typename ValueType>
int Stack<ValueType>::size() const {
	return count;
}

template <typename ValueType>
bool Stack<ValueType>::isEmpty() const {
	return count == 0;
}

//	O(N)
template <typename ValueType>
void Stack<ValueType>::clear() {
	while (!isEmpty())pop();
}

template <typename ValueType>
void Stack<ValueType>::push(ValueType value) {
	Cell* newCell = new Cell;
	newCell->value = value;
	newCell->link = list;
	list = newCell;
	++count;
}

template <typename ValueType>
ValueType Stack<ValueType>::pop() {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType Stack<ValueType>::pop() : スタックが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Cell* cp = list;
	ValueType result = list->value;
	list = list->link;
	--count;
	delete cp;

	return result;
}

template <typename ValueType>
ValueType Stack<ValueType>::peek() const {
	if (isEmpty()) {
		std::cerr << "ERROR : template <typename ValueType> ValueType Stack<ValueType>::peek() const : スタックが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return list->value;
}

template <typename ValueType>
Stack<ValueType>& Stack<ValueType>::operator=(const Stack<ValueType>& src) {
	if (this != &src) {
		clear();
		deepCopy();
	}

	return *this;
}

template <typename ValueType>
void Stack<ValueType>::deepCopy(const Stack<ValueType>& src) {
	Cell* cp = src.list;
	Cell* oldCell = nullptr;
	while (cp) {
		Cell* newCell = new Cell;
		newCell->value = cp->value;
		newCell->link = nullptr;
		if (!oldCell) list = newCell;
		else oldCell->link = newCell;
		oldCell = newCell;
		cp = cp->link;
	}

	count = src.count;
}
