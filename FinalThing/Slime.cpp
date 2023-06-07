#include "Slime.h"

Slime::Slime() : Creature("slime.txt", 0, 0)
{
	name = "Slime";
}

Slime::Slime(int x, int y) : Creature("slime.txt", x, y)
{
	name = "Slime";
}

Slime::~Slime()
{}
