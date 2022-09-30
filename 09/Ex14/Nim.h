#pragma once
#include "Library/vector.h"

enum Player_t { HUMAN, COMPUTER };

Player_t opponent(const Player_t& player);

struct Move
{
	int row;
	int nTaken;
};

/*
* Chapter9, Ex.14
* 任意の数の山からコインを1~n枚取り合い、最後のコインをとった人が負け
*/
class SimpleNim
{
public:
	SimpleNim();
	SimpleNim(const Vector<int>& nCoins, int maxGetCoins, Player_t player);

	void play();

	bool isGameEnd();

private:
	int mNRow;
	Vector<int> mNCoins;
	Player_t mWhoseTurn;
	int mMaxMove;

	void getCoins(Move& move);

	bool isValidRow(int row);
	bool isValidCoins(int row, int nGetCoins);

	//	Move処理(ターン制ゲームに共通した処理)
	//	本来であれば以下の処理をベースクラスとして別に作ってNimクラスがこれを継承する形となるだろう(たぶん)が、
	//	練習のためこれらをNim.hに記述している
	Move getUserMove();
	Move getComputerMove();
	void makeMove(const Move& move);
	void retractMove(const Move& move);
	void displayMove(const Move& move);
	void displayGame() const;
	void switchTurn();
	Player_t getCurrentPlayer() const;
	Move findBetterMove();
	Move findBetterMove(int depth, int& rating);
	int evaluatePosition(int depth);
	int evaluateStaticPosition();
	void generateMoveList(Vector<Move>& moveList);
	void announceResult();
};

