
/*
* ファイル名を分割する。
* 
* 例えば"File.txt"というファイルは"File"(getRoot), ".txt"(getExtension)となる
* ドットが存在しないときはgetRootはそのままファイル名を返し、getExtensionはから文字列を返す
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"

std::string getRoot(const std::string& filename);
std::string getExtension(const std::string& filename);
std::size_t lastDotPos(const std::string& filename);

int main()
{
	while (1)
	{
		std::string filename = "";
		std::getline(std::cin, filename);

		std::cout << "getRoot      : " << getRoot(filename) << std::endl;
		std::cout << "getExtension : " << getExtension(filename) << std::endl;
	}
}

std::string getRoot(const std::string& filename)
{
	std::size_t dotPos = lastDotPos(filename);
	return (dotPos == std::string::npos) ? filename : filename.substr(0, dotPos);
}

std::string getExtension(const std::string& filename)
{
	std::size_t dotPos = lastDotPos(filename);
	return (dotPos == std::string::npos) ? "" : filename.substr(dotPos);
}

std::size_t lastDotPos(const std::string& filename)
{
	std::size_t dotPos = std::string::npos;
	
	for (std::size_t i = 0; i < filename.length(); ++i)
	{
		std::size_t currentNum = filename.length() - 1 - i;
		if (filename.at(currentNum) == '.')
		{
			return currentNum;
		}
	}

	return dotPos;
}
