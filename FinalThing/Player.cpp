#include "Player.h"

Player::Player() :Creature("Player.txt", 1, 1), exitflag(false) ,equippedWeapon(nullptr), equippedArmor(nullptr), healitemnum(0), inventory(List<Item*>()), saveflag(false)
{
	name = "Player";
	
}

Player::Player(int x, int y) :Creature("Player.txt", x, y) , exitflag(false), equippedWeapon(nullptr), equippedArmor(nullptr), healitemnum(0), inventory(List<Item*>()), saveflag(false)
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
		exitflag = true;
		break;
	case UP:
		requested_pos[1] = (pos_m[1] - 1);
		requested_pos[0] = pos_m[0];
		break;
	case LEFT:
		requested_pos[0] = pos_m[0] - 1;
		requested_pos[1] = pos_m[1];
		break;
	case RIGHT:
		requested_pos[0] = pos_m[0] + 1;
		requested_pos[1] = pos_m[1];
		break;
	case DOWN:
		requested_pos[1] = pos_m[1] + 1;
		requested_pos[0] = pos_m[0];
		break;
	case H:
		healflag = true;
		break;
	case S:
		saveflag = true;
		break;
	default:
		requestfail = true;
		break;

	}
}

void Player::Attack(Creature* target)
{
	switch ((equippedWeapon == nullptr))
	{
	case false:
		target->TakeDamage(attack_m + equippedWeapon->ReturnAttack(), equippedWeapon->ReturnTags());
		break;
	case true:
		target->TakeDamage(attack_m, attack_tags_m);
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
		break;
	case false:
		tempdef =  equippedArmor->tags_m;
		break;
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
						basedamage *= 0.5;
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

void Player::InventoryCheck()
{
	int temphealitem{};
	Node<Item*>* temp = inventory.m_head;
	while (temp != nullptr)
	{
		if (temp->item->type == "heal")
		{
			temphealitem++;
		}
		else if (temp->item->type == "weapon")
		{
			
			if (equippedWeapon != nullptr && ((Weapon*)(temp->item))->attackval_m > equippedWeapon->attackval_m)
			{
				equippedWeapon = (Weapon*)(temp->item);
			}
			else if (equippedWeapon == nullptr)
			{
				equippedWeapon = (Weapon*)(temp->item);
			}
		}
		else if (temp->item->type == "armor")
		{
			if (equippedArmor != nullptr && ((Armor*)(temp->item))->defval_m > equippedArmor->defval_m)
			{
				equippedArmor = (Armor*)(temp->item);
			}
			else if (equippedArmor == nullptr)
			{
				equippedArmor = (Armor*)(temp->item);
			}
		}

		temp = temp->m_next;
	}
	healitemnum = temphealitem;
}

void Player::Heal()
{
	Node<Item*>* temp = inventory.m_head;
	switch (healitemnum > 0)
	{
	case true:
		switch (hp_current_m == hp_max_m)
		{
		case false:
				while (temp != nullptr)
				{
					if (temp->item->type == "heal")
					{
						healitemnum--;
						switch ((((Healitem*)(temp->item))->ReturnHeal() + hp_current_m) > hp_max_m)
						{
						case true:
							hp_current_m = hp_max_m;
							break;
						case false:
							hp_current_m += ((Healitem*)(temp->item))->ReturnHeal();
							break;
						}
						system("cls");
						cout << "Used " << temp->item->title << " and healed " << ((Healitem*)(temp->item))->ReturnHeal() << " points\n";
						inventory.DeleteData(temp->item);
						system("pause");
						break;
					}
					temp = temp->m_next;
				}
				break;
		case true:
			system("cls");
			cout << "You are already at full health" << endl;
			system("pause");
			break;
		}
		break;
	case false:
		system("cls");
		cout << "You do not have any healing items" << endl;
		system("pause");
		break;

	}
	


	
	
}
