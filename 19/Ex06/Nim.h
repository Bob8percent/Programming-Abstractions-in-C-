#pragma once
#include "TwoPlayerGame.h"
#include "Library/vector.h"

struct Move
{
	int row;
	int nTaken;
};

/*
* Chapter19, Ex06
* TwoPlayerGame(AIのミニマックスアルゴリズム処理を担う)を継承して実装する
*/
class SimpleNim :public TwoPlayerGame<Move>
{
public:
	SimpleNim(){}
	SimpleNim(const Vector<int>& nCoins, int maxGetCoins, Player_t player);

	void play();

	virtual bool isGameEnd();

private:
	int mNRow;
	Vector<int> mNCoins;
	int mMaxMove;

	void getCoins(Move& move);

	bool isValidRow(int row);
	bool isValidCoins(int row, int nGetCoins);

	virtual Move getUserMove();
	virtual void makeMove(const Move& move);
	virtual void retractMove(const Move& move);
	virtual void displayMove(const Move& move);
	virtual void displayGame() const;
	virtual int evaluateStaticPosition();
	virtual void generateMoveList(Vector<Move>& moveList);
};

