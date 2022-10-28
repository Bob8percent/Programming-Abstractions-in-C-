#include "StringMap.h"

StringMap::StringMap() {
	capacity = INTIAL_CAPACITY;
	pairs = new Pair[capacity];
	count = 0;
}

StringMap::StringMap(const StringMap& src) {
	deepCopy(src);
}

StringMap::~StringMap() {
	delete[] pairs;
}

std::string StringMap::get(const std::string& key) const {
	int i = findKey(key);
	if (i != -1)return pairs[i].value;
	else return "";
}

//	O(N)
void StringMap::put(const std::string& key, const std::string& value) {
	if (count >= capacity)expandCapacity();

	Pair newPair;
	newPair.key = key;
	newPair.value = value;

	for (int i = 0; i < count; ++i) {
		if (key < pairs[i].key) {
			//	iにinsert
			for (int k = count; k > i; --k) {
				pairs[k] = pairs[k - 1];
			}
			pairs[i] = newPair;
			++count;
			return;
		}

		if (key == pairs[i].key) {
			pairs[i].value = value;
			++count;
			return;
		}
	}

	pairs[count++] = newPair;
}

int StringMap::size() const {
	return count;
}

bool StringMap::isEmpty() const {
	return count == 0;
}

bool StringMap::containsKey(const std::string& key) const {
	return findKey(key) != -1;
}

void StringMap::clear() {
	count = 0;
}

StringMap& StringMap::operator=(const StringMap& src) {
	if (this != &src) {
		delete[] pairs;
		deepCopy(src);
	}
	return *this;
}

//	O(logN)
int StringMap::findKey(const std::string& key) const {
	return findKey(key, 0, count - 1);
}
int StringMap::findKey(const std::string& key, int start, int end) const {
	if (start > end) {
		return -1;
	}

	int mid = (start + end) / 2;
	if (pairs[mid].key == key)return mid;
	else if (pairs[mid].key < key)return findKey(key, mid + 1, end);
	else return findKey(key, start, mid - 1);
}

void StringMap::expandCapacity() {
	Pair* newElements = new Pair[capacity * 2];
	for (int i = 0; i < capacity; ++i) {
		newElements[i] = pairs[i];
	}
	
	delete[] pairs;
	pairs = newElements;
	capacity *= 2;
}

void StringMap::deepCopy(const StringMap& src) {
	pairs = new Pair[src.capacity];
	for (int i = 0; i < src.count; ++i) {
		pairs[i] = src.pairs[i];
	}
	
	capacity = src.capacity;
	count = src.count;
}

