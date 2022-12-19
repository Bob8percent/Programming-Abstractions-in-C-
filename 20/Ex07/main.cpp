#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include <stack>
#include <SFML/Graphics.hpp>
#include "Plot.h"
#include "Expression.h"
#include "Library/tokenscanner.h"
#include "Library/strlib.h"

typedef double(*doubleFn)(double);
double integrate(doubleFn fn, double minX, double maxX, int width) {
	double area = 0;
	double dx = (maxX - minX) / width;
	for (int i = 0; i < width; ++i) {
		area += fn(minX + i * dx) * dx;
	}
	return area;
}

int main() {
	std::cout << integrate(std::sin, 0, PI, 20);
}
