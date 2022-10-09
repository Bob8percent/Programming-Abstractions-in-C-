#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/stack.h"

//	TokenScannerクラスはChapter6のEx11のものを使用した
void runCalculator();
std::string _integerToString(int num, int base);
int _stringToInteger(const std::string& num, int base);

int main()
{
	runCalculator();
}

//	演算子に優先順位のない電卓
void runCalculator()
{
	const int base = 16;
	while (1)
	{
		std::string line;
		std::getline(std::cin, line);

		TokenScanner scanner(line);
		scanner.ignoreWhiteSpace();
		Stack<int> operands;
		char currentOperator;
		while (scanner.hasMoreTokens())
		{
			std::string token = scanner.nextToken();
			char ch = token.at(0);
			if (isdigit(ch) || isupper(ch))
			{
				operands.push(_stringToInteger(token, base));
			}
			else
			{
				switch (ch)
				{
				case '+':
				case '-':
				case '*':
				case '/':
					currentOperator = ch;
					break;
				default:
					std::cerr << "ERROR : void runCalculator() : "
						<< "不適な文字が入力されています" << std::endl;
					std::exit(EXIT_FAILURE);
					break;
				}
			}

			//	計算
			if (operands.size() == 2)
			{
				double rhs = operands.pop();
				double lhs = operands.pop();
				double result;
				switch (currentOperator)
				{
				case '+':
					result = lhs + rhs;
					break;
				case '-':
					result = lhs - rhs;
					break;
				case '*':
					result = lhs * rhs;
					break;
				case '/':
					result = lhs / rhs;
					break;
				default:
					break;
				}
				operands.push(result);
			}
		}

		//	計算結果出力
		std::cout << "> " << _integerToString(operands.pop(), base) << std::endl;
	}
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
	for (std::size_t i = 0; i < str.length(); ++i) {
		char ch = str.at(str.length() - i - 1);
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
