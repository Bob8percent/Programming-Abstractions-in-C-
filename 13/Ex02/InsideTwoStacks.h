#pragma once
#include <string>

enum STACK_TYPE {
	BEFORE,
	AFTER
};

//	内部実装のデータ構造は配列だが、2つのスタック機能を抽象化している。つまり、2つのスタックが一つの配列を共有している。
//	それぞれのスタックは中心(逆)方向に伸長する
class InsideTwoStacks
{
public:
	InsideTwoStacks();
	InsideTwoStacks(const InsideTwoStacks& src);
	~InsideTwoStacks();

	InsideTwoStacks& operator=(const InsideTwoStacks& src);

	std::size_t size(STACK_TYPE type) const;
	bool isEmpty(STACK_TYPE type) const;
	void clear(STACK_TYPE type);

	void push(char ch, STACK_TYPE type);
	char pop(STACK_TYPE type);
	char peek(STACK_TYPE type) const;

private:
	static const int INITIAL_CAPACITY = 10;
	char* elements;
	std::size_t beforeCount;
	std::size_t afterCount;
	std::size_t capacity;

	void expandCapcity();
	void deepCopy(const InsideTwoStacks& src);
};

