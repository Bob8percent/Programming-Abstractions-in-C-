#pragma once
#include <string>
#include "InsideTwoStacks.h"

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

	//	以下は前後の単語に対する処理(単語は英数字、区切りは英数字以外の文字とする)。よく使いそうだからEditorBufferクラスに含めた
	void moveCursorForwardSkip();
	void moveCursorBackwardSkip();
	void deleteWord();

	std::string getText() const;
	int getCursor() const;	//	カーソル位置

	void copy(int count);
	void paste();

	bool search(const std::string& word);

private:
	//	データ構造
	//	従来のデータ構造の課題：文字列の最初(後)から最後(初)まで移動したとき、文字数の2倍のメモリが使用される可能性がある
	//	-> InsideTwoStacksクラスの使用(内部実装では一つの配列だが2つのスタック構造を抽象化しており、2つのスタックが一つの配列を共有している。)
	InsideTwoStacks twoStacks;

	EditorBuffer(const EditorBuffer& src) {}
	void operator=(const EditorBuffer& src) {}

	std::string copyBuffer;
};
