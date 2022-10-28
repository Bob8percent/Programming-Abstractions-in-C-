#pragma once
#include <string>
#include "Library/vector.h"

class StringMap
{
public:
	StringMap();
	~StringMap();
	std::string get(const std::string& key) const;
	void put(const std::string& key, const std::string& value);

	void debug();	//	各バケットの個数を求めるデバッグ関数

private:
	//	データ構造：hashTable
	struct Cell {
		std::string key;
		std::string value;
		Cell* link;
	};
	static const int INITIAL_BUCKET_COUNT = 13;
	int nBuckets;
	Cell** buckets;
	int count;

	int hashCode(const std::string& key) const;
	Cell* findCell(int bucket, const std::string& key) const;

	void reHash();
};
