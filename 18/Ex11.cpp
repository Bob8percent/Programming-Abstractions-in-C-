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
	Vector<Flight*> path = g.findShortestPath("Atlanta", "Portland");
	double cost = 0;
	std::cout << "Atlanta";
	for (Flight* f : path) {
		std::cout << " -> " << f->getEndName();
		cost += f->getCost();
	}
	std::cout << cost << std::endl;
}
