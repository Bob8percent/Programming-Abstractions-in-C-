#include "EditorBuffer.h"

EditorBuffer::EditorBuffer() {
	//	cursorはnullptrのとき文字0を指し、それ以外の場合、指している文字と次の文字の間にあることを意味している
	//	startは文字がないときはnullptr、あるときは最初の文字を指している
	cursor = nullptr;
	start = nullptr;
}

EditorBuffer::~EditorBuffer() {
	Cell* cell = start;
	while (cell) {
		Cell* currentCell = cell;
		cell = cell->link;
		delete currentCell;
	}
}

//	O(1)
void EditorBuffer::moveCursorForward() {
	if (start) {
		//	文字があるとき
		if (!cursor) {
			//	地点0を指しているとき
			cursor = start;
		}
		else if (cursor->link) {
			//	末尾じゃないとき
			cursor = cursor->link;
		}
	}
}

//	O(N)
void EditorBuffer::moveCursorBackward() {
	if (start) {
		//	文字があるとき
		if (cursor) {
			if (start == cursor)cursor = nullptr;
			else {
				Cell* cell = start;
				//	カーソル位置より前方のポインタを見つける
				while (cell) {
					if (cell->link == cursor) {
						cursor = cell;
						return;
					}
					cell = cell->link;
				}
			}
		}
	}
}

//	O(1)
void EditorBuffer::moveCursorToStart() {
	cursor = nullptr;
}

//	O(N)
void EditorBuffer::moveCursorToEnd() {
	if (start) {
		if (!cursor)cursor = start;

		while (cursor->link) {
			cursor = cursor->link;
		}
	}
}

//	O(1)
void EditorBuffer::insertCharacter(char ch) {
	Cell* newCell = new Cell;
	newCell->ch = ch;
	if (!cursor) {
		newCell->link = start;
		start = newCell;
		cursor = newCell;
	}
	else {
		newCell->link = cursor->link;
		cursor->link = newCell;
		cursor = newCell;
	}
}

//	O(1)
void EditorBuffer::deleteCharacter() {
	if (!cursor) {
		if (start) {
			Cell* nextCell = start->link;
			delete start;
			start = nextCell;
		}
	}
	//	cursor->linkを消す
	else if (cursor->link) {
		Cell* dCell = cursor->link;
		cursor->link = dCell->link;
		delete dCell;
	}
}

//	O(N)
std::string EditorBuffer::getText() const {
	std::string str;
	Cell* cell = start;
	while (cell) {
		str += cell->ch;
		cell = cell->link;
	}
	return str;
}

//	O(N)
int EditorBuffer::getCursor() const {
	if (!cursor)return 0;

	Cell* cell = start;
	int cursorPos = 0;
	while (cell) {
		if (cell == cursor->link) {
			return cursorPos;
			break;
		}
		cell = cell->link;
		++cursorPos;
	}
}
