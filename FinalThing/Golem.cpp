#include "Golem.h"

Golem::Golem() : Creature("golem.txt", 0, 0)
{
	name = "Golem";
}

Golem::Golem(int x, int y) : Creature("golem.txt", x, y)
{
	name = "Golem";
}

Golem::~Golem()
{}