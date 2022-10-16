#include "EditorBuffer.h"

EditorBuffer::EditorBuffer() {
	//	地点0を作成
	//	ここで作らずcursorとstartにnullptrを設定しても、
	//	末尾にダミーセルを作ることになる。末尾よりも0に作った方がシンプルだ
	Cell* cell0 = new Cell;
	cell0->ch = -1;
	cell0->link = nullptr;

	//	初期位置は地点0
	cursor = new Cell;
	cursor->link = cell0;
	cursor->ch = -1;
	start = new Cell;
	start->link = cell0;
	start->ch = -1;
}

EditorBuffer::~EditorBuffer() {
	delete cursor;

	Cell* cell = start;
	while (!cell->link) {
		Cell* currentCell = cell;
		cell = cell->link;
		delete currentCell;
	}
}

//	O(1)
void EditorBuffer::moveCursorForward() {
	if (cursor->link->link) {
		cursor->link = cursor->link->link;
	}
}

void EditorBuffer::moveCursorBackward() {
	Cell* cell = start->link;

	//	カーソル位置より前方のポインタを見つける
	while (cell) {
		if (cell->link == cursor->link) {
			cursor->link = cell;
			return;
		}
		cell = cell->link;
	}
}

//	O(1)
void EditorBuffer::moveCursorToStart() {
	cursor->link = start->link;
}

//	O(N)
void EditorBuffer::moveCursorToEnd() {
	Cell* cell = start->link;
	while (1) {
		if (!cell->link) {
			cursor->link = cell;
			return;
		}
		cell = cell->link;
	}
}

//	O(1)
void EditorBuffer::insertCharacter(char ch) {
	Cell* newCell = new Cell;
	newCell->ch = ch;
	newCell->link = cursor->link->link;
	cursor->link->link = newCell;
}

void EditorBuffer::deleteCharacter() {
	Cell* dCell = cursor->link->link;
	if (dCell) {
		//	dCellが末尾ではないとき
		delete dCell;
		cursor->link->link = cursor->link->link->link;
	}
}

//	O(N)
std::string EditorBuffer::getText() const {
	std::string str;
	Cell* cell = start->link->link;
	while (cell) {
		str += cell->ch;
		cell = cell->link;
	}
	return str;
}

//	O(N)
int EditorBuffer::getCursor() const {
	Cell* cell = start->link;
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
