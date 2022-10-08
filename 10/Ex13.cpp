#define _USE_MATH_DEFINES

#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <SFML/Graphics.hpp>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/random.h"
#include "Library/map.h"
#include "Library/set.h"
#include <ctime>

int findMajorityElement(Vector<int>& vec);

int main()
{
	Vector<int> vec;
	vec += 1, 1, 1, 1, 1, 1, 1, 1, 6, 74, 3, 2, 4, 5, 6;
	std::cout << findMajorityElement(vec) << std::endl;
}

int findMajorityElement(Vector<int>& vec) {
	int size = vec.size();

	int max = -1;
	for (int i = 0; i < size; ++i) {
		if (max < vec[i])max = vec[i];
	}

	Vector<int> valuesCount(max + 1, 0);
	for (int i = 0; i < size; ++i) {
		++valuesCount[vec[i]];
	}

	int majoritySize = size / 2 + 1;
	for (int i = 0; i < max; ++i) {
		if (majoritySize <= valuesCount[i]) {
			return i;
		}
	}

	return -1;
}
