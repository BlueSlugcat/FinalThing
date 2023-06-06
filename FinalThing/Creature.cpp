#include "Creature.h"

Creature::Creature() : hp_current_m(1), hp_max_m(1), attack_m(1), attack_tags_m({"none", "test"}),
defense_m(0), defense_tags_m({ "none", "test" }), misc_tags_m({ "none" }), description_m("basic test creature"), pos_m({0,0})
{}

Creature::Creature(int hp, int attack, string aTags[], int defense, string dTags[], string mTags[], string descript, int x, int y) :
	hp_current_m(hp), hp_max_m(hp), attack_m(attack), defense_m(defense), description_m(descript), pos_m({ x, y })
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

Creature::Creature(const Creature& original)
{
	hp_current_m = original.hp_current_m;
	hp_max_m = original.hp_max_m;
	attack_m = original.attack_m;
	attack_tags_m = original.attack_tags_m;
	defense_m = original.defense_m;
	defense_tags_m = original.defense_tags_m;
	misc_tags_m = original.misc_tags_m;
	description_m = original.description_m;
}

Creature& Creature::operator=(const Creature& original)
{
	if (this != &original)
	{
		hp_current_m = original.hp_current_m;
		hp_max_m = original.hp_max_m;
		attack_m = original.attack_m;
		attack_tags_m = original.attack_tags_m;
		defense_m = original.defense_m;
		defense_tags_m = original.defense_tags_m;
		misc_tags_m = original.misc_tags_m;
		description_m = original.description_m;
	}

	return *this;
}

Creature::Creature(Creature&& thing) noexcept : hp_current_m(thing.hp_current_m), hp_max_m(thing.hp_max_m), attack_m(thing.attack_m), attack_tags_m(thing.attack_tags_m),
defense_m(thing.defense_m), defense_tags_m(thing.defense_tags_m), misc_tags_m(thing.misc_tags_m), description_m(thing.description_m)
{
	thing.hp_current_m = NULL;
	thing.hp_max_m = NULL;
	thing.attack_m = NULL;
	thing.attack_tags_m.clear();
	thing.defense_m = NULL;
	thing.defense_tags_m.clear();
	thing.misc_tags_m.clear();
	thing.description_m.clear();

}

Creature& Creature::operator=(Creature&& thing) noexcept 
{
	if (this != &thing)
	{
		hp_current_m = thing.hp_current_m;
		hp_max_m = thing.hp_max_m;
		attack_m = thing.attack_m;
		attack_tags_m = thing.attack_tags_m;
		defense_m = thing.defense_m;
		defense_tags_m = thing.defense_tags_m;
		misc_tags_m = thing.misc_tags_m;
		description_m = thing.description_m;
	}
	thing.hp_current_m = NULL;
	thing.hp_max_m = NULL;
	thing.attack_m = NULL;
	thing.attack_tags_m.clear();
	thing.defense_m = NULL;
	thing.defense_tags_m.clear();
	thing.misc_tags_m.clear();
	thing.description_m.clear();

	return *this;
}

Creature::~Creature()
{}

void Creature::Attack(Creature& target)
{

}

Creature& Creature::TakeDamage(int attack, vector<string> aTags)
{
	int actualdamage = attack - defense_m;
	if ((hp_current_m - actualdamage) < 0)
	{
		hp_current_m = 0;
	}
	else
	{
		hp_current_m -= actualdamage;
	}
	return *this;
}

void Creature::Describe()
{
	cout << description_m << endl;
}



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
