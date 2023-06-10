
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC
#include <iostream>
#include "Creature.h"
#include "Dungeon.h"
#include "Game.h"
#include "Player.h"
int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    cout << "restore save state if one is present? y/n (Save system is not functioning properly at this time, error will occur)" << endl;
    if (_getch() == 121)
    {
        system("cls");
        cout << "Attempting to load save" << endl;
         Game game(1);
 
    }
    else
    {
        system("cls");
        Game game;
    }
    
}

