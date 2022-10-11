#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/stack.h"
#include "CharStack.h"
#include "UnitTest.h"

struct Tower {
	std::string name;
	Tower* link;
};

Tower* readBeaconsFromFile(const std::string& filename);

int main() {
	Tower* tp = readBeaconsFromFile("BeaconsOfGondor.txt");

	while (tp) {
		std::cout << tp->name << std::endl;
		tp = tp->link;
	}
}

Tower* readBeaconsFromFile(const std::string& filename) {
	std::ifstream ifs;
	ifs.open(filename);
	if (ifs.fail()) {
		std::cerr << "ERROR : Tower* readBeaconsFromFile(const std::string& filename) : "
			<< "ファイルを開けません" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	std::string name;
	int i = 0;
	Tower* startTower = nullptr;
	Tower* previous = nullptr;
	while (std::getline(ifs, name)) {
		Tower* tp = new Tower;
		tp->name = name;
		tp->link = nullptr;
		if (i > 0)previous->link = tp;
		else startTower = tp;
		previous = tp;
		++i;
	}

	return startTower;
}


