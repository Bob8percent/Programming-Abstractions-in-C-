#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"

//  TokenScannerについて、scanStringを有効にすると、引用符で囲まれた文字列が単一のトークンとして得られる
int main()
{
	TokenScanner scanner("aaa \"bbb is bbb\" ccc \'ddd\" e f ");
	scanner.ignoreWhiteSpace();
	scanner.scanString();
	while (scanner.hasMoreTokens())
	{
		std::cout << scanner.nextToken() << std::endl;
	}
}
