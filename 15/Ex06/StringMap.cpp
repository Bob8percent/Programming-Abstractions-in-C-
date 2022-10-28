#include "StringMap.h"

StringMap::StringMap() {
	nBuckets = INITIAL_BUCKET_COUNT;
	buckets = new Cell * [nBuckets];
	for (int i = 0; i < nBuckets; ++i)buckets[i] = nullptr;

	count = 0;
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

const double REHASH_THRESHOLD = 0.7;	//	TODO : static const doubleだとインターフェイス内で初期化できなかった
void StringMap::put(const std::string& key, const std::string& value) {
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

void StringMap::reHash() {
	Cell** oldBuckets = buckets;
	int oldNum = nBuckets;

	while ((count / (1.0 * nBuckets)) > REHASH_THRESHOLD) {
		++nBuckets;
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

void StringMap::add(const std::string& key, const std::string& value) {
	int i = hashCode(key) % nBuckets;

	Cell* newCell = new Cell;
	newCell->key = key;
	newCell->value = value;

	newCell->link = buckets[i];
	buckets[i] = newCell;
}

void StringMap::remove(const std::string& key) {
	int i = hashCode(key) % nBuckets;
	if (!buckets[i] || buckets[i]->key != key) {
		std::cerr << "ERROR : void StringMap::restore(const std::string& key) : "
			<< "keyをキーに持つセルは、バケットの先頭に存在しません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	else {
		Cell* hideCell = buckets[i]->link;
		buckets[i]->value = hideCell->value;
		buckets[i]->link = hideCell->link;
		delete hideCell;
	}
}

void StringMap::debug() {
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
