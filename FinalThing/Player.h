#pragma once
#include "Creature.h"
class Player : public Creature
{
protected:

public: 
	Player();
	Player(int x, int y);
	~Player();
	void detect(); //used here in order to negate its effect for the player
};

