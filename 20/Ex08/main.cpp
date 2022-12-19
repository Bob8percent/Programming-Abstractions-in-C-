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
#include "Library/vector.h"

template <typename IterType>
IterType maxElement(IterType start, IterType end) {
	IterType max = start;
	for (IterType i = start; i != end; i++) {
		if ((*max) < (*i)) {
			max = i;
		}
	}
	return max;
}

int main() {
	Vector<int> v;
	v += 1, 3, 4, 2, 4, 5, 6, 3, 2, 10, 1, 2, 3, 5;
	std::cout << *maxElement<Vector<int>::iterator>(v.begin(), v.end()) << std::endl;
}
