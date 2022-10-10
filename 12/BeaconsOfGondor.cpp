#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/stack.h"

struct Tower {
	std::string name;
	Tower* link;
};

//	Link-Listをつくる
Tower* createBeaconOfGondor();
Tower* createTower(const std::string& name, Tower* link);

int main() {
	Tower* tp = createBeaconOfGondor();

	while (tp) {
		std::cout << tp->name << std::endl;
		tp = tp->link;
	}
}

Tower* createBeaconOfGondor() {
	Tower* tp = createTower("Rohan", nullptr);
	tp = createTower("Halifirien", tp);
	tp = createTower("Calenhad", tp);
	tp = createTower("Min-Rimmon", tp);
	tp = createTower("Erelas", tp);
	tp = createTower("Nardol", tp);
	tp = createTower("Eilenach", tp);
	tp = createTower("Amon Din", tp);
	tp = createTower("Minas Tirith", tp);

	return tp;
}

Tower* createTower(const std::string& name, Tower* link) {
	Tower* tower = new Tower;
	tower->name = name;
	tower->link = link;

	return tower;
}
