#ifndef CREATURE_H
#define CREATURE_H
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
using std::uniform_int_distribution;
using std::random_device;
using std::mt19937;
class Creature
{
protected:
	bool slimed;
	bool status; //true = alive, false = dead
	string name;
	vector<int> requested_pos; //if i understood multithreading better i would have likes to have done mid function requests to the directior for a much more 
	bool detected;
	vector<int> target_pos_m;
	int hp_current_m;
	int hp_max_m;
	int attack_m;
	vector<string> attack_tags_m; //using vector because they make having collection of strings much nicer
	int defense_m;
	vector<string> defense_tags_m;
	vector<string> misc_tags_m;
	string description_m;
	int sightrange_m;
	vector<int> pos_m;
public:
	Creature();
	Creature(int hp, int attack, string aTags[], int defense, string dTags[], string mTags[], string description, int x, int y);//arg ctor
	Creature(string filename, int x, int y);//allows for creature values to be read from preset files
	Creature(const Creature& original);//copy ctor
	Creature& operator=(const Creature& original);//copy op
	Creature(Creature&& thing) noexcept;//move ctor
	Creature& operator=(Creature&& thing) noexcept;//move op
	virtual ~Creature();
	virtual void Detect();
	virtual void Detect(Creature* scug);
	virtual void Attack(Creature& target);
	virtual void TakeDamage(int attack, vector<string> aTags);
	virtual void MoveChoose();//determines next move, seperated from actually applying it so the game director can check the requested position
							  // then approve/deny the request(and re-run the function) or tell the creature to attack if the player/a hostile creature is in that position 
	virtual void MoveTrue();
	void Describe();
	void ShowTags();
	 vector<int> ReturnPos();

	virtual void SelectLeader(vector<vector<int*>> alphaPos);// only here to allow Kobold creation to be streamlined
	virtual void SelectTarget();

	friend class Game;
};
#endif
