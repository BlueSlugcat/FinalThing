#ifndef KOBOLD_H
#define KOBOLD_H
#include "Creature.h"
#include <cmath>
class Kobold : public Creature
{
protected:
	bool in_pack;
	vector<int*>leader_pos;
	bool alpha;
public:
	Kobold();
	Kobold(int x, int y);
	Kobold(size_t isalpha, int x, int y);
	~Kobold();
	void SelectLeader(vector<vector<int*>> alphaPos);
	void Detect();
	void MoveChoose();
	friend class Game;
};
#endif

