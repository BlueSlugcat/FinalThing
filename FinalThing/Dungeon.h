#ifndef DUNGEON_H
#define DUNGEON_H

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include "Creature.h"
using std::rand;
using std::srand;
using std::time;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::fstream;
using std::stringstream; 
using std::to_string;
class Dungeon
{
protected:
	int type;
	int truesizex;
	int truesizey;
	char** map;
	
public:
	//this class will hold little to no manager functions do to them not being needed for its intended purpose
	Dungeon();//basic testroom build
	Dungeon(int game, bool thing);//actual game map build
	Dungeon(int ver);
	~Dungeon();
	void display();
	friend class Game;
};
#endif

