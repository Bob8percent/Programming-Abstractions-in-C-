#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "graphpriv.h"
#include "Library/vector.h"

int main() {
	std::ifstream ifs;
	ifs.open("AirlineGraph.txt");
	if (ifs.fail()) {
		std::cerr << "ERROR : ファイルを開けません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	Graph<City, Flight> g;
	g.readGraph(ifs);


	//	ユーザー入力
	std::string s1, s2;
	std::cout << "地点1 : ";
	std::getline(std::cin, s1);
	std::cout << "地点2 : ";
	std::getline(std::cin, s2);

	Vector<Flight*> path = g.findShortestPath(s1, s2);

	bool isFirst = true;
	for (Flight* f : path) {
		if (isFirst) {
			std::cout << f->getStartName();
			isFirst = false;
		}
		std::cout << " -> " << f->getEndName();
	}
}
