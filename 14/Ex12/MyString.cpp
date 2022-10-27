#include "MyString.h"
#include <iostream>

MyString::MyString() {
	head = nullptr;
	tail = nullptr;
	count = 0;
}

MyString::MyString(const std::string& str) {
	Cell* oldCell = nullptr;
	for (std::size_t i = 0; i < str.length(); ++i) {
		Cell* cell = new Cell;
		cell->ch = str.at(i);
		cell->link = nullptr;

		if (!oldCell)head = cell;
		else oldCell->link = cell;
		
		oldCell = cell;
		tail = cell;
	}
	count = str.length();
}

MyString::MyString(const MyString& src) {
	deepCopy(src);
}

MyString::~MyString() {
	clear();
}

std::string MyString::toString() const {
	if (count == 0)return "";

	std::string str;
	Cell* cp = head;
	while (cp) {
		str += cp->ch;
		cp = cp->link;
	}

	return str;
}

std::size_t MyString::length() const {
	return count;
}

//	+とsubstrに関して、
//	短い配列ほど効率がいいけど、どちらにせよMyStringを宣言時と戻り値で2回コピーするからコストは高そう
MyString MyString::substr(std::size_t start, std::size_t n/* = 0*/) const {
	if (!(0 <= start && start < count)) {
		std::cerr << "ERROR : MyString MyString::substr(std::size_t start, std::size_t n = std::string::npos) : "
			<< "startが範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	MyString str;
	Cell* cp = head;
	Cell* oldCell = nullptr;
	if (n == 0)n = count;
	while (start--)cp = cp->link;
	while (cp) {
		Cell* cell = new Cell;
		cell->ch = cp->ch;
		cell->link = nullptr;

		if (oldCell)oldCell->link = cell;
		else {
			str.head = cell;
			str.tail = cell;
		}

		++str.count;
		oldCell = cell;
		cp = cp->link;

		if (!(--n))break;
	}
	if(oldCell)str.tail = oldCell;
	return str;
}

MyString MyString::operator+(const MyString& src) const {
	MyString str = *this;
	Cell* cp = src.head;
	Cell* oldCell = nullptr;
	while (cp) {
		Cell* cell = new Cell;
		cell->ch = cp->ch;
		cell->link = nullptr;

		if (oldCell)oldCell->link = cell;
		else str.tail->link = cell;

		oldCell = cell;
		cp = cp->link;
	}
	str.count += src.count;
	if (oldCell)str.tail = oldCell;

	return str;
}

void MyString::clear() {
	while (head) {
		Cell* cp = head;
		head = head->link;
		delete cp;
	}
	head = nullptr;
	tail = nullptr;
	count = 0;
}

MyString& MyString::operator+=(const MyString& src) {
	Cell* cp = src.head;
	Cell* oldCell = nullptr;
	while (cp) {
		Cell* cell = new Cell;
		cell->ch = cp->ch;
		cell->link = nullptr;

		if (oldCell)oldCell->link = cell;
		else tail->link = cell;

		oldCell = cell;
		cp = cp->link;
	}
	count += src.count;
	if (oldCell)tail = oldCell;

	return *this;
}

MyString& MyString::operator=(const MyString& src) {
	if (this != &src) {
		clear();
		deepCopy(src);
	}

	return *this;
}

char& MyString::operator[](std::size_t i) const {
	if (!(0 <= i && i < count)) {
		std::cerr << "ERROR : char& MyString::operator[](std::size_t i) const : "
			<< "iが範囲外です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	Cell* cp = head;
	while (i--) cp = cp->link;
	return cp->ch;
}

bool MyString::operator==(const MyString& src) const {
	if (count != src.count)return false;

	Cell* cp = head;
	Cell* scp = src.head;
	while (cp && scp) {
		if (cp->ch != scp->ch)return false;
		cp = cp->link;
		scp = scp->link;
	}

	return true;
}

bool MyString::operator!=(const MyString& src) const {
	return !((*this) == src);
}

bool MyString::operator>(const MyString& src) const {
	std::size_t minLen = (count < src.count) ? count : src.count;

	Cell* cp = head;
	Cell* scp = src.head;
	//	各文字のASCIIコードの大小を比較する
	for (std::size_t i = 0; i < minLen; ++i) {
		if (cp->ch > scp->ch)return true;
		if (cp->ch < scp->ch)return false;

		cp = cp->link;
		scp = scp->link;
	}

	//	minLenまで同じ文字のときは文字列が長い方が大きい
	return count > src.count;
}

bool MyString::operator>=(const MyString& src) const {
	return !(src > (*this));
}

bool MyString::operator<(const MyString& src) const {
	return src > (*this);
}

bool MyString::operator<=(const MyString& src) const {
	return !((*this) > src);
}

void MyString::deepCopy(const MyString& src){
	Cell* cp = src.head;
	Cell* oldCell = nullptr;
	head = nullptr;
	while (cp) {
		Cell* cell = new Cell;
		cell->ch = cp->ch;
		cell->link = nullptr;
		if (oldCell) oldCell->link = cell;
		else {
			head = cell;
			tail = cell;
		}
		oldCell = cell;
		cp = cp->link;
	}
	count = src.count;
	if(oldCell) tail = oldCell;
}

std::ostream& operator<<(std::ostream& os, const MyString& src) {
	return os << src.toString();
}
