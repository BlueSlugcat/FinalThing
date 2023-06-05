

#include <iostream>
#include "Creature.h"


int main()
{
    Creature test;
    //test.ShowTags();
    Creature filetest("C:\\creaturefiles\\test.txt");
    filetest.ShowTags();
}

