#include "StringMap.h"

StringMap::StringMap() {

}

StringMap::~StringMap() {

}

std::string StringMap::get(const std::string& key) const {
	int i = findKey(key);
	if (i != -1)return pairs[i].value;
	else return "";
}

//	O(N)
void StringMap::put(const std::string& key, const std::string& value) {
	Pair newPair;
	newPair.key = key;
	newPair.value = value;

	for (int i = 0; i < pairs.size(); ++i) {
		if (key < pairs[i].key) {
			pairs.insert(i, newPair);
			return;
		}

		if (key == pairs[i].key) {
			pairs[i].value = value;
			return;
		}
	}

	pairs.add(newPair);
}

//	O(logN)
int StringMap::findKey(const std::string& key) const {
	return findKey(key, 0, pairs.size() - 1);
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


