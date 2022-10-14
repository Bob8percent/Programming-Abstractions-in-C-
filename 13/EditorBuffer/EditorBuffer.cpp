#include "EditorBuffer.h"

EditorBuffer::EditorBuffer() {

}

EditorBuffer::~EditorBuffer() {

}

void EditorBuffer::moveCursorForward() {

}
void EditorBuffer::moveCursorBackward() {

}

void EditorBuffer::moveCursorToStart() {
	cursorPos = 0;
}
void EditorBuffer::moveCursorToEnd() {

}

void EditorBuffer::insertCharacter(char ch) {

}

void EditorBuffer::deleteCharacter() {

}

std::string EditorBuffer::getText() const {

}

std::string EditorBuffer::toString() const {

}

int EditorBuffer::getCursor() const {
	return cursorPos;
}

