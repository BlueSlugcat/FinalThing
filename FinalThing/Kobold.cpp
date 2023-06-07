#include "Kobold.h"

Kobold::Kobold() : Creature("kobold.txt", 0, 0), alpha(false), in_pack(false), leader_pos({ 0,0 })
{}

Kobold::Kobold(int x, int y) : Creature("kobold.txt", x, y), alpha(false), in_pack(false)
{}

Kobold::Kobold(size_t isalpha, int x, int y) : Creature("kobold.txt", x, y), alpha(true), in_pack(false)
{
	hp_current_m += 2;
	hp_max_m += 2;
	attack_m += 1;
	defense_m += 1;
	misc_tags_m.push_back("pack leader");
}

Kobold::~Kobold()
{}