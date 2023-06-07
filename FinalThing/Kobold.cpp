#include "Kobold.h"

Kobold::Kobold() : Creature("kobold.txt", 0, 0), alpha(false), in_pack(false), leader_pos({ 0,0 })
{
	name = "Kobold";
}

Kobold::Kobold(int x, int y) : Creature("kobold.txt", x, y), alpha(false), in_pack(false)
{
	name = "Kobold";
}

Kobold::Kobold(size_t isalpha, int x, int y) : Creature("kobold.txt", x, y), alpha(true), in_pack(true) //kobold alpha will always have in_pack active in order to lead other kobolds
{
	name = "Kobold Alpha";
	hp_current_m += 2;
	hp_max_m += 2;
	attack_m += 1;
	defense_m += 1;
	misc_tags_m.push_back("pack leader");
}

void Kobold::SelectLeader(vector<vector<int*>> alphaPos)
{
	double distance = 1000;
	int closest{};
	int i{};
	for (auto thing : alphaPos)
	{
		if (sqrt(pow((*thing[0] - pos_m[0]), 2) + pow((*thing[1] - pos_m[1]), 2)) < distance)
		{
			closest = i;
			distance = sqrt(pow((*thing[0] - pos_m[0]), 2) + pow((*thing[i] - pos_m[1]), 2));
		}
		i++;
	}
	leader_pos = { &alphaPos[closest][0], &alphaPos[closest][1] };
}

void Kobold::Detect()//Kobold has dual purpose detection in order to maintain pack system
{
	bool flag = false;
	bool packflag = false;
	for (int y = 1; y < (sightrange_m + 1); y++)
	{
		for (int x = 1; x < sightrange_m + 1; x++)
		{
			if ((pos_m[0] - x) == target_pos_m[0] && (pos_m[1] - y) == target_pos_m[1])
			{
				flag = true;
			}
			else if ((pos_m[0] + x) == target_pos_m[0] && (pos_m[1] + y) == target_pos_m[1])
			{
				flag = true;
			}
			if ((pos_m[0] - x) ==  *leader_pos[0] && (pos_m[1] - y) == *leader_pos[1] && !alpha)
			{
				packflag = true;
			}
			else if ((pos_m[0] + x) == *leader_pos[0] && (pos_m[1] + y) == *leader_pos[1] && !alpha)
			{
				packflag = true;
			}
		}
	}
	if (flag)
	{
		detected = true;
	}
	else
	{
		detected = false;
	}
	if (packflag)
	{
		in_pack = true;
	}
	else if (!alpha)
	{
		in_pack = false;
	}
}


void Kobold::MoveChoose()
{
	if (detected)
	{
		if (target_pos_m[0] > pos_m[0])
		{
			requested_pos[0] = pos_m[0] + 1;
		}
		else if (target_pos_m[0] < pos_m[0])
		{
			requested_pos[0] = pos_m[0] - 1;
		}
		if (target_pos_m[1] > pos_m[1])
		{
			requested_pos[1] = pos_m[1] + 1;
		}
		else if (target_pos_m[1] < pos_m[1])
		{
			requested_pos[1] = pos_m[1] - 1;
		}
	}
	else if (!in_pack)
	{
		if (*leader_pos[0] > pos_m[0])
		{
			requested_pos[0] = pos_m[0] + 1;
		}
		else if (*leader_pos[0] < pos_m[0])
		{
			requested_pos[0] = pos_m[0] - 1;
		}
		if (*leader_pos[1] > pos_m[1])
		{
			requested_pos[1] = pos_m[1] + 1;
		}
		else if (*leader_pos[1] < pos_m[1])
		{
			requested_pos[1] = pos_m[1] - 1;
		}
	}
	else
	{
		srand(time(NULL));
		int xchange = (rand() % 1 - 1);
		srand(time(NULL));
		int ychange = (rand() % 1 - 1);
		requested_pos[0] = pos_m[0] + xchange;
		requested_pos[1] = pos_m[1] + ychange;
	}
}

Kobold::~Kobold()
{
	cout << "Kobold Dtor" << endl;
}