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
	ValueType* elements;
	static const int INITIAL_CAPACITY = 10;
	int capacity;
	int count;

	void deepCopy(const Vector<ValueType>& src);
	void expandCapacity();
};

template <typename ValueType>
Vector<ValueType>::Vector() {
	capacity = INITIAL_CAPACITY;
	elements = new ValueType[capacity];
	count = 0;
}

template <typename ValueType>
Vector<ValueType>::Vector(int n, ValueType value/* = ValueType()*/) {
	capacity = INITIAL_CAPACITY;
	if (capacity < n)capacity = n;
	elements = new ValueType[capacity];
	for (int i = 0; i < n; ++i)elements[i] = value;
	count = n;
}
template <typename ValueType>
Vector<ValueType>::Vector(const Vector<ValueType>& src) {
	deepCopy(src);
}

template <typename ValueType>
Vector<ValueType>::~Vector() {
	delete[] elements;
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
	if (count >= capacity)expandCapacity();

	//	シフト
	for (int i = count; i > index; --i) {
		elements[i] = elements[i - 1];
	}

	//	挿入
	elements[index] = value;

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

	//	シフト
	for (int i = index; i < count - 1; ++i) {
		elements[i] = elements[i + 1];
	}

	--count;
}

template <typename ValueType>
void Vector<ValueType>::add(ValueType value) {
	if (count >= capacity)expandCapacity();

	elements[count++] = value;
}

template <typename ValueType>
ValueType& Vector<ValueType>::operator[] (int index) {
	if (index < 0 || count <= index) {
		std::cerr << "ERROR : template <typename ValueType> ValueType & Vector<ValueType>::operator[] (int index) : "
			<< "indexが範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return elements[index];
}

template <typename ValueType>
Vector<ValueType>& Vector<ValueType>::operator=(const Vector<ValueType>& src) {
	if (this != &src) {
		delete[] elements;
		deepCopy();
	}
	return *this;
}

template <typename ValueType>
void Vector<ValueType>::deepCopy(const Vector<ValueType>& src) {
	capacity = src.capacity;
	count = src.count;
	elements = new ValueType[capacity];
	for (int i = 0; i < count; ++i) {
		elements[i] = src.elements[i];
	}
}

template <typename ValueType>
void Vector<ValueType>::expandCapacity() {
	capacity *= 2;
	ValueType* newElements = new ValueType[capacity];
	for (int i = 0; i < count; ++i) {
		newElements[i] = elements[i];
	}

	delete[] elements;
	elements = newElements;
}
