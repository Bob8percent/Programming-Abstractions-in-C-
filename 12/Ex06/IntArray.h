#pragma once
class IntArray
{
public:
	IntArray(int n);
	IntArray(const IntArray& src);
	~IntArray();

	int size() const;

	int get(int k) const;
	void put(int k, int value);

	int& operator[](int k);
	IntArray& operator=(const IntArray & src);

private:
	int n;
	int* elements;

	void deepCopy(const IntArray& src);

	//	引数なしは禁止
	IntArray() {}
};

