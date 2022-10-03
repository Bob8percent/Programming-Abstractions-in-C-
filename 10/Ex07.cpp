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

//	選択ソートはサイズが小さいときに力を発揮するので、
//	サイズの小さいときは選択ソート、大きいときはクイックソートを使うハイブリッド戦略を実装する
double calcCurrentTime();

void hybridSort(Vector<int>& vec, const int crossOverPoint);
void h_quickSort(Vector<int>& vec, int lh, int rh, const int crossOverPoint);
void h_selectionSort(Vector<int>& vec, int lh, int rh);

int main()
{
	Vector<int> vec;
	Vector<int> N;
	N += 10, 100, 1000, 10000,100000;
	Vector<int> crossOverPoints;
	crossOverPoints += 10, 50, 100, 200, 500, 1000;

	std::cout << "ハイブリッドソート";
	setRandomSeed(1);
	for (int k = 0; k < crossOverPoints.size(); ++k)
	{
		std::cout << " COP:" << crossOverPoints[k] << std::endl;
		for (int i = 0; i < N.size(); ++i)
		{
			vec.clear();
			for (int j = 0; j < N[i]; ++j)
			{
				vec += randomInteger(0, 10000);
			}
			double start = calcCurrentTime();
			hybridSort(vec, 1000);
			double end = calcCurrentTime();
			std::cout << std::setw(7) << N[i] << "  " << std::setw(7) << end - start << "秒" << std::endl;
		}
	}
}

double calcCurrentTime()
{
	return double(clock()) / CLOCKS_PER_SEC;
}

void hybridSort(Vector<int>& vec, const int crossOverPoint)
{
	h_quickSort(vec, 0, vec.size() - 1, crossOverPoint);
}

void h_quickSort(Vector<int>& vec, int lh, int rh, const int crossOverPoint)
{
	if (lh >= rh)return;
	if ((rh - lh) <= crossOverPoint)
	{
		h_selectionSort(vec, lh, rh);
		return;
	}

	//	pivotは最初、中間、最後の中央値にする
	int pivot = lh;
	int midIdx = (lh + rh) / 2;
	if (vec[lh] <= vec[midIdx] && vec[midIdx] <= vec[rh])pivot = midIdx;
	else if (vec[rh] <= vec[midIdx] && vec[midIdx] <= vec[lh])pivot = midIdx;
	else if (vec[midIdx] <= vec[lh] && vec[lh] <= vec[rh])pivot = lh;
	else if (vec[rh] <= vec[lh] && vec[lh] <= vec[midIdx])pivot = lh;
	else if (vec[midIdx] <= vec[rh] && vec[rh] <= vec[lh])pivot = rh;
	else if (vec[lh] <= vec[rh] && vec[rh] <= vec[midIdx])pivot = rh;

	int tmp = vec[pivot];
	vec[pivot] = vec[lh];
	vec[lh] = tmp;
	int start = lh, end = rh;
	pivot = lh;
	++lh;

	while (1)
	{
		//	rhを移動してpivotより小さいものを探す
		while (vec[pivot] <= vec[rh] && rh > lh)--rh;
		//	lhを移動してpivotより大きいものを探す
		while (vec[pivot] > vec[lh] && rh > lh)++lh;
		if (rh == lh)break;
		int tmp = vec[lh];
		vec[lh] = vec[rh];
		vec[rh] = tmp;
	}

	//	vec[pivot]より右側にある要素がすべて大きい場合
	if (vec[pivot] <= vec[rh])
	{
		//quickSort(vec, start, start - 1);
		h_quickSort(vec, pivot + 1, end, crossOverPoint);
	}
	else
	{
		int tmp = vec[pivot];
		vec[pivot] = vec[rh];
		vec[rh] = tmp;
		h_quickSort(vec, start, rh - 1, crossOverPoint);
		h_quickSort(vec, rh + 1, end, crossOverPoint);
	}
}

void h_selectionSort(Vector<int>& vec, int lh, int rh)
{
	for (int i = lh; i <= rh; ++i)
	{
		int min = vec[i];
		int min_idx = i;
		for (int j = i + 1; j <= rh; ++j)
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

