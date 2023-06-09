#ifndef GAME_H
#define Game_H
#include "Dungeon.h"
#include "Player.h"
#include "Kobold.h"
#include "Golem.h"
#include "Slime.h"
using std::cin;

class Game
{
protected:
	vector<string>weaponCatalog;
	vector<string>healthCatalog;
	vector<string>armorCatalog;
	vector<Item*> activeItems;
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

