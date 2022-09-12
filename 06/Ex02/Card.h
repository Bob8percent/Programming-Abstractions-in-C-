#pragma once
#include <ostream>

enum Suit { CLUBS, DIAMONDS, HEARTS, SPADES};

Suit& operator++(Suit& rhs);

const int ACE = 1;
const int JACK = 11;
const int QUEEN = 12;
const int KING = 13;

class Card
{
public:
	Card(int r, Suit s);

	int getRank() const;
	Suit getSuit() const;

private:
	int rank;
	Suit suit;
};

std::ostream& operator<<(std::ostream& os, const Card& rhs);

