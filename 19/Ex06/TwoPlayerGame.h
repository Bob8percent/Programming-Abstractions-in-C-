#pragma once
#include "Library/vector.h"

enum Player_t { HUMAN, COMPUTER };

Player_t opponent(const Player_t& player);

template <typename MoveType>
class TwoPlayerGame {
public:
	virtual bool isGameEnd() = 0;

protected:
	TwoPlayerGame();	//	ユーザー側にインスタンスを作ることを制限し、スライスを避けるため
	TwoPlayerGame(Player_t player);

	//	ゲームの種類によって処理が変わる関数
	virtual MoveType getUserMove() = 0;
	virtual void makeMove(const MoveType& move) = 0;
	virtual void retractMove(const MoveType& move) = 0;
	virtual void displayMove(const MoveType& move) = 0;
	virtual void displayGame() const = 0;
	virtual int evaluateStaticPosition() = 0;
	virtual void generateMoveList(Vector<MoveType>& moveList) = 0;	//	次の手の候補リストを取得

	//	高確率で共通化できる処理
	virtual MoveType getComputerMove();
	virtual void switchTurn();
	virtual Player_t getCurrentPlayer() const;
	virtual MoveType findBetterMove();
	virtual MoveType findBetterMove(int depth, int& rating);
	virtual int evaluatePosition(int depth);
	virtual void announceResult();

	Player_t mWhoseTurn;
	int maxDepth;
	const static int WINNING_POSITION = 1000;
	const static int LOSING_POSITION = -WINNING_POSITION;
};

template <typename MoveType>
TwoPlayerGame<MoveType>::TwoPlayerGame() {
	mWhoseTurn = HUMAN;
	maxDepth = 4;
}

template <typename MoveType>
TwoPlayerGame<MoveType>::TwoPlayerGame(Player_t player) {
	mWhoseTurn = player;
	maxDepth = 4;
}

template <typename MoveType>
MoveType TwoPlayerGame<MoveType>::getComputerMove() {
	return findBetterMove();
}

template <typename MoveType>
void TwoPlayerGame<MoveType>::displayMove(const MoveType& move);

template <typename MoveType>
void TwoPlayerGame<MoveType>::displayGame() const;

template <typename MoveType>
void TwoPlayerGame<MoveType>::switchTurn() {
	mWhoseTurn = opponent(mWhoseTurn);
}

template <typename MoveType>
Player_t TwoPlayerGame<MoveType>::getCurrentPlayer() const {
	return mWhoseTurn;
}

template <typename MoveType>
MoveType TwoPlayerGame<MoveType>::findBetterMove() {
	int rating;
	return findBetterMove(0, rating);
}

template <typename MoveType>
MoveType TwoPlayerGame<MoveType>::findBetterMove(int depth, int& rating) {
	Vector<MoveType> moveList;
	generateMoveList(moveList);
	MoveType betterMove;
	if (moveList.isEmpty())
	{
		std::cerr << "ERROR : Move SimpleNim::findBetterMove(int depth, int& rating) : "
			<< "moveListが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	int minRating = WINNING_POSITION + 1;
	for (int i = 0, size = moveList.size(); i < size; ++i)
	{
		mWhoseTurn = (depth % 2 == 0) ? COMPUTER : HUMAN;
		makeMove(moveList[i]);
		int moveRating = evaluatePosition(depth + 1);
		if (moveRating < minRating)
		{
			betterMove = moveList[i];
			minRating = moveRating;
		}
		mWhoseTurn = (depth % 2 == 0) ? COMPUTER : HUMAN;
		retractMove(moveList[i]);
	}
	rating = -minRating;
	return betterMove;
}

template <typename MoveType>
int TwoPlayerGame<MoveType>::evaluatePosition(int depth) {
	if (isGameEnd() || depth >= maxDepth)
	{
		return evaluateStaticPosition();
	}

	int rating;
	findBetterMove(depth, rating);
	return rating;
}

template <typename MoveType>
void TwoPlayerGame<MoveType>::announceResult() {
	displayGame();

	if (mWhoseTurn == HUMAN)
		std::cout << "あなたの勝ちです" << std::endl;
	else
		std::cout << "私の勝ちです" << std::endl;
}
