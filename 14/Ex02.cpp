#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "Library/vector.h"

template <typename ValueType>
void swap(ValueType& x, ValueType& y) {
	ValueType tmp = x;
	x = y;
	y = tmp;
}

template <typename ValueType>
void quickSort(Vector<ValueType>& vec, int start, int end) {
	if (start >= end)return;

	int rh = end;
	int lh = start;
	int pivot = start;
	++lh;
	while (1) {
		while (vec[pivot] <= vec[rh] && rh > lh)--rh;
		while (vec[lh] < vec[pivot] && rh > lh)++lh;
		if (rh == lh)break;
		
		swap(vec[rh], vec[lh]);
	}

	if (vec[pivot] <= vec[rh]) {
		quickSort(vec, pivot + 1, end);
	}
	else {
		swap(vec[rh], vec[pivot]);
		quickSort(vec, start, rh - 1);
		quickSort(vec, rh + 1, end);
	}
}

//	quick sort
template <typename ValueType>
void sort(Vector<ValueType>& vec) {
	quickSort(vec, 0, vec.size() - 1);
}

int main() {
	Vector<int> vec;
	vec += 56, 25, 37, 58, 95, 19, 73, 30;
	quickSort(vec, 0, vec.size() - 1);

	for (int i = 0; i < vec.size(); ++i)
	{
		std::cout << vec[i] << std::endl;
	}
}

