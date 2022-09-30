#pragma once
#include "Library/vector.h"

enum Player_t { HUMAN, COMPUTER };

Player_t opponent(const Player_t& player);

struct Move
{
	int pos;
};

/*
* Chapter9, Ex.15
* 三目並べを作る
*/
class TicTacToe
{
public:
	TicTacToe();
	TicTacToe(Player_t player);

	void play();

	bool isGameEnd();

private:
	char mGrids[9];
	Player_t mWhoseTurn;

	bool isValid(int pos);
	bool isAllMarked();
	bool isEqualLines();

	//	Move処理(ターン制ゲームに共通した処理)
	//	本来であれば以下の処理をベースクラスとして別に作ってNimクラスがこれを継承する形となるだろう(たぶん)が、
	//	練習のためこれらをNim.hに記述している
	void initGame();
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



