
/*
* getReal()の実装
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"

double getReal(std::istream& is);

int main()
{
	std::cout << getReal(std::cin) << std::endl;
}

double getReal(std::istream& is)
{
	while (1)
	{
		std::string str = "";
		std::getline(is, str);

		std::istringstream iss(str);
		double value;
		iss >> value >> std::skipws;

		if (!iss.fail() && iss.eof())
		{
			return value;
		}

		iss.clear();
		std::cout << "ERROR : double getReal(std::istream& is) : "
			<< "文字列から実数を取得できません" << std::endl;
	}
}
