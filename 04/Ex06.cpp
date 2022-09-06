
/*
* ファイル名について、拡張子がない場合それを追加し、*印がついている場合は拡張子は入れ替える
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"

std::string defaultExtension(const std::string& filename, const std::string& ext);
std::string getRoot(const std::string& filename);
std::string getExtension(const std::string& filename);
std::size_t lastDotPos(const std::string& filename);

int main()
{
	while (1)
	{
		std::cout << "ファイル名：";
		std::string filename = "";
		std::getline(std::cin, filename);

		std::cout << "追加する拡張子：";
		std::string ext = "";
		std::getline(std::cin, ext);

		std::cout << defaultExtension(filename, ext) << std::endl;
	}
}

std::string defaultExtension(const std::string& filename, const std::string& ext)
{
	std::size_t dotPos = lastDotPos(filename);

	if (ext.at(0) == '*')
	{
		return getRoot(filename) + getExtension(ext);
	}
	else
	{
		return (lastDotPos(filename) == std::string::npos) ? (filename + ext) : filename;
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
	for (std::size_t i = 0; i < filename.length(); ++i)
	{
		std::size_t currentPos = filename.length() - i - 1;
		if (filename.at(currentPos) == '.')
		{
			return currentPos;
		}
	}

	return std::string::npos;
}
