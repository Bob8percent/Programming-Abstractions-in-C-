#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "_Set.h"

int main() {
	const int CHAR_NUM = 16;
	while (1) {
		std::string x;
		std::string y;
		std::cout << "Enter x: ";
		std::getline(std::cin, x);
		if (x.length() != CHAR_NUM) {
			std::cerr << "ERROR : xは" << CHAR_NUM << "文字だけ入力してください" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		for (int i = 0; i < x.length(); ++i) {
			if (!(x.at(i) == '0' || x.at(i) == '1')) {
				std::cerr << "ERROR : xは0、1以外の入力はしないでください" << std::endl;
				std::exit(EXIT_FAILURE);
			}
		}
		std::cout << "Enter y: ";
		std::getline(std::cin, y);
		if (y.length() != CHAR_NUM) {
			std::cerr << "ERROR : yは" << CHAR_NUM << "文字だけ入力してください" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		for (int i = 0; i < y.length(); ++i) {
			if (!(y.at(i) == '0' || y.at(i) == '1')) {
				std::cerr << "ERROR : yは0、1以外の入力はしないでください" << std::endl;
				std::exit(EXIT_FAILURE);
			}
		}

		std::cout << "x & y = ";
		for (int i = 0; i < CHAR_NUM; ++i) {
			int x_bit = x.at(i) - '0';
			int y_bit = y.at(i) - '0';
			std::cout << (x_bit & y_bit);
		}
		std::cout << std::endl;

		std::cout << "x | y = ";
		for (int i = 0; i < CHAR_NUM; ++i) {
			bool x_bit = x.at(i) - '0';
			bool y_bit = y.at(i) - '0';
			std::cout << (x_bit | y_bit);
		}
		std::cout << std::endl;

		std::cout << "x ^ y = ";
		for (int i = 0; i < CHAR_NUM; ++i) {
			bool x_bit = x.at(i) - '0';
			bool y_bit = y.at(i) - '0';
			std::cout << (x_bit ^ y_bit);
		}
		std::cout << std::endl;

		std::cout << "~y = ";
		for (int i = 0; i < CHAR_NUM; ++i) {
			bool y_bit = y.at(i) - '0';
			std::cout << !y_bit;
		}
		std::cout << std::endl;

		std::cout << "x & ~y = ";
		for (int i = 0; i < CHAR_NUM; ++i) {
			bool x_bit = x.at(i) - '0';
			bool y_bit = y.at(i) - '0';
			std::cout << (x_bit & ~y_bit);
		}
		std::cout << std::endl;
	}
}
