#include "Game.h"

Game::Game() : idolflag(true), dooropen(false), winflag(false), gameoverflag(false), dungeon(new Dungeon(true))
{
	PlaceCreatures();
}

Game::~Game()
{
	for (auto item : activeEntities)
	{
		delete item;
	}
}



Game& Game::PlaceCreatures()
{
	vector<vector<int*>> alphaPos;
	int alphanum{};
	activeEntities.clear();
	for (int y{}; y < dungeon.truesizey; y++)
	{
		for (int x{}; x < dungeon.truesizex; x++)
		{
			if (dungeon.map[y][x] == '@')//i know the y then x looks strange, how do you think i feel trying to do the mental gymnastics to make this work
			{
				activeEntities.insert(activeEntities.begin(), new Player(x, y)); // this will ALWAYS place the player at the start of the list, making it so the player acts first 
				player_pos = { x, y };
			
			}
			else if (dungeon.map[y][x] == 'k')
			{
				activeEntities.push_back(new Kobold(x, y));
			
			}
			else if (dungeon.map[y][x] == 'K')
			{
				activeEntities.push_back(new Kobold(1, x, y)); //if any amount of kobolds are on the map, at least 1 alpha kobold must be among them
				alphanum++;
				
				alphaPos.push_back({&(activeEntities.back()->pos_m[0]), &(activeEntities.back()->pos_m[1]) });

				
			}
			else if (dungeon.map[y][x] == 'G')
			{
				activeEntities.push_back(new Golem(x, y));
		
			}
			else if (dungeon.map[y][x] == 'S')
			{
				activeEntities.push_back(new Slime(x, y));
		;
			}
		}
	}
	for (auto thing : activeEntities)
	{
		if (thing->name == "Kobold")
		{
			thing->SelectLeader(alphaPos);
		}
	}
	return *this;
}

void Creature::SelectLeader(vector<vector<int*>> alphaPos)
{} //this is here because without it the the whole program shits itself



