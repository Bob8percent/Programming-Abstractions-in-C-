#include "Nim.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Library/random.h"

const int MAX_DEPTH = 4;
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
		displayGame();

		if (getCurrentPlayer() == HUMAN)
		{
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
	std::cout << "現在" << mNCoin << "枚です" << std::endl;
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
		makeMove(moveList[i]);
		int moveRating = evaluatePosition(depth + 1);
		if (moveRating < minRating)
		{
			bestMove = moveList[i];
			minRating = moveRating;
		}
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
	//	(mNCoin%4==1)でCOM(/HUMAN)の番に回ってきたらHUMAN(/COM)は絶対負ける
	//	negamax法における静的評価はleafがCOMのときは評価*(-1)を返し、HUMANのときは評価を返せばいい(今回もそうなっている)
	//	なぜなら、leafがCOMのときは評価が最大となる選択肢を、HUMANのときは評価が最小となる選択肢を選びたいが、
	//	findBetterMoveではこのうちleafがHUMANのときのみしか考慮されておらず、COMのときにも対応できるように静的評価を工夫しないといけない
	return (mNCoin % 4 == 1) ? LOSING_POSITION : WINNING_POSITION;
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
}

void SimpleNim::retractMove(const Move& move)
{
	mNCoin += move.nTaken;
}

void SimpleNim::displayMove(const Move& move)
{
	std::cout << move.nTaken << "枚とります" << std::endl;
}

void SimpleNim::generateMoveList(Vector<Move>& moveList)
{
	int nCoin = (3 >= mNCoin) ? (mNCoin - 1) : 3;
	for (int i = 1; i <= nCoin; ++i)
	{
		Move move;
		move.nTaken = i;
		moveList += move;
	}
}

bool SimpleNim::isValid(int nGetCoin)
{
	if (nGetCoin < 1 || 3 < nGetCoin)return false;
	if (nGetCoin > mNCoin)return false;

	return true;
}

bool SimpleNim::isGameEnd()
{
	return mNCoin <= 1;
}

void SimpleNim::announceResult()
{
	Player_t previousTurn = opponent(mWhoseTurn);
	if (mNCoin == 0)
	{
		std::cout << "あなたは最後のコインをとってしまいました" << std::endl
			<< "あなたの負けです" << std::endl;
	}
	else if (mNCoin == 1)
	{
		if (previousTurn == HUMAN)
			std::cout << "あなたの勝ちです" << std::endl;
		else
			std::cout << "私の勝ちです" << std::endl;
	}
}

