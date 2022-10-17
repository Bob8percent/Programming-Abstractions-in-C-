#include "EditorBuffer.h"

EditorBuffer::EditorBuffer() {
	//	地点0の前にダミーセルを作る。
	//	cursorが指しているCellの後ろに挿入、削除する。
	//	これを作らないと削除がO(1)にできない。
	Cell* dummyCell = new Cell;
	dummyCell->ch = -1;
	dummyCell->link = nullptr;
	cursor = dummyCell;
	start = dummyCell;
}

EditorBuffer::~EditorBuffer() {
	deleteBuffer();
}

//	O(1)
void EditorBuffer::moveCursorForward() {
	if (cursor->link) {
		cursor = cursor->link;
	}
}

//	O(N)
void EditorBuffer::moveCursorBackward() {
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

//	O(1)
void EditorBuffer::moveCursorToStart() {
	cursor = start;
}

//	O(N)
void EditorBuffer::moveCursorToEnd() {
	while (cursor->link) {
		cursor = cursor->link;
	}
}

//	O(1)
void EditorBuffer::insertCharacter(char ch) {
	Cell* newCell = new Cell;
	newCell->ch = ch;
	newCell->link = cursor->link;
	cursor->link = newCell;
	cursor = newCell;	//	cursorの移動
}

//	O(1)
void EditorBuffer::deleteCharacter() {
	//	cursor->linkを消す
	if (cursor->link) {
		Cell* dCell = cursor->link;
		cursor->link = dCell->link;
		delete dCell;
	}
}

//	O(N)
std::string EditorBuffer::getText() const {
	std::string str;
	Cell* cell = start->link;	//	dammyCellの後ろから開始
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

void EditorBuffer::deleteBuffer() {
	Cell* cell = start;
	while (cell) {
		Cell* currentCell = cell;
		cell = cell->link;
		delete currentCell;
		currentCell = nullptr;
		//debugArray += true;
	}
}
