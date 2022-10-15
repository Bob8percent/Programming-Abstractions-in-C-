#include "EditorBuffer.h"

EditorBuffer::EditorBuffer() {
	capacity = INITIAL_CAPACITY;
	elements = new char[capacity];
	length = 0;
	cursorPos = 0;
}

EditorBuffer::~EditorBuffer() {
	delete[] elements;
}

void EditorBuffer::moveCursorForward() {
	if (0 <= cursorPos && cursorPos < length) {
		++cursorPos;
	}
}
void EditorBuffer::moveCursorBackward() {
	if (0 < cursorPos && cursorPos <= length) {
		--cursorPos;
	}
}

void EditorBuffer::moveCursorToStart() {
	cursorPos = 0;
}
void EditorBuffer::moveCursorToEnd() {
	cursorPos = length;
}

//	curosrPosが大きいほど高速。O(N):平均O(N)、最悪O(N)
void EditorBuffer::insertCharacter(char ch) {
	//	capacityを増やし、割り当てをするのと同時にchのインサートを行えば、計算量は半分になるが、
	//	半分しか減らないのであれば、以下のように記述して可読性を上げるほうが恩恵が大きそう。
	if (length >= capacity) expandCapacity();
	
	//	まずcursorPosの要素を以外を移動
	for (int i = length - 1; i >= cursorPos; --i) {
		elements[i + 1] = elements[i];
	}
	//	cursorPosに要素を当てはめる
	elements[cursorPos] = ch;

	++cursorPos;
	++length;
}

//	cursorPosは大きいほど高速。O(N):平均O(N)、最悪O(N)
void EditorBuffer::deleteCharacter() {
	if (cursorPos >= length)return;
	
	for (int i = cursorPos; i < length - 1; ++i) {
		elements[i] = elements[i + 1];
	}

	--length;
}

std::string EditorBuffer::getText() const {
	return std::string(elements, length);
}

int EditorBuffer::getCursor() const {
	return cursorPos;
}

void EditorBuffer::expandCapacity() {
	capacity *= 2;
	char* oldElements = elements;
	elements = new char[capacity];
	for (int i = 0; i < length; ++i) {
		elements[i] = oldElements[i];
	}
	delete[] oldElements;
}

