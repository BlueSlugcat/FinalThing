#include "Weapon.h"

Weapon::Weapon() : Item(), attackval_m(1), tags_m({"none"})
{}

Weapon::Weapon(string name, string what, vector<int> pos, int attack, vector<string> tags) :
	Item(name, what, pos) , attackval_m(attack)
{
	tags_m.resize(tags.size());
	tags_m = tags;
}
Weapon::~Weapon()
{}

vector<string> Weapon::ReturnTags()
{
	return tags_m;
}

int Weapon::ReturnAttack()
{
	return attackval_m;
}