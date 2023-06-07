#include "Slime.h"

Slime::Slime() : Creature("slime.txt", 0, 0)
{}

Slime::Slime(int x, int y) : Creature("slime.txt", x, y)
{}

Slime::~Slime()
{}
