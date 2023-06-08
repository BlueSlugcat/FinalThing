#pragma once
#include "Creature.h"
class Golem : public Creature
{
protected:
	vector<vector<int>> targets;
	bool hunting;
public:
	Golem();
	Golem(int x, int y);
	~Golem();
	void Detect(Creature* entity);
	void SelectTarget();
	void MoveChoose();
	friend class Game;
};

