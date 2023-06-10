#ifndef PLAYER_H
#define PLAYER_H
#include "Creature.h"
#include <windows.h>
#include <tchar.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <time.h>
#include "List.cpp"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Healitem.h"

#define ESC 27
#define UP 72
#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define H 104
#define S 115
class Player : public Creature
{
protected:
	bool saveflag;
	bool attackflag;
	string attacktarget;
	bool itemflag;
	string itemfound;
	bool healflag;
	bool exitflag;
	bool requestfail;
	int healitemnum;
	List<Item*> inventory;
	Weapon* equippedWeapon;
	Armor* equippedArmor;

public: 
	Player();
	Player(int x, int y);
	~Player();
	void Heal();
	void MoveChoose();
	void Attack(Creature* target);
	void TakeDamage(int attack, vector<string> atags);
	void InventoryCheck();
	friend class Game;

};
#endif

