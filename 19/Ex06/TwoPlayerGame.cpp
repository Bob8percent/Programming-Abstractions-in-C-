#include "TwoPlayerGame.h"

Player_t opponent(const Player_t& player)
{
	return (player == HUMAN) ? COMPUTER : HUMAN;
}
