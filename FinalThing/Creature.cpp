#include "Creature.h"

Creature::Creature() : hp_current_m(1), hp_max_m(1), attack_m(1), attack_tags_m({"none", "test"}),
defense_m(0), defense_tags_m({ "none", "test" }), misc_tags_m({ "none" }), description_m("basic test creature")
{}

Creature::Creature(int hp, int attack, string aTags[], int defense, string dTags[], string mTags[], string descript) :
	hp_current_m(hp), hp_max_m(hp), attack_m(attack), defense_m(defense), description_m(descript)
{ 
	int aTagNum = sizeof(*aTags) / sizeof(aTags[0]);
	int dTagNum = sizeof(*dTags) / sizeof(dTags[0]);
	int mTagNum = sizeof(*mTags) / sizeof(mTags[0]);
	for (int i{}; i < aTagNum; i++)
	{
		attack_tags_m.push_back(aTags[i]);
	}
	for (int i{}; i < dTagNum; i++)
	{
		defense_tags_m.push_back(dTags[i]);
	}
	for (int i{}; i < mTagNum; i++)
	{
		misc_tags_m.push_back(mTags[i]);
	}
}

Creature::Creature(string filename)
{
	/*
	* file formating is as follows (order and seperation via new line is important here)
	* //starts at hp
	* hp (this is for both current and max, so just one number)
	* attack value (just a number >= 0) //allowing for attack of 0 could open the door for indirect damage or status effect enemies
	* attack tags (seperated by ',' for mutiple tags)
	* defense value (just a number >= 0)
	* defense tags (seperated by ',' for multiple tags)
	* misc tags (seperated by ',' for multiple tags) // these are for flavor tags, IE tags like "smelly", or things that don't have any real effect on gameplay
	* description (can be a multi-line description, but must be ended by this specific character: $
	*/

	fstream file;
	file.open(filename);
	if (file.is_open())
	{
		string temp;
		string tok;
		getline(file, temp, '\n');
		if (stoi(temp) <= 0)
		{
			hp_current_m = 1;
			hp_max_m = 1;
		}
		else
		{
			hp_current_m = stoi(temp);
			hp_max_m = stoi(temp);
		}
		getline(file, temp, '\n');
		if (stoi(temp) < 0)
		{
			attack_m = 1; //setting to 1 as this is the default, 0 will only be applied if it is specifically given
		}
		else
		{
			attack_m = stoi(temp);
		}
		getline(file, temp, '\n');
		stringstream tempstream(temp);
		while (getline(tempstream, tok, ','))
		{
			attack_tags_m.push_back(tok);
		}
		getline(file, temp, '\n');
		if (stoi(temp) < 0)
		{
			defense_m = 0;
		}
		else
		{
			defense_m = stoi(temp);
		}
		getline(file, temp, '\n');
		tempstream.str(string());
		tempstream.clear();
		tempstream.str(temp);
		tok.clear();
		while (getline(tempstream, tok, ','))
		{
			defense_tags_m.push_back(tok);
		}
		tempstream.str(string());
		tempstream.clear();
		tok.clear();
		getline(file, temp, '\n');
		tempstream.str(temp);
		while (getline(tempstream, tok, ','))
		{
			misc_tags_m.push_back(tok);
		}
		tempstream.str(string());
		tempstream.clear();
		tok.clear();
		getline(file, temp, '$');
		description_m = temp;

		file.close();

	}
	else
	{
		cout << "\n\nFAILURE TO OPEN FILE\n"
			<< "creature will use default values\n\n";

		hp_current_m = 1;
		hp_max_m = 1;
		attack_m = 1;
		attack_tags_m.push_back("none");
		defense_m = 1;
		defense_tags_m.push_back("none");
		misc_tags_m.push_back("none");
		description_m = "default";
	}



}



Creature::~Creature()
{}



void Creature::ShowTags()
{
	cout << "Attack tags: \n";
	for (string tag : attack_tags_m)
	{
		if (attack_tags_m.back() == tag)
		{
			cout << tag << endl;
		}
		else
		{
			cout << tag << ", ";
		}
	}
	
	cout << "\nDefense Tags: \n";
	for (string tag : defense_tags_m)
	{
		if (defense_tags_m.back() == tag)
		{
			cout << tag << endl;
		}
		else
		{
			cout << tag << ", ";
		}
	}
	cout << "\nMisc Tags: \n";
	for (string tag : misc_tags_m)
	{
		if (misc_tags_m.back() == tag)
		{
			cout << tag << endl;
		}
		else
		{
			cout << tag << ", ";
		}
	}
		
}
