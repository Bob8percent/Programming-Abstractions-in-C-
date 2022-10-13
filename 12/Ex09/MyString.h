#pragma once
#include <string>

//結論：
//	固定長の文字列配列として扱うならば効率がいい。
//	でも、コピーや代入、+やsubstrといったものはコストがかかるので使用注意。

class MyString
{
public:
	MyString();
	MyString(const std::string& str);
	MyString(const MyString& src);
	~MyString();

	std::string toString() const;
	std::size_t length() const;
	MyString substr(std::size_t start, std::size_t n = 0);

	MyString operator+(const MyString& src) const;
	MyString& operator+=(const MyString& src);

	MyString& operator=(const MyString& src);

	char& operator[](std::size_t i) const;
	
	bool operator==(const MyString& src) const;
	bool operator!=(const MyString& src) const;
	bool operator>(const MyString& src) const;
	bool operator>=(const MyString& src) const;
	bool operator<(const MyString& src) const;
	bool operator<=(const MyString& src) const;

	friend std::ostream& operator<<(std::ostream& os, const MyString& src);

private:
	char* elements;

	static const std::size_t INITIAL_CAPACITY = 10;
	std::size_t capacity;
	std::size_t count;

	void deepCopy(const MyString& src);
};

std::ostream& operator<<(std::ostream& os, const MyString& src);
