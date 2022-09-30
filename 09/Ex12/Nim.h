#pragma once
#include "Library/vector.h"

enum Player_t { HUMAN, COMPUTER };

Player_t opponent(const Player_t& player);

struct Move
{
	int nTaken;
};

class SimpleNim
{
public:
	SimpleNim();
	SimpleNim(int nCoin, Player_t player);

	void set(int nCoin, Player_t player);
	void play();	//	次のターンの処理

	bool isGameEnd();

private:
	int mNCoin;
	Player_t mWhoseTurn;

	int getCoin();

	//	HUMANが取ろうとしているコイン数が妥当か
	bool isValid(int nGetCoin);

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

