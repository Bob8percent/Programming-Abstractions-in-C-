#define _USE_MATH_DEFINES

#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/random.h"
#include "Library/map.h"
#include "Library/set.h"
#include <ctime>

std::string _integerToString(int num, int base);
int _stringToInteger(const std::string& num, int base);

int main() {
	std::cout << _stringToInteger("111", 16) << std::endl;
}

std::string _integerToString(int num, int base) {
	if (!(2 <= base && base <= 36))std::exit(EXIT_FAILURE);

	std::string str;

	//	numが負の数の場合、baseの補数表現にした時の数を非負表現の数に変換する
	//	例：-1は2の補数表現では1111 1111だが、これは非負表現では255となる
	unsigned int val = (num < 0) ? (UINT_MAX + num + 1) : num;

	int nBits = 0;
	for (int i = base; i >= 2; i /= 2, ++nBits);
	int digit = 32 / nBits;	//	32ビット表現にする

	do {
		char ch;
		int remainder = val % base;
		if (remainder < 10) ch = remainder + '0';
		else ch = (remainder - 10) + 'A';
		str = ch + str;
		val /= base;

	} while (--digit > 0);

	return str;
}

int _stringToInteger(const std::string& str, int base) {
	if (!(2 <= base && base <= 36))std::exit(EXIT_FAILURE);

	int val = 0;
	int digit = 1;
	for (std::size_t i = str.length() - 1; i >= 0; --i) {
		char ch = str.at(i);
		if (isdigit(ch)) {
			val += digit * (ch - '0');
		}
		else if (isupper(ch)) {
			val += digit * (ch - 'A');
		}
		else {
			std::exit(EXIT_FAILURE);
		}
		digit *= base;
	}

	return val;
}


