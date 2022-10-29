#include "StringMap.h"

StringMap::StringMap() {
	capacity = INITIAL_CAPACITY;
	elements = new Cell[capacity];
	count = 0;
}

StringMap::StringMap(const StringMap& src) {
	deepCopy(src);
}

StringMap::~StringMap() {
	delete[] elements;
}

std::string StringMap::get(const std::string& key) const {
	int i = hashCode(key) % capacity;
	int cp = findCell(i, key);
	if (cp != -1)return elements[i].value;
	else return "";
}

const double REHASH_THRESHOLD = 0.7;	//	TODO : static const doubleだとインターフェイス内で初期化できなかった
void StringMap::put(const std::string& key, const std::string& value) {
	double lambda = count / (1.0 * capacity);
	if (lambda > REHASH_THRESHOLD)reHash();

	int i = hashCode(key) % capacity;
	int cp = findCell(i, key);
	if (cp != -1) elements[cp].value = value;
	else {
		//	空のインデックスにセルを作成
		for (int k = 0; k < capacity; ++k) {
			int index = (i + k) % capacity;
			if (elements[index].key == "") {
				elements[index].key = key;
				elements[index].value = value;
				break;
			}
		}

		++count;
	}
}

int StringMap::size() const {
	return count;
}

bool StringMap::isEmpty() const {
	return count == 0;
}

const int HASH_SEED = 5381;
const int HASH_MULTIPLIER = 33;
const int HASH_MASK = unsigned(-1) >> 1;
int StringMap::hashCode(const std::string& key) const {
	unsigned hash = HASH_SEED;
	for (int i = 0; i < key.length(); ++i) {
		hash = HASH_MULTIPLIER * hash + key[i];
	}
	return int(hash & HASH_MASK);
}

int StringMap::findCell(int bucket, const std::string& key) const {
	if (!((0 <= bucket) && (bucket < capacity))) {
		std::cerr << "ERROR : int StringMap::findCell(int bucket, const std::string & key) const : "
			<< "indexが範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	for (int i = 0; i < capacity; ++i) {
		int index = (bucket + i) % capacity;
		if (elements[index].key == key)return index;
	}

	return -1;
}

bool StringMap::containsKey(const std::string& key) const {
	int i = hashCode(key);
	return findCell(i, key) != -1;
}

void StringMap::clear() {
	count = 0;
}

void StringMap::reHash() {
	Cell* oldElements = elements;
	int oldCapacity = capacity;

	while ((count / (1.0 * capacity)) > REHASH_THRESHOLD) {
		capacity *= 2;	//	O(1)にするため。細かい数学は償却分析をしよう。
	}
	
	//	新しくハッシュマップを作成
	elements = new Cell[capacity];
	count = 0;
	for (int i = 0; i < oldCapacity; ++i) {
		if (oldElements[i].key != "") {
			put(oldElements[i].key, oldElements[i].value);
		}
	}

	//	oldElementsを解放
	delete[] oldElements;
}

void StringMap::remove(const std::string& key) {
	int i = hashCode(key) % capacity;
	int cp = findCell(i, key);

	if (cp != -1) {
		elements[cp].key = "";	//	valueは変更する必要ない
		--count;
	}
}

StringMap& StringMap::operator=(const StringMap& src) {
	if (this != &src) {
		delete[] elements;
		deepCopy(src);
	}
	return *this;
}

void StringMap::deepCopy(const StringMap& src) {
	capacity = src.capacity;
	elements = new Cell[capacity];
	count = src.count;
	for (int i = 0; i < capacity; ++i) {
		elements[i] = src.elements[i];
	}
}

void StringMap::debug() {
	double lambda = count / (1.0 * capacity);
	std::cout << lambda << std::endl;
}
