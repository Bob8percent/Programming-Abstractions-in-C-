#pragma once
#include <string>

/*
* 文字列から先頭および末尾の空白文字を削除した文字列を返す関数
*/
std::string trim(const std::string& str);
std::string trimBack(const std::string & str);
std::string trimFront(const std::string & str);
std::string trimChar(const std::string& str, std::size_t num);

