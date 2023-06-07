#include "Game.h"

Game::Game() : idolflag(true), dooropen(false), winflag(false), gameoverflag(false), dungeon(new Dungeon(1)), activeEntities({Creature()})
{
	this->PlaceCreatures();
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
			if (dungeon.map[y][x] == '@')
			{
				activeEntities.push_back(Player(x, y));
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
}


