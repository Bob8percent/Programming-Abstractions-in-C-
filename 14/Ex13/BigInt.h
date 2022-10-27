#pragma once
#include <string>

//	今更気づいたし当然のことだけども、
//	以下の+演算子オーバーロード関数のようにコピーコンストラクタが呼ばれる場面があるときはコピーコンストラクタの作成をさぼれない。
//	privateに避難させたとしても、メソッドでコピーされるなら意味ない。このようなミスを以前の問題でも連発してる。
// 
//	非負の巨大な整数を扱えるクラス
class BigInt
{
public:
	BigInt();
	BigInt(const BigInt& src);
	BigInt(const std::string& digits);
	BigInt(int num);
	~BigInt();

	std::string toString() const;
	void clear();

	BigInt operator+ (const BigInt& src) const;	//	渡すときコピーコンストラクタが呼ばれることに注意
	BigInt operator* (const BigInt& src) const;	//	同上

	bool operator==(const BigInt& src) const;
	bool operator!=(const BigInt& src) const;

	BigInt& operator=(const BigInt& src);

private:
	struct Cell {
		char value;
		Cell* link;	//	次の位へのポインタ
	};
	Cell* head;	//	1の位へのポインタ
	int digit;

	void initialize();
	void deepCopy(const BigInt& src);
};

