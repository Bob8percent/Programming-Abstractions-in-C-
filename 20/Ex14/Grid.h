#pragma once
#include <vector>

template<typename ValueType>
class GridIterator;

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

	std::vector<ValueType>& operator[](int index) const;

	std::vector<ValueType>& operator= (const Grid<ValueType>& src);

	typedef GridIterator<ValueType> iterator;
	iterator begin() {
		return GridIterator(this, 0, 0);
	}
	iterator end() {
		return GridIterator(this, mNumRows, 0);
	}

private:
	std::vector<ValueType>* elements;
	int mNumRows;
	int mNumCols;

	void deepCopy(const Grid<ValueType>& src);

	friend class GridIterator<ValueType>;
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
	elements = new std::vector<ValueType>[rows];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			elements[i].push_back(0);
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
	std::vector<ValueType>* newElements = new std::vector<ValueType>[rows];
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			if (inBounds(i, j))newElements[i].push_back(elements[i][j]);
			else newElements[i].add(0);
		}
	}
	mNumCols = cols;
	mNumRows = rows;
	delete[] elements;
	elements = newElements;
}

template <typename ValueType>
std::vector<ValueType>& Grid<ValueType>::operator[](int index) const {
	if (index < 0 || mNumRows <= index) {
		std::cerr << "ERROR : template <typename ValueType> std::vector<ValueType>&Grid<ValueType>::operator[](int index) : "
			<< "範囲外の行を指定しています" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	return elements[index];
}

template <typename ValueType>
std::vector<ValueType>& Grid<ValueType>::operator= (const Grid<ValueType>& src) {
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

	std::vector<ValueType>* newElements = new std::vector<ValueType>[mNumRows];
	for (int i = 0; i < mNumRows; ++i) {
		for (int j = 0; j < mNumCols; ++j) {
			newElements[i].push_back(src.elements[i][j]);
		}
	}
	elements = newElements;
}

/*
* =================================================================================================
* GridIteratorクラスの実装
* 
* 行優先のイテレーター
* =================================================================================================
*/
template <typename ValueType>
class GridIterator {
public:
	GridIterator() {
		grid = nullptr;
	}
	ValueType& operator*() {
		if (!grid) {
			std::cerr << "ERROR : ValueType& GridIterator::operator*() : "
				<< "gridが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return (*grid)[row][col];
	}

	ValueType* operator->() {
		if (!grid) {
			std::cerr << "ERROR : ValueType* GridIterator::operator->() : "
				<< "gridが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return &(*grid)[row][col];	//	アドレスを返す
	}

	bool operator==(const GridIterator<ValueType>& rhs) {
		if (grid != rhs.grid) {
			std::cerr << "ERROR : bool GridIterator::operator==(const GridIterator<ValueType>& rhs) : "
				<< "vpと異なるVectorです" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return (row == rhs.row) && (col == rhs.col);
	}

	bool operator!=(const GridIterator<ValueType>& rhs) {
		if (grid != rhs.grid) {
			std::cerr << "ERROR : bool GridIterator::operator!=(const GridIterator<ValueType>& rhs) : "
				<< "gridとrhs.gridが異なります" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return !((*this) == rhs);
	}

	GridIterator<ValueType>& operator++() {
		if (!grid) {
			std::cerr << "ERROR : ValueType& GridIterator::operator++() : "
				<< "gridが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		int linearNum = row * grid->mNumCols + col + 1;
		row = linearNum / grid->mNumCols;
		col = linearNum % grid->mNumCols;
		return *this;
	}
	GridIterator<ValueType> operator++(int) {
		if (!grid) {
			std::cerr << "ERROR : ValueType GridIterator::operator++(int) : "
				<< "gridが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		GridIterator copy(*this);	//	デフォルトのコピーコンストラクタ(浅いコピーでOK)
		++(*this);
		return copy;
	}
	
private:
	const Grid<ValueType>* grid;
	int row;
	int col;

	GridIterator(Grid<ValueType>* grid, int row, int col) {
		this->grid = grid;
		this->row = row;
		this->col = col;
	}

	friend class Grid<ValueType>;
};
