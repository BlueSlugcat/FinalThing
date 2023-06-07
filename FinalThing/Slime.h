#pragma once
#include "Creature.h"
class Slime : public Creature
{
protected:

public:
	Slime();
	Slime(int x, int y);
	~Slime();
	friend class Game;

};

