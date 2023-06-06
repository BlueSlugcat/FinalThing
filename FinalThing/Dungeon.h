#ifndef DUNGEON_H
#define DUNGEON_H

#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::fstream;
using std::stringstream; 
class Dungeon
{
protected:
	//bool idolflag;
	//bool dooropen;
	size_t truesizex;
	size_t truesizey;
	char** map;
	
public:
	//this class will hold little to no manager functions do to them not being needed for its intended purpose
	Dungeon();//basic testroom build
	~Dungeon();
	//Dungeon& createdungeon();
	void display();
};
#endif

