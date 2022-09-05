
/*
* noskipwsマニピュレータの挙動を確認する
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "String.h"

int main()
{
	std::cout << "noskipws(空白を区別しない):" << std::endl << std::endl;
	char a, b, c;
	std::cin >> std::noskipws >> a >> b >> c;
	std::cout << a << b << c << std::endl;

	//	noskipwsマニピュレータを指定すると、例えば"1 2"と入力するとa = '1', b = ' ', c = '2'となる
}

