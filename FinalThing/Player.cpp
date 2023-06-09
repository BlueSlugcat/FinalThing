#include "Player.h"

Player::Player() :Creature("Player.txt", 1, 1), exitflag(false) ,equippedWeapon(nullptr), equippedArmor(nullptr)
{
	name = "Player";
	
}

Player::Player(int x, int y) :Creature("Player.txt", x, y) , exitflag(false), equippedWeapon(nullptr), equippedArmor(nullptr)
{
	name = "Player";
	
}

Player::~Player()
{
	cout << "Player Dtor" << endl;

}

void Player::MoveChoose()
{
	int buffer = _getch();
	if (buffer == 224)
	{
		buffer = _getch();
	}
	switch (buffer)
	{
	case ESC:
		cout << "ESC" << endl;
		exitflag = true;
		break;
	case UP:
		requested_pos[1] = (pos_m[1] - 1);
		requested_pos[0] = pos_m[0];
		cout << "UP" << endl;
		break;
	case LEFT:
		requested_pos[0] = pos_m[0] - 1;
		requested_pos[1] = pos_m[1];
		cout << "LEFT" << endl;
		break;
	case RIGHT:
		requested_pos[0] = pos_m[0] + 1;
		requested_pos[1] = pos_m[1];
		cout << "RIGHT" << endl;
		break;
	case DOWN:
		requested_pos[1] = pos_m[1] + 1;
		requested_pos[0] = pos_m[0];
		cout << "DOWN" << endl;
		break;
	default:
		requestfail = true;
		cout << "FAIL" << endl;
		break;

	}
}

void Player::Attack(Creature& target)
{
	switch ((equippedWeapon == nullptr))
	{
	case true:
		target.TakeDamage(attack_m + equippedWeapon->ReturnAttack(), equippedWeapon->ReturnTags());
		break;
	case false:
		target.TakeDamage(attack_m, attack_tags_m);
		break;
	}
}

void Player::TakeDamage(int attack, vector<string> aTags)
{
	bool weakfire = false;
	bool weakfrost = false;
	bool weakblunt = false;
	bool weakpierce = false;
	bool weakslice = false;
	bool resistfire = false;
	bool resistfrost = false;
	bool resistblunt = false;
	bool resistpierce = false;
	bool resistslice = false;
	bool nullify = false;
	float basedamage = attack;
	vector<string> tempdef;

	switch ((equippedArmor == nullptr))
	{
	case true:
		tempdef = defense_tags_m;
	case false:
		tempdef = equippedArmor->ReturnTags();
	}

	for (string tag : tempdef)
	{
		if (tag == "cloth")
		{
			weakfire = true;
			weakslice = true;
			weakblunt = true;
		}
		else if ( tag == "solid")
		{
			weakblunt = true;
			weakfrost = true;
			resistpierce = true;
			resistslice = true;
		}
		else if (tag == "mail")
		{
			resistslice = true;
			weakfrost = true;
			resistfire = true;
		}
		else if (tag == "leather")
		{
			weakpierce = true;
			resistslice = true;
		}
		else if (tag == "nullifying")
		{
			nullify = true;
		}
	}

	switch (nullify)
	{
	case true:
		weakfire = false;
		weakfrost = false;
		weakblunt = false;
		weakpierce = false;
		weakslice = false;
	}
	for (string tag : aTags)
	{
		if (tag == "sticky") //50% chance for effect to be applied
		{
			random_device dev;
			mt19937 scug(dev());
			uniform_int_distribution<int> dis(1, 10);
			switch ((dis(scug) > 5))
			{
			case true:
				slimed = true;
				break;
			}
		}
		else
		{
			if (tag == "slice")
			{
				switch (weakslice)
				{
				case true:
					basedamage += 3;
					break;
				case false:
					switch (resistslice)
					{
					case true:
						basedamage -= 0.5;
					}
					break;
				}

			}
			else if (tag == "blunt")
			{
				switch (weakblunt)
				{
				case true:
					basedamage += 3;
					break;
				case false:
					switch (resistblunt)
					{
					case true:
						basedamage -= 3;
					}
					break;
				};
			}
			else if (tag == "pierce" && weakpierce == true)
			{
				switch (weakpierce)
				{
				case true:
					basedamage += 3;
					break;
				case false:
					switch (resistpierce)
					{
					case true:
						basedamage -= 3;
					}
					break;
				}
			}
			else if (tag == "fire")
			{
				switch (weakfire)
				{
				case true:
					basedamage *= 2;
					break;
				case false:
					switch (resistfire)
					{
					case true:
						basedamage *= 0.5;
					}
					break;
				}
			}
			else if (tag == "frost")
			{
				switch (weakfrost)
				{
				case true:
					basedamage *= 2;
					break;
				case false:
					switch (resistfrost)
					{
					case true:
						basedamage *= 0.5;
					}
				}
			}
		}
	}

	if (fmod(basedamage, 1) > .4)
	{
		basedamage += 1;
	}

	int actualdamage = (int)basedamage - defense_m;
	if (actualdamage < 0)
	{
		actualdamage = 0;
	}
	if ((hp_current_m - actualdamage) <= 0)
	{
		hp_current_m = 0;
		status = false;

	}
	else
	{
		hp_current_m -= actualdamage;
	}
}