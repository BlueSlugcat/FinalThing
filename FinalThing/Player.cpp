#include "Player.h"

Player::Player():Creature("Player.txt", 1, 1)
{
	name = "Player";
}

Player::Player(int x, int y) :Creature("Player.txt", x, y)
{
	name = "Player";
}

Player::~Player()
{
	cout << "Player dtor" << endl;
}