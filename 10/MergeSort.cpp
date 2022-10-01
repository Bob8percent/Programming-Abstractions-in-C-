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
#include "Library/map.h"
#include "Library/set.h"


void mergeSort(Vector<int>& vec);
void merge(Vector<int>& vec, Vector<int>& v1, Vector<int>& v2);

int main()
{
	Vector<int> vec;
	vec += 56, 25, 37, 58, 95, 19, 73, 30;
	mergeSort(vec);

	for (int i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << std::endl;
	}
}

void mergeSort(Vector<int>& vec)
{
	int n = vec.size();
	if (n <= 1)return;
	Vector<int> v1, v2;
	
	for (int i = 0; i < n; ++i)
	{
		if (i < n / 2)v1 += vec[i];
		else v2 += vec[i];
	}

	mergeSort(v1);
	mergeSort(v2);
	vec.clear();
	merge(vec, v1, v2);
}

void merge(Vector<int>& vec, Vector<int>& v1, Vector<int>& v2)
{
	int n1 = v1.size(), n2 = v2.size();
	int p1 = 0, p2 = 0;
	while (p1 < n1 && p2 < n2)
	{
		if (v1[p1] < v2[p2])
		{
			vec += v1[p1];
			++p1;
		}
		else
		{
			vec += v2[p2];
			++p2;
		}
	}

	while (p1 < n1)
	{
		vec += v1[p1];
		++p1;
	}
	while (p2 < n2)
	{
		vec += v2[p2];
		++p2;
	}
}

