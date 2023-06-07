#pragma once
#include "Creature.h"
class Golem : public Creature
{
protected:

public:
	Golem();
	Golem(int x, int y);
	~Golem();
	friend class Game;
};

