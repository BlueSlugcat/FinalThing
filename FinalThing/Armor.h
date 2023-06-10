#ifndef ARMOR_H
#define ARMOR_H
#include "Item.h"
class Armor :public Item
{
protected:
	int defval_m;
	vector<string> tags_m;
public:
	Armor();
	Armor(string name, string what, vector<int> pos, int def, vector<string> tags);
	~Armor();
	int ReturnDef();
	vector<string> ReturnTags();
	friend class Player;
};
#endif

