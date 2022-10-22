#pragma once
#include <string>

struct Cell {
	char ch;
	Cell* before;
	Cell* after;
};

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
	//	データ構造:双方向リスト(線形リストは双方向リストと片方向リストのことらしい)
	//	教科書p606ではダミーセルのbeforeが文字列の末尾を、文字列の末尾のafterがダミーセルを指しているが、
	//	後者に関して有用性を感じないので実装しない。

	Cell* cursor;	//	カーソル位置(地点1を指しているとき、カーソルは1と2の間に位置する)
	Cell* start;	//	スタート地点(地点0を指している)

	EditorBuffer(const EditorBuffer& src) {}
	void operator=(const EditorBuffer& src) {}
};
