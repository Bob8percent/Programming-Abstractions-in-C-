#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include "_Grid.h"

int main() {
	int row = 4;
	int col = 5;
	Grid<int> g(row, col);
	for (int i = 0; i < row; ++i) {
		for (int j = 0; j < col; ++j) {
			g[i][j] = i + j;
		}
	}

	for (Grid<int>::iterator i = g.begin(); i != g.end(); ++i) {
		std::cout << *i << std::endl;
	}
}
