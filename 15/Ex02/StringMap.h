#pragma once
#include <string>

class StringMap
{
public:
	StringMap();
	StringMap(const StringMap& src);
	~StringMap();

	std::string get(const std::string& key) const;
	void put(const std::string& key, const std::string& value);

	StringMap& operator=(const StringMap& src);

private:
	//	データ構造：動的配列
	struct Pair {
		std::string key;
		std::string value;
	};
	static const int INTIAL_CAPACITY = 10;
	int capacity;
	int count;
	Pair* pairs;

	int findKey(const std::string& key) const;
	int findKey(const std::string& key, int start, int end) const;

	void expandCapacity();
	void deepCopy(const StringMap& src);
};
