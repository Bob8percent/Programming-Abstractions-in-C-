#include "EditorBuffer.h"

EditorBuffer::EditorBuffer() {
}

EditorBuffer::~EditorBuffer() {
}

//	O(1)
void EditorBuffer::moveCursorForward() {
	if (!after.isEmpty())before.push(after.pop());
}

//	O(1)
void EditorBuffer::moveCursorBackward() {
	if (!before.isEmpty())after.push(before.pop());
}

//	O(N)
//	課題：文字列の最初(後)から最後(初)まで移動したとき、文字数の2倍のメモリが使用される可能性がある
void EditorBuffer::moveCursorToStart() {
	while (!before.isEmpty())after.push(before.pop());
}
//	O(N)
void EditorBuffer::moveCursorToEnd() {
	while (!after.isEmpty())before.push(after.pop());
}

//	O(1)
void EditorBuffer::insertCharacter(char ch) {
	before.push(ch);
}

//	O(1)
void EditorBuffer::deleteCharacter() {
	if (before.isEmpty() && after.isEmpty()) return;
	if (!after.isEmpty()) {
		after.pop();
		return;
	}
}

//	O(N)
std::string EditorBuffer::getText() const {
	CharStack b = before;
	CharStack a = after;

	std::string str;
	while (!b.isEmpty())str = b.pop() + str;
	while (!a.isEmpty())str += a.pop();

	return str;
}

int EditorBuffer::getCursor() const {
	return before.size();
}
