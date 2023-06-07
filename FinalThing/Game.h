#ifndef GAME_H
#define Game_H
#include "Dungeon.h"
#include "Creature.h"w
#include "Player.h"
#include "Kobold.h"
#include "Golem.h"
#include "Slime.h"
class Game
{
protected:
	vector<int[2]> tile_replace_list;
	bool idolflag;
	bool dooropen;
	bool winflag;
	bool gameoverflag;
	vector<int> player_pos;
	vector<Creature> activeEntities;
	Dungeon dungeon;
public:
	Game();
	~Game();
	void UpdateScreen();
	void MovePhase();
	Game& PlaceCreatures();
	void WinCheck();
	void GameOverCheck();
	void IdolCheck();
	void Run();
};
#endif

