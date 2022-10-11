#pragma once
class IntArray
{
public:
	IntArray(int n);
	~IntArray();

	int size() const;

	int get(int k) const;
	void put(int k, int value);

private:
	int n;
	int* elements;

	//	コピー、代入を禁止
	IntArray(const IntArray& src) {}
	void operator=(const IntArray& src) {}
};

