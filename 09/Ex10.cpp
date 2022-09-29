#define _USE_MATH_DEFINES

#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"
#include "Domino.h"

int cutStock(Vector<int>& requests, int stockLength);
int subCutStock(Vector<int>& requests, Vector<int>& stocks, int stockLength);

bool isAllUsed(const Vector<int>& requests);

int main()
{
	Vector<int> requests;
	requests += 4, 3, 4, 1, 7, 8;
	int stockLength = 10;
	std::cout << cutStock(requests, stockLength) << std::endl;
}

int cutStock(Vector<int>& requests, int stockLength)
{
	for (int i = 0; i < requests.size(); ++i)
	{
		if (requests[i] < 0 || requests[i] > stockLength)return -1;
	}

	while (1)
	{
		Vector<int> newReq=	
	}
	Vector<int> stocks;
	return subCutStock(requests, stocks, stockLength);
}

int subCutStock(Vector<int>& requests, Vector<int>& stocks, int stockLength)
{
	if (isAllUsed(requests))return stocks.size();

	if (stocks.isEmpty())
	{
		stocks += requests[0];
		requests[0] = -1;
	}

	//	末尾のストックをstockLengthに可能な限り近づける
	for (int i = 0; i < requests.size(); ++i)
	{
		//	-1の場合使用済みとする
		if (requests[i] != -1)
		{
			int tmp = requests[i];
			if (stocks[stocks.size() - 1] + tmp <= stockLength)
			{
				stocks[stocks.size() - 1] += tmp;
			}
			else continue;
			requests[i] = -1;
			int result = subCutStock(requests, stocks, stockLength);
			if (result != -1)return result;

			requests[i] = tmp;
			stocks[stocks.size() - 1] -= tmp;
		}
	}

	//	新しくストックを作る
	for (int i = 0; i < requests.size(); ++i)
	{
		if (requests[i] != -1)
		{
			int tmp = requests[i];
			stocks += tmp;
			requests[i] = -1;
			return;
		}
	}

	return -1;
}

bool isAllUsed(const Vector<int>& requests)
{
	for (int i = 0; i < requests.size(); ++i)
	{
		if (requests[i] != -1)return false;
	}
	return true;
}
