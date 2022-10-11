#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include "TokenScanner.h"
#include "Library/stack.h"
#include "CharStack.h"
#include "UnitTest.h"

char* copyCString(char* str);

int main() {
	char str[] = { 'A','B' ,'C' ,'D' ,'\0' };

	char* newStr = copyCString(str);

	std::cout << newStr << std::endl;

	delete[] newStr;
}

char* copyCString(char* str) {
	if (!str)return nullptr;

	int strSize = 0;
	while (str[strSize++] != '\0');

	char* newStr = new char[strSize];
	for (int i = 0; i < strSize; ++i) {
		newStr[i] = str[i];
	}

	return newStr;
}


