#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "graphpriv.h"
#include "Library/vector.h"

int main() {
	std::ifstream ifs;
	ifs.open("C18Ex14.txt");
	if (ifs.fail()) {
		std::cerr << "ERROR : ファイルを開けません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	Graph<City, Flight> g;
	g.readGraph(ifs);

	g.findDominatingSet();
	std::set<City*> s = g.findDominatingSet();
	for (City* c : s) {
		std::cout << c->getName() << std::endl;
	}
}
