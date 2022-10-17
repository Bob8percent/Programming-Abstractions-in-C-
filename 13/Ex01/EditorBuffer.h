#pragma once
#include <string>
#include "Library/vector.h"

struct Cell {
	char ch;
	Cell* link;
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
	//	データ構造:連結リスト
	//	考えたアイデア：各セルに前方のCellへのポインタ変数を作れば後方移動もO(1)になるけど依存関係が増えて扱いずらくなりメモリ消費がやばいというデメリットがある？？
	//	->教科書p606に考えたことがそのまま書かれていた。Doubly Linked Listというらしい。演習問題で後程実装する予定。

	Cell* cursor;	//	カーソル位置(地点1を指しているとき、カーソルは1と2の間に位置する)
	Cell* start;	//	スタート地点(地点0を指している)
	
	EditorBuffer(const EditorBuffer& src) {}
	void operator=(const EditorBuffer& src) {}

	void deleteBuffer();
	//Vector<bool> debugArray;
};
