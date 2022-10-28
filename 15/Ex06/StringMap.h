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

	//	------------コメントについて----------
	//	インターフェースに書くときはクライアントへ、実装部分に書くときは開発者へ向けたコメントを書くべき！
	//	----------------------------------
	// 
	// 
	//	add関数：
	//	key,valueを持つcellをバケットの先頭に追加する関数。
	//	これを使えば、keyを持つcellについて、valueに上書きできる。この実装には、findKeyが最初に見つけたkeyのcellを扱う仕組みであることを利用している
	//	呼び出した分だけ先頭にcellが増えていくことに注意。
	void add(const std::string& key, const std::string& value);	//	一時的に別のvalueを挿入

	//	remove関数：
	//	バケットの先頭にあり、keyをキーに持つcellを削除する関数。
	//	addで作成したcellを削除することを目的として作った。
	void remove(const std::string& key);	//	addしたcellを除去

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
