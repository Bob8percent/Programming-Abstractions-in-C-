#include "EditorBuffer.h"
#include <iostream>

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

//	次の単語の終わりまでカーソル移動
void EditorBuffer::moveCursorForwardSkip() {
	//	今の単語の終わりまで移動
	while (!twoStacks.isEmpty(AFTER) && isalnum(twoStacks.peek(AFTER)))moveCursorForward();
	//	区切り文字(列)の終わりまで移動
	while (!twoStacks.isEmpty(AFTER) && !isalnum(twoStacks.peek(AFTER)))moveCursorForward();
	//	次の単語の終わりまで移動
	while (!twoStacks.isEmpty(AFTER) && isalnum(twoStacks.peek(AFTER)))moveCursorForward();
}

//	前の単語の先頭までカーソル移動
void EditorBuffer::moveCursorBackwardSkip() {
	//	今の単語の先頭まで移動
	while (!twoStacks.isEmpty(BEFORE) && isalnum(twoStacks.peek(BEFORE)))moveCursorBackward();
	//	区切り文字(列)の前まで移動
	while (!twoStacks.isEmpty(BEFORE) && !isalnum(twoStacks.peek(BEFORE)))moveCursorBackward();
	//	前の単語の先頭まで移動
	while (!twoStacks.isEmpty(BEFORE) && isalnum(twoStacks.peek(BEFORE))) moveCursorBackward();
}

//	次の単語の終わりまで削除
void EditorBuffer::deleteWord() {
	//	今の単語の終わりまで削除
	while (!twoStacks.isEmpty(AFTER) && isalnum(twoStacks.peek(AFTER)))deleteCharacter();
	//	区切り文字(列)の終わりまで削除
	while (!twoStacks.isEmpty(AFTER) && !isalnum(twoStacks.peek(AFTER)))deleteCharacter();
	//	次の単語の終わりまで削除
	while (!twoStacks.isEmpty(BEFORE) && isalnum(twoStacks.peek(BEFORE))
		&& !twoStacks.isEmpty(BEFORE) && isalnum(twoStacks.peek(AFTER)))deleteCharacter();
}

int EditorBuffer::getCursor() const {
	return twoStacks.size(BEFORE);
}

void EditorBuffer::copy(int count) {
	copyBuffer.clear();
	std::size_t i = 0;
	std::size_t size = twoStacks.size(AFTER);
	for (; i < count && i < size; ++i) {
		copyBuffer += twoStacks.peek(AFTER);
		moveCursorForward();
	}
	for (std::size_t j = 0; j < i; ++j) moveCursorBackward();
}

void EditorBuffer::paste() {
	for (std::size_t i = 0; i < copyBuffer.length(); ++i) {
		insertCharacter(copyBuffer[i]);
	}
}

