#include "Armor.h"

Armor::Armor() : Item(), defval_m(1), tags_m({"none"})
{}

Armor::Armor(string name, string what, vector<int> pos, int def, vector<string> tags) :
	Item(name,what,pos), defval_m(def), tags_m(tags)
{}

Armor::~Armor()
{}

vector<string> Armor::ReturnTags()
{
	return tags_m;
}

int Armor::ReturnDef()
{
	return defval_m;
}
