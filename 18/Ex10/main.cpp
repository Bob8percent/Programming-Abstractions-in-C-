#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "graphpriv.h"

int main() {
	std::ifstream ifs;
	ifs.open("AirlineGraph.txt");
	if (ifs.fail()) {
		std::cerr << "ERROR : ファイルを開けません" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	Graph<City, Flight> g;
	g.readGraph(ifs);

	g.debug();

	g.writeGraph(std::cout);
}
