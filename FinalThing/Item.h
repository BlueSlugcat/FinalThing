#ifndef ITEM_H
#define ITEM_H
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <time.h>
#include <stdlib.h>
#include <random>
using std::time;
using std::srand;
using std::rand;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::fstream;
using std::stringstream;

class Item
{
protected:
	string title;
	string type;
	vector<int> pos_m;
public:
	Item();
	Item(string name, string what, vector<int> pos);
	virtual ~Item();
	vector<int> ReturnPos();

};

#endif

