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
void multipleLines(EditorBuffer& eb);
void insertLine(EditorBuffer& eb, const std::string& line);

int main() {
	EditorBuffer eb;
	while (1) {
		std::string line;
		std::getline(std::cin, line);
		executeCommand(eb, line);
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
	case 'T':
		displayBuffer(eb);
		break;
	case 'A':
		multipleLines(eb);
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
	std::cout << eb.getText() << std::endl;
}

void insertLine(EditorBuffer& eb, const std::string& line) {
	for (std::size_t i = 0; i < line.length(); ++i) {
		eb.insertCharacter(line.at(i));
	}
}

void multipleLines(EditorBuffer& eb) {
	while (1) {
		std::string line;
		std::getline(std::cin, line);
		if (!line.empty()) {
			if (line.at(0) == '.')break;

			for (std::size_t i = 0; i < line.length(); ++i) {
				eb.insertCharacter(line.at(i));
			}
		}
		eb.insertCharacter('\n');
	}
}

void printHelp() {
	std::cout << "Help(Command List): F, B, J, E, Ixxx, D, T, A, H, Q" << std::endl;
}
