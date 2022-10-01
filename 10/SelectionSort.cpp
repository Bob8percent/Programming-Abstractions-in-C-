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

/*
* Selection Sort
* 
* i番目の値とi+1番目以降の最小値を交換する操作を繰り返す。
* 最小値、2番目に小さい値、3番目に小さい値…と0番目から格納されていく
*/
void selectionSort(Vector<int>& vec);

int main()
{
	Vector<int> vec;
	vec += 56, 25, 37, 58, 95, 19, 73, 30;
	selectionSort(vec);

	for (int i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << std::endl;
	}
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

