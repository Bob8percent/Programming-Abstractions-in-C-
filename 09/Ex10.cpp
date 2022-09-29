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

int cutStock(Vector<int>& requests, const int stockLength);
bool subCutStock(Vector<int>& requests, Vector<int>& stocks);

int main()
{
	Vector<int> requests;
	requests += 4, 3, 4, 1, 7, 8;
	int stockLength = 10;
	std::cout << cutStock(requests, stockLength) << std::endl;
}

int cutStock(Vector<int>& requests, const int stockLength)
{
	Vector<int> stocks;

	while (1)
	{
		stocks += stockLength;
		if (subCutStock(requests, stocks))break;
	}

	return stocks.size();
}

bool subCutStock(Vector<int>& requests, Vector<int>& stocks)
{
	if (requests.size() == 0)return true;

	int idx = requests.size() - 1;
	int tmp = requests[idx];
	requests.remove(idx);
	
	//	requests[idx]をどのストックに入れるか
	for (int i = 0; i < stocks.size(); ++i)
	{
		if (stocks[i] >= tmp)
		{
			stocks[i] -= tmp;
			if (subCutStock(requests, stocks))return true;
			stocks[i] += tmp;
		}
	}

	//	入れ方が間違っていたらrequestsに戻す(backtrack)
	requests += tmp;
	return false;
}

//int cutStock(Vector<int>& requests, const int stockLength);
//int subCutStock(Vector<int>& requests, Vector<int>& stocks, const int stockLength);
//void cutShockAllOrder(Vector<int>& requests, Vector<int>& order, int& stockNum, const int stockLength, const int minStockNum);
//bool isAllUsed(const Vector<int>& requests);
//
//int main()
//{
//	Vector<int> requests;
//	requests += 4, 3, 4, 1, 7, 8;
//	int stockLength = 10;
//	std::cout << cutStock(requests, stockLength) << std::endl;
//}
//
//int cutStock(Vector<int>& requests, const int stockLength)
//{
//	int sum = 0;
//	for (int i = 0; i < requests.size(); ++i)
//	{
//		int val = requests[i];
//		if (val < 0 || stockLength < val)return -1;
//		sum += val;
//	}
//
//	int minStockNum = sum / stockLength + (sum % stockLength != 0);
//
//	int stockNum = requests.size();
//	Vector<int> order;
//	cutShockAllOrder(requests, order, stockNum, stockLength, minStockNum);
//
//	return stockNum;
//}
//
//void cutShockAllOrder(Vector<int>& requests, Vector<int>& order, int& stockNum, const int stockLength, const int minStockNum)
//{
//	if (order.size() == requests.size())
//	{
//		Vector<int> stocks;
//		Vector<int> tmp = order;
//		int num = subCutStock(tmp, stocks, stockLength);
//		stockNum = (stockNum > num) ? num : stockNum;
//		return;
//	}
//
//	for (int i = 0; i < requests.size(); ++i)
//	{
//		int tmp = requests[i];
//		if (tmp != -1)
//		{
//			requests[i] = -1;
//			cutShockAllOrder(requests, order += tmp, stockNum, stockLength, minStockNum);
//			requests[i] = tmp;
//			if (stockNum == minStockNum)return;
//			order.remove(order.size() - 1);
//		}
//	}
//}
//
//int subCutStock(Vector<int>& requests, Vector<int>& stocks, const int stockLength)
//{
//	if (isAllUsed(requests))return stocks.size();
//
//	if (stocks.isEmpty())
//	{
//		stocks += requests[0];
//		requests[0] = -1;
//	}
//
//	//	末尾のストックをstockLengthに可能な限り近づける
//	for (int i = 0; i < requests.size(); ++i)
//	{
//		//	-1の場合使用済みとする
//		if (requests[i] != -1)
//		{
//			int tmp = requests[i];
//			bool isAddNew = true;
//			if (stocks[stocks.size() - 1] + tmp <= stockLength)
//			{
//				stocks[stocks.size() - 1] += tmp;
//				isAddNew = false;
//			}
//			else
//			{
//				stocks += tmp;
//			}
//			requests[i] = -1;
//			int result = subCutStock(requests, stocks, stockLength);
//			if (result != -1)return result;
//
//			requests[i] = tmp;
//			if (isAddNew)stocks.remove(stocks.size() - 1);
//			else stocks[stocks.size() - 1] -= tmp;
//		}
//	}
//
//	return -1;
//}
//
//bool isAllUsed(const Vector<int>& requests)
//{
//	for (int i = 0; i < requests.size(); ++i)
//	{
//		if (requests[i] != -1)return false;
//	}
//	return true;
//}
