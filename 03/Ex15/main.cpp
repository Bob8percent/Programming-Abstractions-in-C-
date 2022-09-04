
/*
* PigLatinへ翻訳するプログラム
*/

#include <iostream>
#include <iomanip>
#include <string>
#include "PigLatin.h"

int main()
{
	while (1)
	{
		std::cout << "入力：";
		std::string str = "";
		std::getline(std::cin, str);

		if (str == "END")
		{
			break;
		}

		std::cout << "PigLatinへの翻訳結果：" << lineToPigLatin(str) << "\n";
	}
}

