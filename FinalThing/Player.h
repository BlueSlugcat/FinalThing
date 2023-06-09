#ifndef PLAYER_H
#define PLAYER_H
#include "Creature.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include "List.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"

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
	List<Item> inventory;
	Weapon* equippedWeapon;
	Armor* equippedArmor;

public: 
	Player();
	Player(int x, int y);
	~Player();
	void MoveChoose();
	void Attack(Creature& target);
	void TakeDamage(int attack, vector<string> atags);
	friend class Game;

};
#endif

