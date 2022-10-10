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

Tower* createBeaconOfGondor();
Tower* createTower(const std::string& name, Tower* link);
void freeTower(Tower* tp);

int main() {
	Tower* tp = createBeaconOfGondor();
	Tower* startTp = tp;

	while (tp) {
		std::cout << tp->name << std::endl;
		tp = tp->link;
	}

	//	解放
	freeTower(startTp);
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

void freeTower(Tower* tp) {
	while (tp) {
		Tower* next = tp->link;
		delete tp;
		tp = next;
	}
}

