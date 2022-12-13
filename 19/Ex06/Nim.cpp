#include "Nim.h"
#include <iostream>
#include <string>
#include <sstream>
#include "Library/random.h"

SimpleNim::SimpleNim(const Vector<int>& nCoins, int maxGetCoins, Player_t player) :TwoPlayerGame(player)
{
	if (nCoins.isEmpty())
	{
		std::cerr << "ERROR : SimpleNim::SimpleNim(int nCoin, Player_t player)"
			<< " : nCoinsが空です" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	if (!(player == HUMAN || player == COMPUTER))
	{
		std::cerr << "ERROR : SimpleNim::SimpleNim(int nCoin, Player_t player)"
			<< " : playerにはHUMANまたはCOMPUTERを指定してください" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	int minRow = INT_MAX;
	for (int i = 0; i < nCoins.size(); ++i)
	{
		if (minRow > nCoins[i])minRow = nCoins[i];
	}
	if (minRow < maxGetCoins)
	{
		std::cerr << "ERROR : SimpleNim::SimpleNim(int nCoin, Player_t player)"
			<< " : playerにはHUMANまたはCOMPUTERを指定してください" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	mNCoins = nCoins;
	mNRow = nCoins.size();
	mMaxMove = maxGetCoins;
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

void SimpleNim::displayGame() const
{
	std::cout << "--------------------------" << std::endl;
	for (int i = 0; i < mNCoins.size(); ++i)
	{
		std::cout << "残り(第" << i << "行)：" << mNCoins[i] << "枚" << std::endl;
	}
	std::cout << "--------------------------" << std::endl << std::endl;
}

void SimpleNim::getCoins(Move& move)
{
	//	TODO : 本当はioライブラリを作るべき
	int rowTmp, nCoins;
	while (1)
	{
		std::cout << "どの行を選びますか？ : ";
		std::string str;
		std::getline(std::cin, str);
		std::istringstream iss(str);
		iss >> rowTmp >> std::skipws;
		if (!iss.fail() && iss.eof() && isValidRow(rowTmp))
		{
			move.row = rowTmp;
			break;
		}
		iss.clear();
		std::cout << "不適な入力です" << std::endl;
	}
	while (1)
	{
		std::cout << "何枚とりますか？ : ";
		std::string str;
		std::getline(std::cin, str);
		std::istringstream iss(str);
		iss >> nCoins >> std::skipws;
		if (!iss.fail() && iss.eof() && isValidCoins(rowTmp, nCoins))
		{
			move.nTaken = nCoins;
			std::cout << std::endl;
			break;
		}
		iss.clear();
		std::cout << "不適な入力です" << std::endl;
	}
}

int SimpleNim::evaluateStaticPosition()
{
	bool isTest = true;	//	すべての行が0または1のときのみを対象に場合分けする
	int countOnes = 0;	//	コインが1つの行の数
	for (int i = 0; i < mNCoins.size(); ++i)
	{
		if (mNCoins[i] == 1)++countOnes;

		if (!(mNCoins[i] == 1 || mNCoins[i] == 0))isTest = false;
	}
	bool isEven = (countOnes % 2 == 0);


	//	[以下の評価処理の実装手順について]
	//	currentPlayerがHUMANかCOMかで場合分けして
	//	処理内容が同じだったので統合できると判断した。
	if (isTest)
	{
		if (!isEven)return LOSING_POSITION;
		else return WINNING_POSITION;
	}
	else
	{
		return 0;
	}

}

Move SimpleNim::getUserMove()
{
	Move move;
	getCoins(move);
	return move;
}

void SimpleNim::makeMove(const Move& move)
{
	mNCoins[move.row] -= move.nTaken;
}

void SimpleNim::retractMove(const Move& move)
{
	mNCoins[move.row] += move.nTaken;
}

void SimpleNim::displayMove(const Move& move)
{
	std::cout << "第" << move.row << "行のコインを";
	std::cout << move.nTaken << "枚とります" << std::endl << std::endl;
}

void SimpleNim::generateMoveList(Vector<Move>& moveList)
{
	for (int j = 0; j < mNCoins.size(); ++j)
	{
		int nCoins = (mMaxMove > mNCoins[j]) ? mNCoins[j] : mMaxMove;
		for (int i = 1; i <= nCoins; ++i)
		{
			Move move;
			move.row = j;
			move.nTaken = i;
			moveList += move;
		}
	}
}

bool SimpleNim::isValidRow(int row)
{
	if (row < 0 || mNCoins.size() <= row)return false;

	return true;
}

bool SimpleNim::isValidCoins(int row, int nGetCoins)
{
	if (nGetCoins < 1 || mMaxMove < nGetCoins)return false;
	if (nGetCoins > mNCoins[row])return false;

	return true;
}

bool SimpleNim::isGameEnd()
{
	for (int i = 0; i < mNCoins.size(); ++i)
	{
		if (mNCoins[i] > 0)return false;
	}

	return true;
}


