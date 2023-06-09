#ifndef HEALITEM_H
#define HEALITEM_H
#include "Item.h"
class Healitem : public Item
{
protected:
	int healval;
public:
	Healitem();
	Healitem(string name, string what, vector<int> pos, int healval);
	~Healitem();
	int ReturnHeal();
};

#endif 

