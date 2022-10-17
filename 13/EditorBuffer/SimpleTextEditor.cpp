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
	char ch = line.at(0);
	switch (ch) {
	case 'F':
		eb.moveCursorForward();
		break;
	case 'B':
		eb.moveCursorBackward();
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
		eb.deleteCharacter();
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
