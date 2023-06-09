#include "Item.h"

Item::Item() : title("Item"), pos_m({ 0,0 })
{}

Item::Item(string name, string what, vector<int> pos) : title(name), pos_m(pos)
{}

Item::~Item()
{}

vector<int> Item::ReturnPos()
{
	return pos_m;
}