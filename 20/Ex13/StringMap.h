#pragma once
#include <string>

class StringMapIterator;

class StringMap
{
public:
	StringMap();
	~StringMap();
	std::string get(const std::string& key) const;
	void put(const std::string& key, const std::string& value);

	//	イテレーター
	typedef class StringMapIterator iterator;
	iterator begin();
	iterator end();

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

	int hashCode(const std::string& key) const;
	Cell* findCell(int bucket, const std::string& key) const;

	friend class StringMapIterator;
};

//	イテレーター
class StringMapIterator {
public:
	StringMapIterator() { map = nullptr; cp = nullptr; }
	StringMapIterator operator++(int);
	bool operator==(const StringMapIterator& rhs);
	bool operator!=(const StringMapIterator& rhs);
	std::string& operator*();
	std::string* operator->();

private:
	StringMapIterator(StringMap* map, StringMap::Cell* cell) { 
		this->map = map;
		cp = cell;
	}

	StringMap* map;
	StringMap::Cell* cp;
	friend class StringMap;
};
