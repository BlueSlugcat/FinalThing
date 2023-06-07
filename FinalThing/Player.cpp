#include "Player.h"

Player::Player():Creature("Player.txt", 1, 1)
{}

Player::Player(int x, int y) :Creature("Player.txt", x, y)
{}

Player::~Player()
{}