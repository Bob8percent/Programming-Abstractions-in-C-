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
void selectionSort(Vector<int>& vec);
void mergeSort(Vector<int>& vec);
void merge(Vector<int>& vec, Vector<int>& v1, Vector<int>& v2);

void generateRandInteger(Vector<int>& vec, int n);

int main()
{
	Vector<int> vec;
	Vector<int> N;
	N += 10, 100, 1000, 10000;

	std::cout << "選択ソート" << std::endl;
	for (int i = 0; i < N.size(); ++i)
	{
		vec.clear();
		setRandomSeed(1);
		generateRandInteger(vec, N[i]);

		double start = calcCurrentTime();
		selectionSort(vec);
		double end = calcCurrentTime();
		std::cout << std::fixed;
		std::cout << std::setw(7) << N[i] << "  " << std::setprecision(7) << end - start << "秒" << std::endl;

	}

	std::cout << "マージソート" << std::endl;
	for (int i = 0; i < N.size(); ++i)
	{
		vec.clear();
		setRandomSeed(1);
		generateRandInteger(vec, N[i]);
		double start = calcCurrentTime();
		mergeSort(vec);
		double end = calcCurrentTime();
		std::cout << std::setw(7) << N[i] << "  " << std::setw(7) << end - start << "秒" << std::endl;
	}
}

void generateRandInteger(Vector<int>& vec, int n)
{
	for (int i = 0; i < n; ++i)
	{
		vec += randomInteger(0, n);
	}
}

double calcCurrentTime()
{
	return double(clock()) / CLOCKS_PER_SEC;
}

void selectionSort(Vector<int>& vec)
{
	for (int i = 0; i < vec.size() - 1; ++i)
	{
		int min = vec[i];
		int min_idx = i;
		for (int j = i + 1; j < vec.size(); ++j)
		{
			if (min > vec[j])
			{
				min = vec[j];
				min_idx = j;
			}
		}

		//	iとmin_idxを交換
		int tmp = vec[i];
		vec[i] = vec[min_idx];
		vec[min_idx] = tmp;
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

