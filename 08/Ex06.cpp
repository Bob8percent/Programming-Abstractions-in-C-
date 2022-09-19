#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

bool isMeasurable(int target, Vector<int>& weights);

int main()
{
	Vector<int> weights;
	weights += 1, 3,4,5;
	std::cout << std::boolalpha << isMeasurable(5, weights) << std::endl;
}

bool isMeasurable(int target, Vector<int>& weights)
{
	if (weights.isEmpty())
	{
		return target == 0;
	}
	
	int end = weights.size() - 1;
	int w = weights[end];
	weights.remove(end);
	//	targetの反対側の皿に置くか、target側の皿に置くか、除外するか
	return isMeasurable(target - w, weights) || isMeasurable(target + w, weights) || isMeasurable(target, weights);
}


