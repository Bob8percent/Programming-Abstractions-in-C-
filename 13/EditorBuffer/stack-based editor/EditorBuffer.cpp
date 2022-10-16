#include "EditorBuffer.h"

EditorBuffer::EditorBuffer() {
}

EditorBuffer::~EditorBuffer() {
}

void EditorBuffer::moveCursorForward() {
	if (!after.isEmpty())before.push(after.pop());
}
void EditorBuffer::moveCursorBackward() {
	if (!before.isEmpty())after.push(before.pop());
}

void EditorBuffer::moveCursorToStart() {
	while (!before.isEmpty())after.push(before.pop());
}

void EditorBuffer::moveCursorToEnd() {
	while (!after.isEmpty())before.push(after.pop());
}

void EditorBuffer::insertCharacter(char ch) {
	before.push(ch);
}

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
