#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

int countSubsetSumWays(const Set<int>& set, int target);
void countSubsetSum(const Set<int>& set, int target, int& count);

int main()
{
	Set<int> set;
	set += 1, 3, 4, 5;
	std::cout << countSubsetSumWays(set, 5) << std::endl;
	std::cout << countSubsetSumWays(set, 11) << std::endl;
}

int countSubsetSumWays(const Set<int>& set, int target)
{
	if (target == 0)return 1;
	else if (set.isEmpty()) return 0;

	int val = set.first();
	Set<int> temp = set - val;
	return countSubsetSumWays(temp, target) + countSubsetSumWays(temp, target - val);
}
