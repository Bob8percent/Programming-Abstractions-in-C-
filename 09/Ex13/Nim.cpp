#include "Nim.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Library/random.h"

const int MAX_DEPTH = 4;
const int MAX_MOVE = 4;
const int WINNING_POSITION = 1000;
const int LOSING_POSITION = -WINNING_POSITION;

Player_t opponent(const Player_t& player)
{
	return (player == HUMAN) ? COMPUTER : HUMAN;
}

SimpleNim::SimpleNim()
{
	mNCoin = 0;
	mWhoseTurn = HUMAN;
	pile += 0, 0;
}

SimpleNim::SimpleNim(int nCoin, Player_t player)
{
	if (nCoin <= 0)
	{
		std::cerr << "ERROR : SimpleNim::SimpleNim(int nCoin, Player_t player)"
			<< " : nCoinが0以下です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	if (!(player == HUMAN || player == COMPUTER))
	{
		std::cerr << "ERROR : SimpleNim::SimpleNim(int nCoin, Player_t player)"
			<< " : playerにはHUMANまたはCOMPUTERを指定してください" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	mNCoin = nCoin;
	mWhoseTurn = player;
	pile += 0, 0;
}

void SimpleNim::set(int nCoin, Player_t player)
{
	if (nCoin <= 0)
	{
		std::cerr << "ERROR : SimpleNim::SimpleNim(int nCoin, Player_t player)"
			<< " : nCoinが0以下です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	if (!(player == HUMAN || player == COMPUTER))
	{
		std::cerr << "ERROR : SimpleNim::SimpleNim(int nCoin, Player_t player)"
			<< " : playerにはHUMANまたはCOMPUTERを指定してください" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	mNCoin = nCoin;
	mWhoseTurn = player;
}

void SimpleNim::play()
{
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

void SimpleNim::switchTurn()
{
	mWhoseTurn = opponent(mWhoseTurn);
}

Player_t SimpleNim::getCurrentPlayer() const
{
	return mWhoseTurn;
}

void SimpleNim::displayGame() const
{
	std::cout << "--------------------------" << std::endl;
	std::cout << "残り　　　：" << mNCoin << "枚" << std::endl;
	std::cout << "あなたの山：" << pile[HUMAN] << "枚" << std::endl;
	std::cout << "私の山　　：" << pile[COMPUTER] << "枚" << std::endl;
	std::cout << "--------------------------" << std::endl;
}

int SimpleNim::getCoin()
{
	while (1)
	{
		std::cout << "何枚とりますか？ : ";
		std::string str;
		std::getline(std::cin, str);
		std::istringstream iss(str);
		int value;
		iss >> value >> std::skipws;
		if (!iss.fail() && iss.eof())
		{
			if (isValid(value)) return value;
		}
		iss.clear();
		std::cout << "不適な入力です" << std::endl;
	}
}

Move SimpleNim::findBetterMove()
{
	int rating;
	return findBetterMove(0, rating);
}

Move SimpleNim::findBetterMove(int depth, int& rating)
{
	Vector<Move> moveList;
	generateMoveList(moveList);
	Move bestMove;
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
			bestMove = moveList[i];
			minRating = moveRating;
		}
		mWhoseTurn = (depth % 2 == 0) ? COMPUTER : HUMAN;
		retractMove(moveList[i]);
	}
	rating = -minRating;
	return bestMove;
}

int SimpleNim::evaluatePosition(int depth)
{
	if (isGameEnd() || depth >= MAX_DEPTH)
	{
		return evaluateStaticPosition();
	}

	int rating;
	findBetterMove(depth, rating);
	return rating;
}

int SimpleNim::evaluateStaticPosition()
{
	bool isEvenH = (pile[HUMAN] % 2 == 0);
	bool isEvenC = (pile[COMPUTER] % 2 == 0);

	//	COMPUTERにとって不利な評価ほど低くなる
	if (mWhoseTurn == HUMAN)
	{
		if (mNCoin == 0)
		{
			if (isEvenC && isEvenH)return LOSING_POSITION;
			if (isEvenC)return WINNING_POSITION;
			if (isEvenH)return LOSING_POSITION;

			//	勝ち負け決まらない
			return 0;
		}
		else if (mNCoin == 1)
		{
			if (!isEvenC)return WINNING_POSITION;
			else if (isEvenH) return LOSING_POSITION;

			//	勝ち負け決まらない
			return 0;
		}
		else
		{
			//	mNCoinが上記以外のときは偶数となれば有利という情報しかわからないので少し評価を下げる
			if (isEvenC)return WINNING_POSITION - 1;
			else return LOSING_POSITION + 1;
		}
	}

	//	COMPUTERにとって不利な評価ほど高くなる(<-negamax法の弊害)
	else
	{
		if (mNCoin == 0)
		{
			if (isEvenC && isEvenH)return LOSING_POSITION;
			if (isEvenC)return LOSING_POSITION;
			if (isEvenH)return WINNING_POSITION;

			//	勝ち負け決まらない
			return 0;
		}
		else if (mNCoin == 1)
		{
			if (!isEvenH)return WINNING_POSITION;
			else if (isEvenC) return LOSING_POSITION;

			//	勝ち負け決まらない
			return 0;
		}
		else
		{
			if (isEvenC)return LOSING_POSITION + 1;
			else return WINNING_POSITION - 1;
		}
	}
}

Move SimpleNim::getUserMove()
{
	int nCoin = getCoin();
	Move move;
	move.nTaken = nCoin;
	return move;
}

Move SimpleNim::getComputerMove()
{
	return findBetterMove();
}

void SimpleNim::makeMove(const Move& move)
{
	mNCoin -= move.nTaken;
	pile[mWhoseTurn] += move.nTaken;
}

void SimpleNim::retractMove(const Move& move)
{
	mNCoin += move.nTaken;
	pile[mWhoseTurn] -= move.nTaken;
}

void SimpleNim::displayMove(const Move& move)
{
	std::cout << move.nTaken << "枚とります" << std::endl;
}

void SimpleNim::generateMoveList(Vector<Move>& moveList)
{
	int nCoin = (MAX_MOVE > mNCoin) ? mNCoin : MAX_MOVE;
	for (int i = 1; i <= nCoin; ++i)
	{
		Move move;
		move.nTaken = i;
		moveList += move;
	}
}

bool SimpleNim::isValid(int nGetCoin)
{
	if (nGetCoin < 1 || MAX_MOVE < nGetCoin)return false;
	if (nGetCoin > mNCoin)return false;

	return true;
}

bool SimpleNim::isGameEnd()
{
	return mNCoin <= 0;
}

void SimpleNim::announceResult()
{
	if (mNCoin != 0)
	{
		std::cout << "残り枚数が負になっているので勝負判定が不可能です" << std::endl;
		return;
	}

	displayGame();

	Player_t previousTurn = opponent(mWhoseTurn);
	bool isEvenH = (pile[HUMAN] % 2 == 0);
	bool isEvenC = (pile[COMPUTER] % 2 == 0);
	if (isEvenH && isEvenC)
	{
		if (previousTurn == HUMAN)
			std::cout << "あなたの勝ちです" << std::endl;
		else
			std::cout << "私の勝ちです" << std::endl;

		return;
	}
	if (isEvenH)
	{
		std::cout << "あなたの勝ちです" << std::endl;
		return;
	}
	if (isEvenC)
	{
		std::cout << "私の勝ちです" << std::endl;
		return;
	}

	//	いずれのプレイヤーの山も奇数
	std::cout << "どちらの山も奇数なので引き分けです" << std::endl;
}

