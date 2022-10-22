#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <string>
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

//	有限情報ステートマシン
enum State { s0, s1, s2, s3, s4};
void executeCommand(EditorBuffer& eb, const std::string& line) {
	if (line.empty())return;
	State state = s0;
	std::string word;
	int count = 1;	//	数値が入力された時の変数
	std::size_t scanningPos = 0;

	while (1) {
		char ch = line.at(scanningPos);

		if (state == s0) {
			switch (ch) {
			case 'J':
				eb.moveCursorToStart();
				return;
			case 'E':
				eb.moveCursorToEnd();
				return;
			case 'F':
				eb.moveCursorForward();
				return;
			case 'B':
				eb.moveCursorBackward();
				return;
			case 'P':
				eb.paste();
				return;
			case 'H':
				printHelp();
				return;
			case 'Q':
				std::exit(0);	//	正常終了
				return;
			case 'I':
				for (std::size_t i = 1; i < line.length(); ++i) {
					eb.insertCharacter(line.at(i));
				}
				return;
			case 'S':
				for (std::size_t i = 1; i < line.length(); ++i) {
					word += line.at(i);
				}
				std::cout << std::boolalpha<<eb.search(word) << std::endl;
				return;
			case 'W':
				state = s1;
				break;
			default:
				if (isdigit(ch)) {
					state = s2;
					continue;
				}
				else return;
			}
		}
		else if (state == s1) {
			switch (ch) {
			case 'B':
				eb.moveCursorBackwardSkip();
				return;
			case 'F':
				eb.moveCursorForwardSkip();
				return;
			case 'D':
				eb.deleteWord();
				return;
			default:
				return;
			}
		}
		else if (state == s2) {
			std::string numStr;
			for (std::size_t i = 0; i < line.length(); ++i) {
				if (isdigit(line.at(i)))numStr += line.at(i);
				else break;
			}
			int num = 0;
			int digit = 1;
			for (std::size_t i = 0; i < numStr.length(); ++i) {
				num += (numStr[numStr.length() - 1 - i] - '0') * digit;
				digit *= 10;
			}
			count = num;
			scanningPos += (numStr.length() - 1);

			state = s3;
		}
		else if (state == s3) {
			switch (ch) {
			case 'B':
				for (int i = 0; i < count; ++i)eb.moveCursorBackward();
				return;
			case 'F':
				for (int i = 0; i < count; ++i)eb.moveCursorForward();
				return;
			case 'D':
				for (int i = 0; i < count; ++i)eb.deleteCharacter();
				return;
			case 'C':
				eb.copy(count);
				return; 
			case 'X':
				eb.copy(count);
				for (int i = 0; i < count; ++i)eb.deleteCharacter();
				return;
			default:
				return;
			}
		}

		++scanningPos;
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
