#include "StringMap.h"
#include <iostream>

StringMap::StringMap() {
	nBuckets = INITIAL_BUCKET_COUNT;
	buckets = new Cell * [nBuckets];
	for (int i = 0; i < nBuckets; ++i)buckets[i] = nullptr;
}

StringMap::~StringMap() {
	//	listがnBuckets個あるだけ
	for (int i = 0; i < nBuckets; ++i) {
		Cell* head = buckets[i];
		while (head) {
			Cell* cp = head;
			head = head->link;
			delete cp;
		}
	}
}

std::string StringMap::get(const std::string& key) const {
	int i = hashCode(key) % nBuckets;
	Cell* cp = findCell(i, key);
	if (cp)return cp->value;
	else return "";
}

void StringMap::put(const std::string& key, const std::string& value) {
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
			newCell->link = buckets[i]->link;
			buckets[i] = newCell;
		}
	}
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

StringMap::Cell* StringMap::findCell(int bucket, const std::string& key) const {
	if (!((0 <= bucket) && (bucket < nBuckets))) {
		std::cerr << "ERROR : Cell * StringMap::findCell(int bucket, const std::string & key) const : "
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

StringMap::iterator StringMap::begin(){
	for (int i = 0; i < nBuckets; ++i) {
		if (buckets[i])return StringMapIterator(this, buckets[i]);
	}
	return StringMapIterator(this, nullptr);
}

StringMap::iterator StringMap::end(){
	return StringMapIterator(this, nullptr);
}

StringMapIterator StringMapIterator::operator++(int) {
	if (!map) {
		std::cerr << "ERROR : StringMapIterator StringMapIterator::operator++(int) : "
			<< "mapが初期化されていません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	if (!cp) {
		std::cerr << "ERROR : StringMapIterator StringMapIterator::operator++(int) : "
			<< "cpがnullです" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	StringMapIterator copy(*this);
	if (cp->link) {
		cp = cp->link;
	}
	else {
		int bucketNum = map->hashCode(cp->key) % map->nBuckets;
		cp = nullptr;
		for (int i = bucketNum + 1; i < map->nBuckets; ++i) {
			if (map->buckets[i]) {
				cp = map->buckets[i];
				break;
			}
		}
	}
	return copy;

}
bool StringMapIterator::operator==(const StringMapIterator& rhs) {
	if (map != rhs.map) {
		std::cerr << "ERROR : bool StringMapIterator::operator==(const StringMapIterator& rhs) : "
			<< "mapとrhs.mapが異なります" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return cp == rhs.cp;
}

bool StringMapIterator::operator!=(const StringMapIterator& rhs) {
	if (map != rhs.map) {
		std::cerr << "ERROR : bool StringMapIterator::operator!=(const StringMapIterator& rhs) : "
			<< "mapとrhs.mapが異なります" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return !((*this) == rhs);
}

std::string& StringMapIterator::operator*() {
	if (!map) {
		std::cerr << "ERROR : StringMapIterator& StringMapIterator::operator*() : "
			<< "mapが初期化されていません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return cp->key;
}

std::string* StringMapIterator::operator->() {
	if (!map) {
		std::cerr << "ERROR : StringMapIterator* StringMapIterator::operator->() : "
			<< "mapが初期化されていません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	return &cp->key;
}
