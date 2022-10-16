#pragma once
#include <string>
#include "CharStack.h"

//	エディターのバッファ(文字列、カーソル情報)の作成、操作を抽象化する
class EditorBuffer
{
public:
	EditorBuffer();
	~EditorBuffer();

	void moveCursorForward();
	void moveCursorBackward();

	void moveCursorToStart();
	void moveCursorToEnd();

	void insertCharacter(char ch);	//	カーソルの直後に1文字を追加 + カーソル移動
	void deleteCharacter();			//	カーソルの直後の1文字を消す

	std::string getText() const;
	int getCursor() const;	//	カーソル位置

private:
	//	データ構造
	CharStack before, after;

	EditorBuffer(const EditorBuffer& src) {}
	void operator=(const EditorBuffer& src) {}
};
