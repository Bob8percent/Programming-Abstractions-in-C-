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

template <typename IterType, typename ValueType>
int count_if(IterType start, IterType end, bool (*fn)(ValueType)) {
	int count = 0;
	for (IterType i = start; i != end; i++) {
		if (fn(*i)) ++count;
	}
	return count;
}

int main() {
	Vector<int> v;
	v += 1, 3, 4, 2, 4, 5, 6, 3, 2, 10, 1, 2, 3, 5;
	std::cout << count_if<Vector<int>::iterator, int>(v.begin(), v.end(), [](int x) {return x == 1; }) << std::endl;
}
