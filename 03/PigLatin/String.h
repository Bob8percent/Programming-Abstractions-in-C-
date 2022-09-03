#pragma once
#include <string>

/*
* chが母音かどうかを返す関数
*/
bool isVowel(const char ch);

/*
* 文字列中の最初の母音のインデックスを返す関数
* ただし、母音が含まれていないときは-1を返す
*/
int isIncludeVowel(const std::string& str);

