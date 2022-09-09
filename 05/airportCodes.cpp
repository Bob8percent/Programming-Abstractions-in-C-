
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
#include "Library/vector.h"
#include "Library/queue.h"
#include "Library/map.h"

void promptForOpenFile(std::ifstream& ifs, const std::string& prompt);
void airportCodeToMap(Map<std::string, std::string>& airportCodeMap, std::ifstream& ifs);
void printAirportLocation(const Map<std::string, std::string>& airportCodeMap, const std::string& airportCode);

int main()
{
	std::ifstream ifs;
	promptForOpenFile(ifs, "ファイル名入力：");

	//	ファイルをmapに組み込む
	Map<std::string, std::string> airportCodeMap;
	airportCodeToMap(airportCodeMap, ifs);

	while (1)
	{
		std::cout << "Airport Code : ";
		std::string airportCode = "";
		std::getline(std::cin, airportCode);

		printAirportLocation(airportCodeMap, airportCode);
	}
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
		std::cout << "ERROR : void promptForOpenFile(std::ifstream ifs, const std::string& prompt) : "
			<< "ファイルを開けません" << std::endl;
	}
}

void airportCodeToMap(Map<std::string, std::string>& airportCodeMap, std::ifstream& ifs)
{
	const std::size_t codeCharNum = 3;
	std::string line = "";
	while (std::getline(ifs, line))
	{
		std::string key = "", value = "";
		std::size_t equalNum = 0;
		for (std::size_t i = 0; i < line.size(); ++i)
		{
			char ch = line.at(i);
			if (i < codeCharNum)
			{
				key += ch;
			}
			else if (codeCharNum < i)
			{
				value += ch;
			}
		}

		airportCodeMap.put(key, value);
	}
}

void printAirportLocation(const Map<std::string, std::string>& airportCodeMap, const std::string& airportCode)
{
	std::string location = airportCodeMap.get(airportCode);
	if (location == "")
	{
		std::cout << "そのような空港コードはありません" << std::endl;
	}
	else
	{
		std::cout << airportCode << "は" << location << "にあります" << std::endl;
	}
}
