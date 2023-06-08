#ifndef GAME_H
#define Game_H
#include "Dungeon.h"
#include "Player.h"
#include "Kobold.h"
#include "Golem.h"
#include "Slime.h"

class Game
{
protected:
	vector<vector<int>> tile_replace_list;
	bool endflag;
	bool idolflag;
	bool dooropen;
	bool winflag;
	bool gameoverflag;
	vector<int> player_pos;
	vector<Creature*> activeEntities;
	Dungeon* dungeon;
public:
	Game();
	~Game();
	void UpdateScreen();
	void MovePhase();
	void DeadCheck();
	void PlaceCreatures();
	//void WinCheck();
	//void GameOverCheck();
	//void IdolCheck();
	void Run();
};
#endif

