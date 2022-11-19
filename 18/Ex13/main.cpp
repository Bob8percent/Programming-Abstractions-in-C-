#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "graphpriv.h"
#include "Library/vector.h"

int main() {
	std::ifstream ifs;
	ifs.open("CableGraph.txt");
	if (ifs.fail()) {
		std::cerr << "ERROR : ファイルを開けません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	
	Graph<City, Flight> g;
	g.readGraph(ifs);

	Graph<City, Flight> ng = g.findMinimumSpanningTree();
	ng.writeGraph(std::cout);
}
