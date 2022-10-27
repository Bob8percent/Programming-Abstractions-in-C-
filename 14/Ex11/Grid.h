#pragma once
#include "_Vector.h"

template <typename ValueType>
class Grid {
public:
	Grid();
	Grid(int rows, int cols);
	Grid(const Grid<ValueType>& src);
	~Grid();

	int numRows();
	int numCols();

	bool inBounds(int rows, int cols);

	void resize(int rows, int cols);

	Vector<ValueType>& operator[](int index);

	Vector<ValueType>& operator= (const Grid<ValueType>& src);

private:
	Vector<ValueType>* elements;
	int mNumRows;
	int mNumCols;

	void deepCopy(const Grid<ValueType>& src);
};

template <typename ValueType>
Grid<ValueType>::Grid() {
	mNumCols = 0;
	mNumRows = 0;
}

template <typename ValueType>
Grid<ValueType>::Grid(int rows, int cols) {
	mNumCols = cols;
	mNumRows = rows;
	elements = new Vector<ValueType>[rows];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			elements[i].add(0);
		}
	}
}

template <typename ValueType>
Grid<ValueType>::Grid(const Grid<ValueType>& src) {
	deepCopy(src);
}

template <typename ValueType>
Grid<ValueType>::~Grid() {
	delete[] elements;
}


template <typename ValueType>
int Grid<ValueType>::numRows() {
	return mNumRows;
}

template <typename ValueType>
int Grid<ValueType>::numCols() {
	return mNumCols;
}

template <typename ValueType>
bool Grid<ValueType>::inBounds(int rows, int cols) {
	return (0 <= rows && rows < mNumRows) && (0 <= cols && cols < mNumCols);
}

template <typename ValueType>
void Grid<ValueType>::resize(int rows, int cols) {
	Vector<ValueType>* newElements = new Vector<ValueType>[rows];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (inBounds(i, j))newElements[i].add(elements[i][j]);
			else newElements[i].add(0);
		}
	}
	mNumCols = cols;
	mNumRows = rows;
	delete[] elements;
	elements = newElements;
}

template <typename ValueType>
Vector<ValueType>& Grid<ValueType>::operator[](int index) {
	if (index < 0 || mNumRows <= index) {
		std::cerr << "ERROR : template <typename ValueType> Vector<ValueType>&Grid<ValueType>::operator[](int index) : "
			<< "範囲外の行を指定しています" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return elements[index];
}

template <typename ValueType>
Vector<ValueType>& Grid<ValueType>::operator= (const Grid<ValueType>& src) {
	if (this != &src) {
		delete[] elements;
		deepCopy(src);
	}

	return *this;
}

template <typename ValueType>
void Grid<ValueType>::deepCopy(const Grid<ValueType>& src) {
	mNumRows = src.mNumRows;
	mNumCols = src.mNumCols;

	Vector<ValueType>* newElements = new Vector<ValueType>[mNumRows];
	for (int i = 0; i < mNumRows; ++i) {
		for (int j = 0; j < mNumCols; ++j) {
			newElements[i].add(src.elements[i][j]);
		}
	}
	elements = newElements;
}
