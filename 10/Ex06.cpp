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

//	昇順であるほどクイックソートは分割しずらくなり遅くなるのがデメリットだったが、
//	pivotを最初、中間、最後の中央値にすることである程度解決できる
//	ランダムな数列のソートについてはあまり変わらない
double calcCurrentTime();
void quickSort(Vector<int>& vec, int lh, int rh);
void new_quickSort(Vector<int>& vec, int lh, int rh);

int main()
{
	Vector<int> vec;
	Vector<int> N;
	N += 10, 100, 1000;	//	ソート済みの配列を扱う場合、10000以上はスタックオーバーフローしてしまうので未確認

	std::cout << "最初の要素をpivotにした" << std::endl;
	setRandomSeed(1);
	for (int i = 0; i < N.size(); ++i)
	{
		vec.clear();
		for (int j = 0; j < N[i]; ++j)
		{
			vec += randomInteger(0, 10000);
		}
		quickSort(vec, 0, vec.size() - 1);
		double start = calcCurrentTime();
		quickSort(vec, 0, vec.size() - 1);
		double end = calcCurrentTime();
		std::cout << std::setw(7) << N[i] << "  " << std::setw(7) << end - start << "秒" << std::endl;
	}

	std::cout << "最初、中間、最後の要素の中央値をpivotにした" << std::endl;
	setRandomSeed(1);
	for (int i = 0; i < N.size(); ++i)
	{
		vec.clear();
		for (int j = 0; j < N[i]; ++j)
		{
			vec += randomInteger(0, 10000);
		}
		quickSort(vec, 0, vec.size() - 1);
		double start = calcCurrentTime();
		new_quickSort(vec, 0, vec.size() - 1);
		double end = calcCurrentTime();
		std::cout << std::setw(7) << N[i] << "  " << std::setw(7) << end - start << "秒" << std::endl;
	}
}

double calcCurrentTime()
{
	return double(clock()) / CLOCKS_PER_SEC;
}

void quickSort(Vector<int>& vec, int lh, int rh)
{
	if (lh >= rh)return;
	int start = lh, end = rh;
	int pivot = lh;
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
		quickSort(vec, start + 1, end);
	}
	else
	{
		int tmp = vec[pivot];
		vec[pivot] = vec[rh];
		vec[rh] = tmp;
		quickSort(vec, start, rh - 1);
		quickSort(vec, rh + 1, end);
	}
}

void new_quickSort(Vector<int>& vec, int lh, int rh)
{
	if (lh >= rh)return;

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
		quickSort(vec, pivot + 1, end);
	}
	else
	{
		int tmp = vec[pivot];
		vec[pivot] = vec[rh];
		vec[rh] = tmp;
		quickSort(vec, start, rh - 1);
		quickSort(vec, rh + 1, end);
	}

}

