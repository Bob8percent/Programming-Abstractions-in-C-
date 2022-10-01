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

//	正しくpivotが設定され、pivotによってほぼ半分に分割される場合クイックソートは有効(つまりある程度値がランダムであるときに有効)。
//	分割が偏っている場合、逆に遅くなってしまう。最悪なケースは、すでにソートされている数列にクイックソートを使う場合。このとき、
//	常に1つとn-1つに分割されるのでO(N^2)になってしまう。
//	対策として、pivotをその都度ランダムに設定することで平均O(NlogN)にできる。ただ、適切なpivotを設定する処理に凝りすぎてしまうと
//	それにより負荷が増してしまう可能性もあるので注意。
//	正しくpivotが設定されていれば、同じ分割統治であるマージソートより当然速い。
void quickSort(Vector<int>& vec, int lh, int rh);

int main()
{
	Vector<int> vec;
	vec += 56, 25, 37, 58, 95, 19, 73, 30;
	quickSort(vec, 0, vec.size() - 1);

	for (int i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << std::endl;
	}
}

void quickSort(Vector<int>& vec, int lh, int rh)
{
	std::cout << "lh:" << lh << " rh:" << rh << std::endl;
	for (int i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
	if (lh >= rh)return;
	int start = lh + 1, end = rh;
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


