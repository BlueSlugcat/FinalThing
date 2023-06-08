#ifndef PLAYER_H
#define PLAYER_H
#include "Creature.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <time.h>

#define ESC 27
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
class Player : public Creature
{
protected:
	bool exitflag;
	bool requestfail;
public: 
	Player();
	Player(int x, int y);
	~Player();
	void MoveChoose();
	//void detect(); //used here in order to negate its effect for the player
	friend class Game;

};
#endif

