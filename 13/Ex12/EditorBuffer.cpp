#include "EditorBuffer.h"

EditorBuffer::EditorBuffer() {
	Cell* dummyCell = new Cell;
	dummyCell->ch = -1;
	dummyCell->before = nullptr;	//	最後の文字を指す
	dummyCell->after = nullptr;		//	次の文字を指す
	cursor = dummyCell;
	start = dummyCell;
}

EditorBuffer::~EditorBuffer() {
	Cell* cell = start;
	while (cell) {
		Cell* currentCell = cell;
		cell = cell->after;
		delete currentCell;
	}
}

//	O(1)
void EditorBuffer::moveCursorForward() {
	if (cursor->after) {
		cursor = cursor->after;
	}
}

//	O(1)
void EditorBuffer::moveCursorBackward() {
	if (cursor != start) {
		cursor = cursor->before;
	}
}

//	O(1)
void EditorBuffer::moveCursorToStart() {
	cursor = start;
}

//	O(1)
void EditorBuffer::moveCursorToEnd() {
	cursor = start->before;
}

//	O(1)
void EditorBuffer::insertCharacter(char ch) {
	Cell* newCell = new Cell;
	newCell->ch = ch;
	newCell->after = cursor->after;
	if (cursor->after)cursor->after->before = newCell;
	else start->before = newCell;
	cursor->after = newCell;
	newCell->before = cursor;
	cursor = newCell;	//	cursorの移動
}

//	O(1)
void EditorBuffer::deleteCharacter() {
	//	cursor->afterを消す
	if (cursor->after) {
		Cell* dCell = cursor->after;
		cursor->after = dCell->after;
		if (dCell->after)dCell->after->before = cursor;
		delete dCell;
	}
}

//	O(N)
std::string EditorBuffer::getText() const {
	std::string str;
	Cell* cell = start->after;	//	dammyCellの後ろから開始
	while (cell) {
		str += cell->ch;
		cell = cell->after;
	}
	return str;
}

//	O(N)
int EditorBuffer::getCursor() const {
	Cell* cell = start->after;
	int cursorPos = 0;
	while (cell) {
		if (cell == cursor->after) {
			return cursorPos;
			break;
		}
		cell = cell->after;
		++cursorPos;
	}
}
