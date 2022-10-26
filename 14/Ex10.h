#pragma once

template <typename ValueType>
class Vector {
public:
	Vector();
	Vector(int n, ValueType value = ValueType());
	Vector(const Vector<ValueType>& src);
	~Vector();

	int size() const;
	bool isEmpty() const;
	void clear();

	void insert(int index, ValueType value);	//	index以降は1つシフト
	void remove(int index);						//	同上

	void add(ValueType value);

	ValueType& operator[] (int index);

	Vector<ValueType>& operator=(const Vector<ValueType>& src);

private:
	struct Cell {
		ValueType value;
		Cell* link;
	};
	Cell* head;
	Cell* tail;
	int count;

	void deepCopy(const Vector<ValueType>& src);
};

template <typename ValueType>
Vector<ValueType>::Vector() {
	head = nullptr;
	tail = nullptr;
	count = 0;
}

template <typename ValueType>
Vector<ValueType>::Vector(int n, ValueType value/* = ValueType()*/) {
	if (n <= 0) {
		std::cerr << "template <typename ValueType> Vector<ValueType>::Vector(int n, ValueType value = ValueType()) : "
			<< "nは正でなければいけません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	count = n;

	Cell* oldCell = nullptr;
	while (n--) {
		Cell* cell = new Cell;
		cell->value = value;
		cell->link = nullptr;
		if (oldCell)oldCell->link = cell;
		else head = cell;

		oldCell = cell;
	}
	tail = oldCell;
}
template <typename ValueType>
Vector<ValueType>::Vector(const Vector<ValueType>& src) {
	deepCopy(src);
}

template <typename ValueType>
Vector<ValueType>::~Vector() {
	clear();
}

template <typename ValueType>
int Vector<ValueType>::size() const {
	return count;
}

template <typename ValueType>
bool Vector<ValueType>::isEmpty() const {
	return count == 0;
}

template <typename ValueType>
void Vector<ValueType>::clear() {
	while (head) {
		Cell* cp = head;
		head = head->link;
		delete cp;
	}
	head = nullptr;
	tail = nullptr;
	count = 0;
}

//	O(N)
template <typename ValueType>
void Vector<ValueType>::insert(int index, ValueType value) {
	if (index < 0 || count <= index) {
		std::cerr << "ERROR : template <typename ValueType> void Vector<ValueType>::insert(int index, ValueType value) : "
			<< "indexが範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Cell* cell = new Cell;
	cell->value = value;
	cell->link = nullptr;

	Cell* cp = head;
	Cell* oldCell = nullptr;
	while (index--) {
		oldCell = cp;
		cp = cp->link;
	}

	if (!oldCell) head = cell;
	else oldCell->link = cell;
	cell->link = cp;

	++count;
}

//	O(N)
template <typename ValueType>
void Vector<ValueType>::remove(int index) {
	if (index < 0 || count <= index) {
		std::cerr << "ERROR : template <typename ValueType> void Vector<ValueType>::remove(int index) : "
			<< "indexが範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Cell* cp = head;
	Cell* oldCell = nullptr;
	while (index--) {
		oldCell = cp;
		cp = cp->link;
	}

	if (!oldCell)head = head->link;
	else oldCell->link = cp->link;

	delete cp;
	cp = nullptr;
	if (!tail)tail = oldCell;

	--count;
}

template <typename ValueType>
void Vector<ValueType>::add(ValueType value) {
	Cell* cell = new Cell;
	cell->value = value;
	cell->link = nullptr;

	if (isEmpty()) {
		head = cell;
		tail = cell;
	}
	else {
		tail->link = cell;
		tail = cell;
	}

	++count;
}

template <typename ValueType>
ValueType& Vector<ValueType>::operator[] (int index) {
	if (index < 0 || count <= index) {
		std::cerr << "ERROR : template <typename ValueType> ValueType & Vector<ValueType>::operator[] (int index) : "
			<< "indexが範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Cell* cp = head;
	while (index--)cp = cp->link;
	return cp->value;
}

template <typename ValueType>
Vector<ValueType>& Vector<ValueType>::operator=(const Vector<ValueType>& src) {
	if (this != &src) {
		clear();
		deepCopy();
	}
	return *this;
}

template <typename ValueType>
void Vector<ValueType>::deepCopy(const Vector<ValueType>& src) {
	Cell* cp = src.head;
	Cell* oldCell = nullptr;
	while (cp) {
		Cell* cell = new Cell;
		cell->value = cp->value;
		cell->link = nullptr;
		if (oldCell)oldCell->link = cell;
		else head = cell;
		oldCell = cell;
		cp = cp->link;
	}
	tail = oldCell;
	count = src.count;
}

