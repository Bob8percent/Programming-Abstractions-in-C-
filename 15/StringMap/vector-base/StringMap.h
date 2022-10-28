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

private:
	struct Pair {
		std::string key;
		std::string value;
	};

	Vector<Pair> pairs;

	int findKey(const std::string& key) const;
};

