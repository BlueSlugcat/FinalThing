#include "Golem.h"

Golem::Golem() : Creature("golem.txt", 0, 0) , hunting(false)
{
	name = "Golem";
	
}

Golem::Golem(int x, int y) : Creature("golem.txt", x, y) , hunting(false)
{
	name = "Golem";
	
}

Golem::~Golem()
{}

void Golem::Detect(Creature* entity)
{
	for (int y = 1; y < (sightrange_m + 1); y++)
	{
		for (int x = 1; x < sightrange_m + 1; x++)
		{
			if ((pos_m[0] - x) == (entity->ReturnPos()[0]) && (pos_m[1] - y) == (entity->ReturnPos()[1]))
			{
				hunting = true;
				targets.push_back(entity->ReturnPos());
			}
			if ((pos_m[0] + x) == (entity->ReturnPos()[0]) && (pos_m[1] + y) == (entity->ReturnPos()[1]))
			{
				hunting = true;
				targets.push_back(entity->ReturnPos());
			}
		}
	}
}

void Golem::SelectTarget()
{
	double distance = 1000;
	int closest{};
	int i{};

	for (auto thing : targets)
	{
		if (sqrt(pow((thing[0] - pos_m[0]), 2) + pow((thing[1] - pos_m[1]), 2)) < distance)
		{
			closest = i;
			distance = sqrt(pow((thing[0] - pos_m[0]), 2) + pow((thing[i] - pos_m[1]), 2));
		}
		i++;
	}
	target_pos_m = { targets[closest][0], targets[closest][1] };
	targets.clear();
}


void Golem::MoveChoose() //basic creatures will wander randomly unless player is detected
{
	if (hunting)
	{
		SelectTarget();
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
		hunting = false;
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
