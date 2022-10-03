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

double calcCurrentTime();
int linearSearch(Vector<int>& vec, const int val, int& count);
int binarySearch(Vector<int>& vec, const int val, int& count);
int binarySearch(Vector<int>& vec, int start, int end, const int val, int& count);

void mergeSort(Vector<int>& vec);
void merge(Vector<int>& vec, Vector<int>& v1, Vector<int>& v2);

int main()
{
	Vector<int> vec;
	Vector<int> N;
	N += 10, 100, 1000, 10000, 100000;

	std::cout << "線形探索" << std::endl;
	setRandomSeed(1);
	for (int i = 0; i < N.size(); ++i)
	{
		vec.clear();
		for (int j = 0; j < N[i]; ++j)
		{
			vec += randomInteger(0, 10000);
		}
		mergeSort(vec);
		int compare = randomInteger(0, 10000);
		int count = 0;
		std::cout << linearSearch(vec, compare, count) << std::endl;
		std::cout << std::setw(7) << N[i] << "  " << std::setw(7) << count << "回" << std::endl;
	}

	std::cout << "二分探索" << std::endl;
	setRandomSeed(1);
	for (int i = 0; i < N.size(); ++i)
	{
		vec.clear();
		for (int j = 0; j < N[i]; ++j)
		{
			vec += randomInteger(0, 10000);
		}
		mergeSort(vec);
		int compare = randomInteger(0, 10000);
		int count = 0;
		binarySearch(vec, compare, count);
		std::cout << std::setw(7) << N[i] << "  " << std::setw(7) << count << "回" << std::endl;
	}
}

double calcCurrentTime()
{
	return double(clock()) / CLOCKS_PER_SEC;
}

int linearSearch(Vector<int>& vec, const int val, int& count)
{
	int n = vec.size();
	for (int i = 0; i < n; ++i)
	{
		++count;
		if (vec[i] == val)return i;
	}

	return -1;
}

int binarySearch(Vector<int>& vec, const int val, int& count)
{
	return binarySearch(vec, 0, vec.size(), val, count);
}

int binarySearch(Vector<int>& vec, int start, int end, const int val, int& count)
{
	++count;
	int mid = (end + start) / 2;
	if (vec[mid] == val)return mid;
	if (end - start == 1)return -1;

	if (vec[mid] < val)
	{
		return binarySearch(vec, mid, end, val, count);
	}
	else
	{
		return binarySearch(vec, start, mid, val, count);
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
