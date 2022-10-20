#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
#include "TokenScanner.h"
#include "Library/stack.h"
#include "CharStack.h"
#include "UnitTest.h"
#include "PigLatin.h"
#include "EditorBuffer.h"

//	以下の関数：クラス化したほうがよさそうだけども
//	controllerとview
void executeCommand(EditorBuffer& eb, const std::string& line);
void displayBuffer(EditorBuffer& eb);
void printHelp();
int countLoop(const std::string& str);
char getCommand(const std::string& str);

int main() {
	EditorBuffer eb;
	while (1) {
		std::string line;
		std::getline(std::cin, line);
		executeCommand(eb, line);
		displayBuffer(eb);
	}
}

void executeCommand(EditorBuffer& eb, const std::string& line) {
	char ch = getCommand(line);
	int count = countLoop(line);
	switch (ch) {
	case 'F':
		for (int i = 0; i < count; ++i)eb.moveCursorForward();
		break;
	case 'B':
		for (int i = 0; i < count; ++i)eb.moveCursorBackward();
		break;
	case 'J':
		eb.moveCursorToStart();
		break;
	case 'E':
		eb.moveCursorToEnd();
		break;
	case 'I':
		for (std::size_t i = 1; i < line.length(); ++i) {
			eb.insertCharacter(line.at(i));
		}
		break;
	case 'D':
		for (int i = 0; i < count; ++i)eb.deleteCharacter();
		break;
	case 'H':
		printHelp();
		break;
	case 'Q':
		std::exit(0);	//	正常終了
		break;
	default:
		break;
	}
}

int countLoop(const std::string& str) {
	int len = (int)str.length();
	int digits = 1;
	int count = 0;
	for (int i = len - 2; i >= 0; --i) {
		count += digits * (str.at(i) - '0');
		digits *= 10;
	}
	return count;
}

char getCommand(const std::string& str) {
	if (isalpha(str.at(0))) {
		return str.at(0);
	}
	if (isalpha(str.at(str.length() - 1))) {
		return str.at(str.length() - 1);
	}

	return -1;
}

void displayBuffer(EditorBuffer& eb) {
	std::string buffer = eb.getText();
	for (std::size_t i = 0; i < buffer.length(); ++i) {
		std::cout << ' ' << buffer.at(i);
	}
	std::cout << std::endl;

	for (int i = 0; i < eb.getCursor(); ++i) {
		std::cout << "  ";
	}
	std::cout << '^' << std::endl;
}

void printHelp() {
	std::cout << "Help(Command List): F, B, J, E, Ixxx, D, H, Q" << std::endl;
}
