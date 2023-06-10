#include "Item.h"

Item::Item() : title("Item"), pos_m({ 0,0 })
{}

Item::Item(string name, string what, vector<int> pos) : title(name), type(what),pos_m(pos)
{}

Item::Item(const Item& thing) : title(thing.title), type(thing.type), pos_m(0, 0)
{}

Item::~Item()
{}

vector<int> Item::ReturnPos()
{
	return pos_m;
}


string Item::ReturnName()
{
	return title;
}


