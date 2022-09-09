
/*
* ヒストグラムの表示
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

void printHistogram(const Vector<int>& data);

double mean(Vector<double>& data);

int stringToInteger(const std::string& str);
double _stringToReal(const std::string& str);

int main()
{
	std::ifstream ifs;
	promptForOpenFile(ifs, "入力ファイル名：");

	Vector<int> vec;
	readVector(ifs, vec);

	printHistogram(vec);
}

void printHistogram(const Vector<int>& data)
{
	for (int i = 0; i <= 10; ++i)
	{
		int count = 0;
		for (int d = 0; d < data.size(); ++d)
		{
			if (i * 10 <= data[d] && data[d] < (i + 1) * 10)
			{
				++count;
			}
		}

		std::string stars = "";
		while (count--)stars += '*';
		std::string str = (i != 10) ? "0s: " : "0: ";
		std::cout << i << str << stars << std::endl;
	}
}


double mean(Vector<double>& data)
{
	double sum = 0;
	for (int i = 0; i < data.size(); ++i)
	{
		sum += data[i];
	}
	return sum / data.size();
}

/*
* 標準偏差を求める
*/
double stddev(Vector<double>& data)
{
	double ave = mean(data);
	double subSqSum = 0;
	for (int i = 0; i < data.size(); ++i)
	{
		double val = data[i] - ave;
		subSqSum += val * val;
	}
	return std::sqrt(subSqSum / data.size());
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
