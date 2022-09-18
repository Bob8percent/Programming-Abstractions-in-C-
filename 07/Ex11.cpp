#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

std::string integerToString(int num);

int main()
{
	std::cout << integerToString(1958) << std::endl;
}

std::string integerToString(int num)
{
	if (num < 10)return std::string(1, '0' + num);

	//	numが2桁以上の時
	//	numを1の位とそれ以外で分離する
	return integerToString(num / 10) + char('0' + num % 10);
}
