#include "Game.h"

Game::Game() : idolflag(true), dooropen(false), winflag(false), gameoverflag(false), dungeon(new Dungeon(true)), activeEntities({Creature()})
{
	PlaceCreatures();
}

Game::~Game()
{

}

Game& Game::PlaceCreatures()
{
	activeEntities.clear();
	for (int y{}; y < dungeon.truesizey; y++)
	{
		for (int x{}; x < dungeon.truesizex; x++)
		{
			if (dungeon.map[y][x] == '@')//i know the y then x looks strange, how do you think i feel trying to do the mental gymnastics to make this work
			{
				activeEntities.insert(activeEntities.begin(), Player(x, y)); // this will ALWAYS place the player at the start of the list, making it so the player acts first 
				player_pos = { x, y };
			}
			else if (dungeon.map[y][x] == 'k')
			{
				activeEntities.push_back(Kobold(x, y));
			}
			else if (dungeon.map[y][x] == 'K')
			{
				activeEntities.push_back(Kobold(1, x, y)); //if any amount of kobolds are on the map, at least 1 alpha kobold must be among them
			}
			else if (dungeon.map[y][x] == 'G')
			{
				activeEntities.push_back(Golem(x, y));
			}
			else if (dungeon.map[y][x] == 'S')
			{
				activeEntities.push_back(Slime(x, y));
			}
		}
	}
	return *this;
}


