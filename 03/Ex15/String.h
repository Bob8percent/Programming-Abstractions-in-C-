#pragma once
#include <string>

/*
* chが母音かどうかを返す関数
*/
bool isVowel(char ch);

/*
* 文字列をすべて小文字にする関数
*/
std::string toLowerStr(const std::string& str);

/*
* 文字列中の最初の母音のインデックスを返す関数
* ただし、母音が含まれていないときは-1を返す
*/
int isIncludeVowel(const std::string& str);

/*
* 文字列の接尾語が指定したものかどうかを返す関数
*/
bool endWith(const std::string& str, const std::string& suffix);
bool endWith(const std::string& str, const char suffix);

/*
* 文字列から先頭および末尾の空白文字を削除した文字列を返す関数
*/
std::string trim(const std::string& str);
std::string trimBack(const std::string & str);
std::string trimFront(const std::string & str);
std::string trimChar(const std::string& str, std::size_t num);

