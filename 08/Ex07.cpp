#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "Card.h"
#include "TokenScanner.h"
#include "Library/queue.h"
#include "Library/map.h"
#include "Library/set.h"

int countFifteens(const Vector<Card>& cards);
int countSubsetSumWays(const Vector<Card>& cards, int target);

int main()
{
	Vector<Card> cards;
	cards += Card(1, DIAMONDS), Card(5, CLUBS), Card(10, SPADES), Card(4, HEARTS), Card(9, CLUBS);
	//cards += Card(5, DIAMONDS), Card(5, CLUBS), Card(5, SPADES), Card(5, HEARTS), Card(11, CLUBS);
	std::cout << countFifteens(cards) << std::endl;
}

int countFifteens(const Vector<Card>& cards)
{
	return countSubsetSumWays(cards, 15);
}

int countSubsetSumWays(const Vector<Card>& cards, int target)
{
	int sum = 0;
	for (int i = 0; i < cards.size(); ++i)sum += cards[i].getRank();
	if (sum == target)return 1;
	else if (cards.isEmpty())return 0;

	Vector<Card> temp = cards;
	Card c = temp[cards.size() - 1];
	temp.remove(cards.size() - 1);
	return countSubsetSumWays(temp, target) + countSubsetSumWays(temp, target - c.getRank());
}

