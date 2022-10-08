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

//	挿入ソートはある程度ソートされている配列に対して高速。
//	配列のサイズがTHRESHHOLDになるまでクイックソートを行い、そこからは挿入ソートするハイブリッドソートする
double calcCurrentTime();

enum SORT_MODE {
	HYBLID_SELECTION,
	HYBLID_INSERTION
};

void hybridSort(Vector<int>& vec, SORT_MODE mode);
void h_quickSort(Vector<int>& vec, int lh, int rh, SORT_MODE mode);
void h_selectionSort(Vector<int>& vec, int lh, int rh);
void h_insertionSort(Vector<int>& vec);

const int crossOverPoint = 5;
const int threshhold = 20;

int main()
{
	Vector<int> vec;
	Vector<int> N;
	N += 10, 100, 1000, 10000, 100000, 1000000;

	setRandomSeed(1);
	std::cout << "クイックソート + 選択ソート" << std::endl;
	for (int i = 0; i < N.size(); ++i)
	{
		vec.clear();
		for (int j = 0; j < N[i]; ++j)
		{
			vec += randomInteger(0, 10000);
		}
		double start = calcCurrentTime();
		hybridSort(vec, HYBLID_SELECTION);
		double end = calcCurrentTime();
		if (i == 0) {
			for (int k = 0; k < N[i]; ++k) {
				std::cout << vec[k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::setw(7) << N[i] << "  " << std::setw(7) << end - start << "秒" << std::endl;
	}

	setRandomSeed(1);
	std::cout << "クイックソート + 挿入ソート" << std::endl;
	for (int i = 0; i < N.size(); ++i)
	{
		vec.clear();
		for (int j = 0; j < N[i]; ++j)
		{
			vec += randomInteger(0, 10000);
		}
		double start = calcCurrentTime();
		hybridSort(vec, HYBLID_INSERTION);
		double end = calcCurrentTime();
		if (i == 0) {
			for (int k = 0; k < N[i]; ++k) {
				std::cout << vec[k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::setw(7) << N[i] << "  " << std::setw(7) << end - start << "秒" << std::endl;
	}
}

double calcCurrentTime()
{
	return double(clock()) / CLOCKS_PER_SEC;
}

void hybridSort(Vector<int>& vec, SORT_MODE mode)
{
	h_quickSort(vec, 0, vec.size() - 1, mode);
}

void h_quickSort(Vector<int>& vec, int lh, int rh, SORT_MODE mode)
{
	if (lh >= rh)return;
	if ((rh - lh) <= crossOverPoint && mode == HYBLID_SELECTION)
	{
		h_selectionSort(vec, lh, rh);
		return;
	}
	if ((rh - lh) <= threshhold && mode == HYBLID_INSERTION) {
		h_insertionSort(vec);
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
		h_quickSort(vec, pivot + 1, end, mode);
	}
	else
	{
		int tmp = vec[pivot];
		vec[pivot] = vec[rh];
		vec[rh] = tmp;
		h_quickSort(vec, start, rh - 1, mode);
		h_quickSort(vec, rh + 1, end, mode);
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

void h_insertionSort(Vector<int>& vec)
{
	for (int i = 1; i < vec.size(); ++i)
	{
		//	i を0 ~ i-1 のうちの正しい位置に挿入する
		//	0 ~ i-1 まで既に整列されていることを利用
		int tmp = vec[i];
		int j = i - 1;
		while (j >= 0)
		{
			//	右にずらす
			if (vec[j] > tmp)
			{
				vec[j + 1] = vec[j];
			}
			else break;

			--j;
		}
		vec[j + 1] = tmp;	//	挿入
	}
}
