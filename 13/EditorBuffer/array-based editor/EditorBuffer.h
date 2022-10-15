#pragma once
#include <string>

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
	//	データ構造:文字列配列
	char* elements;
	
	//	editorに表示できる文字数はintで十分?
	static const int INITIAL_CAPACITY = 10;
	int capacity;
	int length;
	int cursorPos;

	void expandCapacity();

	EditorBuffer(const EditorBuffer& src){}
	void operator=(const EditorBuffer& src) const{}
};

