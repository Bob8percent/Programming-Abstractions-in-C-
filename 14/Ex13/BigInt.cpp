#include "BigInt.h"
#include <iostream>

BigInt::BigInt() {
	initialize();
}

BigInt::BigInt(const BigInt& src) {
	deepCopy(src);
}

BigInt::BigInt(const std::string& digits) {
	if (digits.length() == 0) {
		initialize();
		return;
	}

	Cell* oldCell = nullptr;
	for (std::size_t i = 0; i < digits.length(); ++i) {
		if (!('0' <= digits.at(i) && digits.at(i) <= '9')) {
			std::cerr << "ERROR : BigInt::BigInt(const std::string & digits) : "
				<< "digits[" << i << "]が数値じゃありません" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		std::size_t index = digits.length() - i - 1;
		Cell* cell = new Cell;
		cell->value = (digits.at(index) - '0');
		cell->link = nullptr;
		if (oldCell)oldCell->link = cell;
		else head = cell;

		oldCell = cell;
	}
}

BigInt::BigInt(int num) {
	if (num < 0) {
		std::cerr << "ERROR : BigInt::BigInt(int num) : numが負です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	if (num == 0) {
		initialize();
		return;
	}

	digit = 0;
	Cell* oldCell = nullptr;
	while (num > 0) {
		Cell* cell = new Cell;
		cell->value = (num % 10);
		cell->link = nullptr;
		if (oldCell)oldCell->link = cell;
		else head = cell;

		oldCell = cell;
		num /= 10;
		++digit;
	}
}

BigInt::~BigInt() {
	clear();
}

void BigInt::initialize() {
	digit = 1;
	Cell* cell = new Cell;
	cell->value = 0;
	cell->link = nullptr;
	head = cell;
}

std::string BigInt::toString() const {
	std::string num;
	Cell* cp = head;
	while (cp) {
		std::string ch(1, cp->value + '0');
		num = ch + num;
		cp = cp->link;
	}
	return num;
}

void BigInt::clear() {
	while (head) {
		Cell* cp = head;
		head = head->link;
		delete cp;
	}
	head = nullptr;
	digit = 0;
}

BigInt BigInt::operator+ (const BigInt& src) const{
	BigInt num;
	Cell* oldCell = nullptr;
	bool isBigger = (digit > src.digit);
	Cell* cp = isBigger ? head : src.head;
	Cell* scp = isBigger ? src.head : head;
	num.digit = isBigger ? digit : src.digit;
	int carry = 0;	//	桁上がり
	while (cp) {
		char result = cp->value + (scp ? scp->value : 0) + carry;

		Cell* cell = new Cell;
		cell->value = result % 10;
		cell->link = nullptr;

		carry = result / 10;
		if (oldCell)oldCell->link = cell;
		else num.head = cell;

		oldCell = cell;
		cp = cp->link;
		if (scp)scp = scp->link;
	}

	if (carry) {
		Cell* cell = new Cell;
		cell->value = 1;
		cell->link = nullptr;
		if (oldCell)oldCell->link = cell;
		else num.head = cell;
		++num.digit;
	}

	return num;
}

BigInt BigInt::operator* (const BigInt& src) const{
	//	TODO : srcを素因数分解してから計算すれば計算量減らせそう
	BigInt num;
	BigInt one(1);
	for (BigInt count; count != src; count = count + one) {
		num = num + (*this);
	}

	return num;
}

bool BigInt::operator==(const BigInt& src) const {
	if (digit != src.digit)return false;

	Cell* cp = head;
	Cell* scp = src.head;
	while (cp && scp) {
		if (cp->value != scp->value)return false;

		cp = cp->link;
		scp = scp->link;
	}

	return true;
}

bool BigInt::operator!=(const BigInt& src) const {
	return !(*this == src);
}

BigInt& BigInt::operator=(const BigInt& src) {
	if (this != &src) {
		clear();
		deepCopy(src);
	}

	return *this;
}

void BigInt::deepCopy(const BigInt& src) {
	Cell* cp = src.head;
	Cell* oldCell = nullptr;
	while (cp) {
		Cell* cell = new Cell;
		cell->value = cp->value;
		cell->link = nullptr;
		if (oldCell)oldCell->link = cell;
		else head = cell;
		
		oldCell = cell;
		cp = cp->link;
	}

	digit = src.digit;
}
