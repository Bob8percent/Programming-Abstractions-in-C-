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

//	配列とポインタの違いは宣言時にストレージが割り当てられるか否か。
//	ポインタは初期化時に割り当てられる

int main()
{
	//	error : 未割当て
	int* p;
	std::cout << p << std::endl;

	//	アドレスが表示される
	int array[4];
	std::cout << array << std::endl;
}


