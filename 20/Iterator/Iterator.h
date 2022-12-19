#pragma once
#include "Library/vector.h"
#include <iostream>

/*
* =================================================================================================
* Vectorのイテレータークラス(Random Access Iterator)
* =================================================================================================
*/
template <typename ValueType>
class Iterator
{
public:
	Iterator() {
		vp = nullptr;
	}

	ValueType& operator*() {
		if (!vp) {
			std::cerr << "ERROR : ValueType& Iterator::operator*() : "
				<< "vpが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return vp[index];
	}

	ValueType* operator->() {
		if (!vp) {
			std::cerr << "ERROR : ValueType* Iterator::operator->() : "
				<< "vpが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return &vp[index];	//	アドレスを返す
	}

	ValueType& operator[](int k) {
		if (!vp) {
			std::cerr << "ERROR : ValueType& Iterator::operator[](int k) : "
				<< "vpが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return vp[index + k];
	}

	bool operator==(const Iterator<ValueType>& rhs) {
		if (vp != rhs.vp) {
			std::cerr << "ERROR : bool Iterator::operator==(const Iterator<ValueType>& rhs) : "
				<< "vpと異なるVectorです" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return (vp == rhs.vp) && (index == rhs.index);
	}

	bool operator!=(const Iterator<ValueType>& rhs) {
		if (vp != rhs.vp) {
			std::cerr << "ERROR : bool Iterator::operator!=(const Iterator<ValueType>& rhs) : "
				<< "vpと異なるVectorです" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return !(this == rhs);
	}

	bool operator<(const Iterator<ValueType>& rhs) {
		if (vp != rhs.vp) {
			std::cerr << "ERROR : bool Iterator::operator<(const Iterator<ValueType>& rhs) : "
				<< "vpと異なるVectorです" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return index < rhs.index;
	}
	bool operator>(const Iterator<ValueType>& rhs) {
		if (vp != rhs.vp) {
			std::cerr << "ERROR : bool Iterator::operator>(const Iterator<ValueType>& rhs) : "
				<< "vpと異なるVectorです" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return index > rhs.index;
	}
	bool operator<=(const Iterator<ValueType>& rhs) {
		if (vp != rhs.vp) {
			std::cerr << "ERROR : bool Iterator::operator<=(const Iterator<ValueType>& rhs) : "
				<< "vpと異なるVectorです" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return index <= rhs.index;
	}
	bool operator>=(const Iterator<ValueType>& rhs) {
		if (vp != rhs.vp) {
			std::cerr << "ERROR : bool Iterator::operator>=(const Iterator<ValueType>& rhs) : "
				<< "vpと異なるVectorです" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return index >= rhs.index;
	}

	Iterator<ValueType>& operator++() {
		if (!vp) {
			std::cerr << "ERROR : ValueType& Iterator::operator++() : "
				<< "vpが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		++index;
		return *this;
	}
	Iterator<ValueType> operator++(int) {
		if (!vp) {
			std::cerr << "ERROR : ValueType Iterator::operator++(int) : "
				<< "vpが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		Iterator copy(*this);	//	デフォルトのコピーコンストラクタ(浅いコピーでOK)
		++index;
		return copy;
	}
	Iterator<ValueType>& operator--() {
		if (!vp) {
			std::cerr << "ERROR : ValueType& Iterator::operator--() : "
				<< "vpが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		--index;
		return *this;
	}
	Iterator<ValueType> operator--(int) {
		if (!vp) {
			std::cerr << "ERROR : ValueType Iterator::operator--(int) : "
				<< "vpが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		Iterator<ValueType> copy(*this);	//	デフォルトのコピーコンストラクタ(浅いコピーでOK)
		--index;
		return copy;
	}

	Iterator<ValueType> operator+(int k) {
		if (!vp) {
			std::cerr << "ERROR : Iterator Iterator::operator+(int k) : "
				<< "vpが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		return Iterator<ValueType>(vp, index + k);
	}
	Iterator<ValueType> operator-(int k) {
		if (!vp) {
			std::cerr << "ERROR : Iterator Iterator::operator-(int k) : "
				<< "vpが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}

		return Iterator<ValueType>(vp, index - k);
	}
	int operator-(const Iterator<ValueType>& rhs) {
		if (!vp) {
			std::cerr << "ERROR : int Iterator::operator-(const Iterator& rhs) : "
				<< "vpが初期化されていません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		if (vp != rhs.vp) {
			std::cerr << "ERROR : int Iterator::operator-(const Iterator& rhs) : "
				<< "vpと異なるVectorです" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		return index - rhs.index;
	}

private:
	const Vector<ValueType>* vp;	//	iteratorによってvectorは操作されないことを保証する
	int index;

	//	Vectorクラスはこのコンストラクターにアクセスする必要があるが、
	//	クライアントが使用できるようにする必要はない
	Iterator(const Vector<ValueType>* vp, int index) {
		this->vp = vp;
		this->index = index;
	}
	friend class Vector<ValueType>;	//	この宣言によってVectorは上のprivateコンストラクタを呼べる
};

