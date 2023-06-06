

#include <iostream>
#include "Creature.h"
#include "Dungeon.h"


int main()
{
    Creature test;
    //test.ShowTags();
    Creature filetest("testcreature.txt", 0, 0);
    filetest.ShowTags();
}

