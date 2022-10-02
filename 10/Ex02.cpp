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

//	挿入ソート
//	ある程度ソートされているとき、入れ替え回数が減るので速い:O(N)
//	平均：O(N^2), 最悪：O(N^2)
void insertionSort(Vector<int>& vec);

int main()
{
	Vector<int> vec;
	vec += 56, 25, 37, 58, 95, 19, 73, 30;
	insertionSort(vec);

	for (int i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

void insertionSort(Vector<int>& vec)
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

		for (int k = 0; k < vec.size(); ++k)
		{
			std::cout << vec[k] << " ";
		}
		std::cout << std::endl;
	}

}
