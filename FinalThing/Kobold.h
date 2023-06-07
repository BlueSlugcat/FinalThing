#pragma once
#include "Creature.h"
class Kobold : public Creature
{
protected:
	bool in_pack;
	vector<int>leader_pos;
	bool alpha;
public:
	Kobold();
	Kobold(int x, int y);
	Kobold(size_t isalpha, int x, int y);
	~Kobold();
	bool packcheck();
	friend class Game;
};

