#ifndef CREATURE_H
#define CREATURE_H
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
class Creature
{
protected:
	int hp_current_m;
	int hp_max_m;
	int attack_m;
	vector<string> attack_tags_m; //using vector because they make having collection of strings much nicer
	int defense_m;
	vector<string> defense_tags_m;
	vector<string> misc_tags_m;
	string description_m;
	
public:
	Creature();
	Creature(int hp, int attack, string aTags[], int defense, string dTags[], string mTags[], string description);//arg ctor
	Creature(string filename);//allows for creature values to be read from preset files
	Creature(const Creature& original);//copy ctor
	Creature& operator=(const Creature& rhs);//copy op
	Creature(Creature&& original) noexcept;//move ctor
	Creature& operator=(Creature&& rhs) noexcept;//move op
	~Creature();
	void Attack(Creature target);
	Creature& TakeDamage(int attack, string* attack_tags);
	void Describe();
	void ShowTags();




};
#endif
