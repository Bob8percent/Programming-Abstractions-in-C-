#pragma once
#include <string>
#include "Library/vector.h"

class StringMap
{
public:
	StringMap();
	StringMap(const StringMap& src);
	~StringMap();
	std::string get(const std::string& key) const;
	void put(const std::string& key, const std::string& value);

	int size() const;
	bool isEmpty() const;

	void remove(const std::string& key);
	bool containsKey(const std::string& key) const;
	void clear();

	StringMap& operator=(const StringMap& src);

	void debug();	//	各バケットの個数を求めるデバッグ関数

private:
	//	データ構造：hashTable(線形プローブ)
	//	線形プローブ：hashCodeはindexの開始点に過ぎない。空のインデックスが現れるまで探索してputする戦略。
	//	今までのバケットチェーンアプローチと違ってバケットごとに完全に分割するわけではなく、
	//	hashCodeの近くにcellを置くという戦略。これに加えて負荷係数を考慮してrehashすることでO(1)を実現させる
	struct Cell {
		std::string key;
		std::string value;
	};
	static const int INITIAL_CAPACITY = 13;
	int capacity;
	int count;	
	Cell* elements;	//	ring buffer

	int hashCode(const std::string& key) const;
	int findCell(int bucket, const std::string& key) const;

	void reHash();
	void deepCopy(const StringMap& src);
};	
