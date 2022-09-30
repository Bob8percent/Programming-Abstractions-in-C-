#include "TicTacToe.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Library/random.h"

const int MAX_DEPTH = 2;
const int WINNING_POSITION = 1000;
const int LOSING_POSITION = -WINNING_POSITION;
const char MARK[2] = { 'O', 'X' };


Player_t opponent(const Player_t& player)
{
	return (player == HUMAN) ? COMPUTER : HUMAN;
}

TicTacToe::TicTacToe()
{
	mWhoseTurn = COMPUTER;

	for (int i = 0; i < 9; ++i)
		mGrids[i] = ' ';
}

TicTacToe::TicTacToe(Player_t player)
{
	mWhoseTurn = player;

	for (int i = 0; i < 9; ++i)
		mGrids[i] = ' ';
}

void TicTacToe::initGame()
{
	std::cout << "三目並べを始めます" << std::endl;
	if (mWhoseTurn == HUMAN)std::cout << "先手はあなたです" << std::endl;
	else std::cout << "先手は私です" << std::endl;
}

void TicTacToe::play()
{
	initGame();

	while (!isGameEnd())
	{
		if (getCurrentPlayer() == HUMAN)
		{
			displayGame();
			makeMove(getUserMove());
		}
		else if (mWhoseTurn == COMPUTER)
		{
			Move move = getComputerMove();
			displayMove(move);
			makeMove(move);
		};

		switchTurn();
	}

	announceResult();
}

void TicTacToe::switchTurn()
{
	mWhoseTurn = opponent(mWhoseTurn);
}

Player_t TicTacToe::getCurrentPlayer() const
{
	return mWhoseTurn;
}

void TicTacToe::displayGame() const
{
	std::cout << "[あなた：O, 私：X]" << std::endl;
	for (int i = 0; i < 3; ++i)
	{
		std::cout << " " << mGrids[3 * i] << " | " << mGrids[3 * i + 1] << " | " << mGrids[3 * i + 2] << std::endl;

		if (i < 2)
			std::cout << "---+---+---" << std::endl;
	}
	std::cout << std::endl;
}

Move TicTacToe::findBetterMove()
{
	int rating;
	return findBetterMove(0, rating);
}

Move TicTacToe::findBetterMove(int depth, int& rating)
{
	Vector<Move> moveList;
	generateMoveList(moveList);
	Move bestMove;
	if (moveList.isEmpty())
	{
		std::cerr << "ERROR : Move TicTacToe::findBetterMove(int depth, int& rating) : "
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
			bestMove = moveList[i];
			minRating = moveRating;
		}
		mWhoseTurn = (depth % 2 == 0) ? COMPUTER : HUMAN;
		retractMove(moveList[i]);
	}
	rating = -minRating;
	return bestMove;
}

int TicTacToe::evaluatePosition(int depth)
{
	//	さらに深く探索するか、やめて評価するか

	if (isGameEnd() || depth >= MAX_DEPTH)
	{
		return evaluateStaticPosition();
	}

	int rating;
	findBetterMove(depth, rating);
	return rating;
}

int TicTacToe::evaluateStaticPosition()
{
	//	TODO:強いAIを作る方法は色々でてきたので機会があれば実装するかも
	if (isEqualLines())
	{
		return LOSING_POSITION;
	}

	return 0;
}

Move TicTacToe::getUserMove()
{
	while (1)
	{
		std::cout << "どの位置に置きますか？ : ";
		std::string str;
		std::getline(std::cin, str);
		std::istringstream iss(str);
		int value;
		iss >> value >> std::skipws;
		if (!iss.fail() && iss.eof() && isValid(value))
		{
			Move move;
			move.pos = value;
			return move;
		}
		iss.clear();
		std::cout << "不適な入力です" << std::endl;
	}
}

bool TicTacToe::isValid(int pos)
{
	return (0 <= pos && pos < 9) && mGrids[pos] == ' ';
}

Move TicTacToe::getComputerMove()
{
	return findBetterMove();
}

void TicTacToe::makeMove(const Move& move)
{
	mGrids[move.pos] = MARK[mWhoseTurn];
}

void TicTacToe::retractMove(const Move& move)
{
	mGrids[move.pos] = ' ';
}

void TicTacToe::displayMove(const Move& move)
{
	std::cout << "位置" << move.pos << "に置きます" << std::endl;
}

void TicTacToe::generateMoveList(Vector<Move>& moveList)
{
	for (int i = 0; i < 9; ++i)
	{
		if (mGrids[i] == ' ')
		{
			Move move;
			move.pos = i;
			moveList += move;
		}
	}
}

bool TicTacToe::isGameEnd()
{
	if (isEqualLines())return true;

	return isAllMarked();
}

bool TicTacToe::isAllMarked()
{
	//	すべてのグリッドが埋まっているとき
	for (int i = 0; i < 9; ++i)
	{
		if (mGrids[i] == ' ')return false;
	}
	return true;
}

bool TicTacToe::isEqualLines()
{
	//	横
	for (int i = 0; i < 3; ++i)
	{
		int idx = i * 3;
		if (mGrids[idx] != ' ' && mGrids[idx] == mGrids[idx + 1] && mGrids[idx + 1] == mGrids[idx + 2])return true;
	}

	//	縦
	for (int i = 0; i < 3; ++i)
	{
		if (mGrids[i] != ' ' && mGrids[i] == mGrids[i + 3] && mGrids[i + 3] == mGrids[i + 6])return true;
	}

	//	斜め
	if (mGrids[0] != ' ' && mGrids[0] == mGrids[4] && mGrids[4] == mGrids[8])return true;
	if (mGrids[2] != ' ' && mGrids[2] == mGrids[4] && mGrids[4] == mGrids[6])return true;

	return false;
}

void TicTacToe::announceResult()
{
	displayGame();

	Player_t previousPlayer = opponent(mWhoseTurn);

	if (isEqualLines())
	{
		if (previousPlayer == HUMAN)
			std::cout << "あなたの勝ちです" << std::endl;
		else
			std::cout << "私の勝ちです" << std::endl;
	}
	else if(isAllMarked())
		std::cout << "引き分けです" << std::endl;
}

