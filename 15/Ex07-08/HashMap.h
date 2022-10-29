#pragma once
#include <iostream>
#include "_HashCode.h"

template <typename KeyType, typename ValueType>
class HashMap
{
public:
	HashMap();
	HashMap(const HashMap<KeyType, ValueType>& src);
	~HashMap();

	int size() const;
	bool isEmpty() const;
	void put(const KeyType& key, const ValueType& value);
	ValueType get(const KeyType& key) const;
	
	void remove(const KeyType& key);
	bool containsKey(const KeyType& key) const;
	void clear();

	ValueType& operator[](const KeyType& key) const;
	HashMap<KeyType, ValueType>& operator=(const HashMap<KeyType, ValueType>& src);
	bool operator==(const HashMap<KeyType, ValueType>& src) const;

	void debug();

private:
	//	データ構造：hashTable
	struct Cell {
		KeyType key;
		ValueType value;
		Cell* link;
	};
	static const int INITIAL_BUCKET_COUNT = 13;
	int nBuckets;
	Cell** buckets;
	int count;
	const double REHASH_THRESHOLD = 0.7;	//	TODO : static const doubleだとインターフェイス内で初期化できなかった

	int hashCode(const KeyType& key) const;	//	keyがプリミティブ型のときはHashCode.hの関数を、ユーザー定義型のときはクライアントが作成したnewHashCode()を呼び出す
	Cell* findCell(int bucket, const KeyType& key) const;
	void deepCopy(const HashMap<KeyType, ValueType>& src);
	void reHash();
};

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::HashMap() {
	nBuckets = INITIAL_BUCKET_COUNT;
	buckets = new Cell * [nBuckets];
	for (int i = 0; i < nBuckets; ++i)buckets[i] = nullptr;
	count = 0;	
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::HashMap(const HashMap<KeyType, ValueType>& src) {
	deepCopy(src);
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>::~HashMap() {
	clear();
}

template <typename KeyType, typename ValueType>
int HashMap<KeyType, ValueType>::size() const {
	return count;
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::isEmpty() const {
	return count == 0;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::put(const KeyType& key, const ValueType& value) {
	double lambda = count / (1.0 * nBuckets);
	if (lambda > REHASH_THRESHOLD)reHash();

	int i = hashCode(key) % nBuckets;
	Cell* cp = findCell(i, key);
	if (cp) cp->value = value;
	else {
		Cell* newCell = new Cell;
		newCell->key = key;
		newCell->value = value;
		newCell->link = nullptr;
		if (!buckets[i])buckets[i] = newCell;
		else {
			newCell->link = buckets[i];
			buckets[i] = newCell;
		}

		++count;
	}
}

template <typename KeyType, typename ValueType>
ValueType HashMap<KeyType, ValueType>::get(const KeyType& key) const {
	int i = hashCode(key) % nBuckets;
	Cell* cp = findCell(i, key);
	if (cp)return cp->value;
	else return "";
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::remove(const KeyType& key) {
	int i = hashCode(key) % nBuckets;
	Cell* cp = findCell(i, key);
	if(cp) {
		Cell* cell = buckets[i];
		Cell* oldCell = nullptr;
		while (cell) {
			if (cell == cp) break;
			oldCell = cell;
			cell = cell->link;
		}

		if (!oldCell) buckets[i] = cp->link;
		else oldCell->link = cp->link;
		delete cp;
	}
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::containsKey(const KeyType& key) const {
	int i = hashCode(key) % nBuckets;
	return findCell(i, key) != nullptr;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::clear() {
	for (int i = 0; i < nBuckets; ++i) {
		Cell* cp = buckets[i];
		while (cp) {
			Cell* dCell = cp;
			cp = cp->link;
			delete dCell;
		}
	}
	nBuckets = INITIAL_BUCKET_COUNT;
	count = 0;
}

template <typename KeyType, typename ValueType>
ValueType& HashMap<KeyType, ValueType>::operator[](const KeyType& key) const {
	int i = hashCode(key) % nBuckets;
	Cell* cp = findCell(i, key);
	if (cp) return cp->value;
	else {
		//	セルが見つからないときは新しく作る
		Cell* newCell = new Cell;
		newCell->key = key;
		newCell->value = ValueType();
		newCell->link = nullptr;
		if (!buckets[i])buckets[i] = newCell;
		else {
			newCell->link = buckets[i];
			buckets[i] = newCell;
		}
		++count;
		return newCell->value;
	}
}

template <typename KeyType, typename ValueType>
HashMap<KeyType, ValueType>& HashMap<KeyType, ValueType>::operator=(const HashMap<KeyType, ValueType>& src) {
	if (this != &src) {
		clear();
		deepCopy(src);
	}
	return *this;
}

template <typename KeyType, typename ValueType>
bool HashMap<KeyType, ValueType>::operator==(const HashMap<KeyType, ValueType>& src) const {
	if (src.size() != size())return false;

	for (int i = 0; i < src.nBuckets; ++i) {
		Cell* cp = src.buckets[i];
		while (cp) {
			if (get(cp->key) != src.get(cp->key))return false;
			cp = cp->link;
		}
	}

	return true;
}

template <typename KeyType, typename ValueType>
int HashMap<KeyType, ValueType>::hashCode(const KeyType& key) const {
	if (isPrimitive(key)) {
		//	HashCode.hのHashCode()を呼び出す
		return ::hashCode(key);
	}
	//else if (typeid(Func) == typeid(int)){
	//	std::cerr << "ERROR : int HashMap<KeyType, ValueType>::hashCode(const KeyType & key) : "
	//		<< "KeyTypeを扱うHashCode関数がサポートされていなません";
	//	std::exit(EXIT_FAILURE);
	//}
	else {
		//	TODO : HashCode.hではサポートされていない型を扱うので、クライアントが作成したHashCodeを使いたい
		return 0;
	}
}

template <typename KeyType, typename ValueType>
typename HashMap<KeyType, ValueType>::Cell*
HashMap<KeyType, ValueType>::findCell(int bucket, const KeyType& key) const {
	if (!((0 <= bucket) && (bucket < nBuckets))) {
		std::cerr << "ERROR : Cell * HashMap::findCell(int bucket, const KeyType& key) const : "
			<< "bucketが範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Cell* cp = buckets[bucket];
	while (cp) {
		if (cp->key == key)return cp;
		cp = cp->link;
	}

	return nullptr;
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::deepCopy(const HashMap<KeyType, ValueType>& src) {
	nBuckets = src.nBuckets;
	count = src.count;
	buckets = new Cell * [nBuckets];
	for (int i = 0; i < nBuckets; ++i) {
		Cell* cp = src.buckets[i];
		Cell* oldCell = nullptr;
		while (cp) {
			Cell* newCell = new Cell;
			newCell->key = cp->key;
			newCell->value = cp->value;
			newCell->link = nullptr;
			if (oldCell)oldCell->link = newCell;
			else buckets[i] = newCell;

			oldCell = newCell;
			cp = cp->link;
		}
	}
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::reHash() {
	Cell** oldBuckets = buckets;
	int oldNum = nBuckets;

	while ((count / (1.0 * nBuckets)) > REHASH_THRESHOLD) {
		nBuckets *= 2;	//	O(1)にするため。細かい数学は償却分析をしよう。
	}

	//	新しくハッシュマップを作成
	buckets = new Cell * [nBuckets];
	for (int i = 0; i < nBuckets; ++i)buckets[i] = nullptr;
	count = 0;
	for (int i = 0; i < oldNum; ++i) {
		Cell* cp = oldBuckets[i];
		while (cp) {
			put(cp->key, cp->value);
			cp = cp->link;
		}
	}

	//	oldBucketsを解放
	for (int i = 0; i < oldNum; ++i) {
		Cell* head = oldBuckets[i];
		while (head) {
			Cell* cp = head;
			head = head->link;
			delete cp;
		}
	}
}

template <typename KeyType, typename ValueType>
void HashMap<KeyType, ValueType>::debug() {
	for (int i = 0; i < nBuckets; ++i) {
		Cell* cp = buckets[i];
		int n = 0;
		while (cp) {
			++n;
			cp = cp->link;
		}
		std::cout << n << " ";
	}

	double lambda = count / (1.0 * nBuckets);
	std::cout << lambda << std::endl;
}
