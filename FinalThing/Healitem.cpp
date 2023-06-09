#include "Healitem.h"

Healitem::Healitem() : Item(), healval(1)
{}

Healitem::Healitem(string name, string what, vector<int> pos, int heal) : Item(name, what, pos), healval(heal)
{}

Healitem::~Healitem()
{}

int Healitem::ReturnHeal()
{
	return healval;
}