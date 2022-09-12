#include "Card.h"
#include <iostream>
#include <sstream>

Suit& operator++(Suit& rhs)
{
	rhs = (Suit)(rhs + 1);
	return rhs;
}

Card::Card(int r, Suit s)
{
	if (!(ACE <= r && r <= KING))
	{
		std::cerr << "ERROR : Card::Card(int r, Suit s) : rは1~13のいずれかでなければいけません" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	if (!(CLUBS <= s && s <= SPADES))
	{
		std::cerr << "ERROR : Card::Card(int r, Suit s) : rは1~13のいずれかでなければいけません" << std::endl;
		std::exit(EXIT_FAILURE);
	}

	rank = r;
	suit = s;
}

int Card::getRank() const
{
	return rank;
}

Suit Card::getSuit() const
{
	return suit;
}

std::ostream& operator<<(std::ostream& os, const Card& rhs)
{
	//	rankを文字列にする
	std::string rStr = "";
	int rank = rhs.getRank();
	switch (rank)
	{
	case 1:
		rStr = 'A';
		break;
	case 11:
		rStr = 'J';
		break;
	case 12:
		rStr = 'Q';
		break;
	case 13:
		rStr = 'K';
		break;
	default:
		std::ostringstream oss;
		os << rank;
		rStr = oss.str();
		break;
	}

	//	suitを文字列にする
	char sChar;
	switch (rhs.getSuit())
	{
	case CLUBS: 
		sChar = 'C';
		break;
	case DIAMONDS:
		sChar = 'D';
		break;
	case HEARTS:
		sChar = 'H';
		break;
	case SPADES:
		sChar = 'S';
		break;
	default:
		break;
	}

	return os << rStr << sChar;
}
