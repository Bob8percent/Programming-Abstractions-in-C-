#include "EditorBuffer.h"

EditorBuffer::EditorBuffer() {
}

EditorBuffer::~EditorBuffer() {
}

//	O(1)
void EditorBuffer::moveCursorForward() {
	if (!twoStacks.isEmpty(AFTER))twoStacks.push(twoStacks.pop(AFTER), BEFORE);
}

//	O(1)
void EditorBuffer::moveCursorBackward() {
	if (!twoStacks.isEmpty(BEFORE))twoStacks.push(twoStacks.pop(BEFORE), AFTER);
}

//	O(N)
//	以下2つの操作は、CharStack使用時と異なりsizeは変化しない
void EditorBuffer::moveCursorToStart() {
	while (!twoStacks.isEmpty(BEFORE))twoStacks.push(twoStacks.pop(BEFORE), AFTER);
}
//	O(N)
void EditorBuffer::moveCursorToEnd() {
	while (!twoStacks.isEmpty(AFTER))twoStacks.push(twoStacks.pop(AFTER), BEFORE);
}

//	O(1)
void EditorBuffer::insertCharacter(char ch) {
	twoStacks.push(ch, BEFORE);
}

//	O(1)
void EditorBuffer::deleteCharacter() {
	if (twoStacks.isEmpty(BEFORE) && twoStacks.isEmpty(AFTER)) return;
	if (!twoStacks.isEmpty(AFTER)) {
		twoStacks.pop(AFTER);
		return;
	}
}

//	O(N)
std::string EditorBuffer::getText() const {
	InsideTwoStacks s = twoStacks;

	std::string str;
	while (!s.isEmpty(BEFORE))str = s.pop(BEFORE) + str;
	while (!s.isEmpty(AFTER))str += s.pop(AFTER);

	return str;
}

int EditorBuffer::getCursor() const {
	return twoStacks.size(BEFORE);
}
