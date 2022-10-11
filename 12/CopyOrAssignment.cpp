#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/stack.h"
#include "CharStack.h"
#include "UnitTest.h"

int main() {
	CharStack cstk;
	cstk.push('A');

	CharStack tmp1 = cstk;	//	初期化なので、代入演算子ではなくコピーコンストラクタが呼ばれる

	CharStack tmp2;
	tmp2 = cstk;			//	コピーコンストラクタではなく代入演算子が呼ばれる
}


