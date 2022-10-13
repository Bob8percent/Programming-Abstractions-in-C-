#pragma once
#include "MyString.h"
//
///*
//* 文字列をPigLatinへ翻訳する関数
//*/
//std::string lineToPigLatin(const std::string& str);
//
///*
//* 英単語をPigLatinへ翻訳する関数
//*/
//std::string wordToPigLatin(const std::string& word);

/*
* 文字列をPigLatinへ翻訳する関数
*/
MyString lineToPigLatin(const MyString& str);

/*
* 英単語をPigLatinへ翻訳する関数
*/
MyString wordToPigLatin(const MyString& word);
