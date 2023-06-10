#ifndef GAME_H
#define Game_H
#include "Dungeon.h"
#include "Player.h"
#include "Kobold.h"
#include "Golem.h"
#include "Slime.h"
using std::ofstream;

class Game
{
protected:
	vector<int> idolpos;
	vector<int>exitpos;
	vector<string>weaponCatalog;
	vector<string>healthCatalog;
	vector<string>armorCatalog;
	vector<Item*> activeItems;
	string hitplayerlast;
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
	Game(int);
	~Game();
	void UpdateScreen();
	void MovePhase();
	void DeadCheck();
	void PlaceObjects();
	void FillCatalog();
	void Run();
	void Save();
};
#endif

