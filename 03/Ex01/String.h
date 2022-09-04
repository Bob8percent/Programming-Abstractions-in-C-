#pragma once
#include <string>

/*
* 文字列が指定した文字列、文字で終了するかどうかを返す関数
*/
bool endWith(const std::string& str, const std::string& suffix);
bool endWith(const std::string& str, const char suffix);
