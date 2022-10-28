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
	//	データ構造：vector
	//	pairsをソートした状態で保ち、findKey()で2分探索法を用いればO(logN)に短縮できるが、
	//	putを実行するたびにシフトが必要なのでO(N)になってしまう。
	struct Pair {
		std::string key;
		std::string value;
	};

	Vector<Pair> pairs;

	int findKey(const std::string& key) const;
};

