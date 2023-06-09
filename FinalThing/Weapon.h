#ifndef WEAPON_H 
#define WEAPON_H
#include "Item.h"
class Weapon : public Item
{
protected:
	int attackval_m;
	vector<string> tags_m;
public:
	Weapon();
	Weapon(string name, string what, vector<int> pos, int attack, vector<string>tags);
	~Weapon();
	vector<string> ReturnTags();
	int ReturnAttack();
};
#endif
