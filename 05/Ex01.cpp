
/*
* readVectorの実装
*/

#define _USE_MATH_DEFINES

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "String.h"
#include "Library/vector.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

void promptForOpenFile(std::ifstream& ifs, const std::string& prompt);
void promptForOpenFile(std::ofstream& ofs, const std::string& prompt);
void readVector(std::istream& is, Vector<int>& vec);
void readVector(std::istream& is, Vector<double>& vec);
void readVector(std::istream& is, Vector<std::string>& vec);
void writeVector(std::ostream& os, Vector<int>& vec);
void writeVector(std::ostream& os, Vector<double>& vec);
void writeVector(std::ostream& os, Vector<std::string>& vec);

int stringToInteger(const std::string& str);
double _stringToReal(const std::string& str);

int main()
{
	std::ifstream ifs;
	promptForOpenFile(ifs, "入力ファイル名：");
	std::ofstream ofs;
	promptForOpenFile(ofs, "出力ファイル名：");

	//Vector<int> vec;
	Vector<double> vec;
	//Vector<std::string> vec;
	readVector(ifs, vec);
	readVector(ifs, vec);
	//readVector(ifs, vec);
	writeVector(ofs, vec);
}

void promptForOpenFile(std::ifstream& ifs, const std::string& prompt)
{
	while (1)
	{
		std::cout << prompt;
		std::string filename = "";
		std::getline(std::cin, filename);

		ifs.open(filename);
		if (!ifs.fail())
		{
			return;
		}

		ifs.clear();
		std::cout << "ERROR : void promptForOpenFile(std::ifstream& ifs, const std::string& prompt) : "
			<< "ファイルが開けません" << std::endl;
	}
}

void promptForOpenFile(std::ofstream& ofs, const std::string& prompt)
{
	while (1)
	{
		std::cout << prompt;
		std::string filename = "";
		std::getline(std::cin, filename);

		ofs.open(filename);
		if (!ofs.fail())
		{
			return;
		}

		ofs.clear();
		std::cout << "ERROR : void promptForOpenFile(std::ofstream& ofs, const std::string& prompt) : "
			<< "ファイルが開けません" << std::endl;
	}
}

void readVector(std::istream& is, Vector<int>& vec)
{
	vec.clear();
	std::string line = "";
	while (std::getline(is,line))
	{
		if (line == "")
		{
			return;
		}
		vec.add(stringToInteger(line));
	}
}

void readVector(std::istream& is, Vector<double>& vec)
{
	vec.clear();
	std::string line = "";
	while (std::getline(is, line))
	{
		if (line == "")
		{
			return;
		}
		vec.add(_stringToReal(line));
	}
}

void readVector(std::istream& is, Vector<std::string>& vec)
{
	vec.clear();
	std::string line = "";
	while (std::getline(is, line))
	{
		if (line == "")
		{
			return;
		}
		vec.add(line);
	}
}

void writeVector(std::ostream& os, Vector<int>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		os << vec[i] << std::endl;
	}
}

void writeVector(std::ostream& os, Vector<double>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		os << vec[i] << std::endl;
	}
}

void writeVector(std::ostream& os, Vector<std::string>& vec)
{
	for (int i = 0; i < vec.size(); ++i)
	{
		os << vec[i] << std::endl;
	}
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
	return -1;
}

double _stringToReal(const std::string& str)
{
	std::istringstream iss(str);
	double value;
	iss >> value >> std::skipws;
	if (!iss.fail() && iss.eof())
	{
		return value;
	}

	std::cout << "ERROR : double stringToReal(const std::string& str) : "
		<< "文字列を実数に変換できません" << std::endl;
	return -1;
}
