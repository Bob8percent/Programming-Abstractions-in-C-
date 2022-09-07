
/*
* 文字列から整数/実数への変換
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"

int stringToInteger(const std::string& str);
std::string integerToString(int n);
double stringToReal(const std::string& str);
std::string realToString(double d);

int main()
{
	//std::cout << "stringToIntegerの入力：";
	//std::string str = "";
	//std::getline(std::cin, str);
	//std::cout << stringToInteger(str) << std::endl;


	//std::cout << "intgerToStringの入力：";
	//int n;
	//std::cin >> n;
	//std::cout << integerToString(n) << std::endl;


	//std::cout << "stringToRealの入力：";
	//std::string str = "";
	//std::getline(std::cin, str);
	//std::cout << stringToReal(str) << std::endl;


	//std::cout << "realToStringの入力：";
	//double d;
	//std::cin >> d;
	//std::cout << realToString(d) << std::endl;

}

int stringToInteger(const std::string& str)
{
	std::istringstream iss(str);
	int value;
	iss >> value >> std::skipws;

	if (!iss.fail() && iss.eof())
	{
		return value;
	}

	std::cout << "ERROR : int stringToInteger(const std::string& str) : "
		<< "文字列を整数に変換できません" << std::endl;
}

std::string integerToString(int n)
{
	std::ostringstream oss;
	oss << n;

	//	文字列に変換できない場合が考えられない
	return oss.str();
}

double stringToReal(const std::string& str)
{
	std::istringstream iss(str);
	double value;
	iss >> value >> std::skipws;

	std::cout << value << std::endl;
	std::cout << std::boolalpha << !iss.fail() << std::endl;
	std::cout << std::boolalpha << iss.eof() << std::endl;
	if (!iss.fail() && iss.eof())
	{
		return value;
	}

	std::cout << "ERROR : double stringToReal(const std::string& str) : "
		<< "文字列を実数に変換できません" << std::endl;
}

std::string realToString(double d)
{
	std::ostringstream oss;
	oss << d;

	return oss.str();
}
