
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include "Creature.h"
#include "Dungeon.h"
#include "Game.h"
#include "Player.h"
//add actual game director
//add graphical system/updater

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //Creature test;
    //test.ShowTags();
    //Creature filetest("testcreature.txt", 0, 0);
    //filetest.ShowTags();
    //Dungeon testroom(1);
    //testroom.display();
    Game thing;
    //Kobold steve;
    thing.Run();
}

