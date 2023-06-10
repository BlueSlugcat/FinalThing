#include "Game.h"

Game::Game() : idolflag(true), dooropen(false), winflag(false), gameoverflag(false), endflag(false), exitpos({1,1})
{
	bool flag = true;
	
	while (flag)
	{
		system("cls");
		cout << "(Recommended you increase window size by a little bit)\nChoose Dungeon or press ESC to close game" << endl
			<< "1. small\n"
			<< "2. medium\n"
			<< "3. large (Unfinished)\n"
			<< "4. random (Not Recommended)\n";
		switch (_getch())
		{
		case 49:
			flag = false;
			dungeon = new Dungeon(1,true);
			system("cls");
			cout << "loading";
			break;
		case 50:
			flag = false;
			dungeon = new Dungeon(3,true);
			system("cls");
			cout << "loading";
			break;
		case 51:
			flag = false;
			dungeon = new Dungeon(2,true);
			system("cls");
			cout << "loading";
			break;
		case 52:
			flag = false;
			dungeon = new Dungeon(4,true);
			system("cls");
			cout << "loading";
			break;
		case 27:
			flag = false;
			endflag = true;
			break;
		default:
			system("cls");
			cout << "Invaild, choose from given list, press any button to return to selection" << endl;
			system("pause");
		}
	}
	if (!endflag)
	{
		system("cls");
		cout << "This is you: @\nYour goal is to fight you way through the dungeon, find the Idol |?|, and make it to the exit |X| alive.\n "
			<< "you move with arrow keys. When you take a turn to move/attack/heal, enemies will take their action as well\n"
			<< "To attack: once next to your target simply press the arrow key in their exact direction and you will attack.\n"
			<< "Walking over items will cause you to pick them up, and stronger equipment is equipped automatically.\n"
			<< "Thats the important bits, now get going!";
		Sleep(3000);
		system("Pause");
		FillCatalog();
		PlaceObjects();
		Run();
	}
}

Game::Game(int)//save restore build //unfinished, as the save system never ended up working correctly
{
	FillCatalog();
	fstream file("typesave.txt");
	
	vector<char> entorder;
	vector<char> itorder;
	string line;
	string tok;
	int entnum;
	int itemnum;
	if (file.is_open())
	{
		
		getline(file, line, '\n');
		dungeon = new Dungeon(stoi(line));
		getline(file, line, '\n');
		entnum = stoi(line);
		getline(file, line, '\n');
		for (int i{}; i < entnum; i++)
		{
			entorder.push_back(line[0]);
			getline(file, line, '\n');
		}
		getline(file, line, '\n');
		itemnum = stoi(line);
		for (int i{}; i < itemnum; i++)
		{
			getline(file, line, '\n');
			itorder.push_back(line[0]);
		}
		file.close();
	}
	else
	{
		throw "Map save is not present or cannot be accessed";
	}
	fstream datfile("creaturessave.dat");
	if (datfile.is_open())
	{
		
		for (auto x : entorder)
		{
			if (x == 'p')
			{
				Player* temp = new Player;
				datfile.read((char*)*&temp, sizeof(Player*));
				activeEntities.push_back(*&temp);
			}
			else if (x == 'k')
			{
				Kobold* temp = new Kobold;
				datfile.read((char*)*&temp, sizeof(Kobold*));
				activeEntities.push_back(*&temp);
			}
			else if (x == 'g')
			{
				Golem* temp = new Golem;
				datfile.read((char*)*&temp, sizeof(Golem*));
				activeEntities.push_back(*&temp);
			}
			else if (x == 's')
			{
				Slime* temp = new Slime;
				datfile.read((char*)*&temp, sizeof(Slime*));
				activeEntities.push_back(*&temp);
			}
			
		}
		datfile.close();
	}
	else
	{
		throw "creature save is not present or cannot be accessed";
	}
	datfile.open("itemsave.dat");
	if (datfile.is_open())
	{
		for (auto x : itorder)
		{
			if (x == 'w')
			{
				Weapon* temp = new Weapon;
				datfile.read((char*)*&temp, sizeof(Weapon*));
				activeItems.push_back(*&temp);
			}
			else if (x == 'a')
			{
				Armor* temp = new Armor;
				datfile.read((char*)*&temp, sizeof(Armor));
				activeItems.push_back(*&temp);
			}
			else if (x == 'h')
			{
				Healitem* temp = new Healitem;
				datfile.read((char*)*&temp, sizeof(Healitem*));
				activeItems.push_back(*&temp);
			}
			else if (x == 'h')
			{
				Item* temp = new Item;
				datfile.read((char*)*&temp, sizeof(Item*));
				activeItems.push_back(*&temp);
			}

		}
		datfile.close();
	}
	else
	{
		throw "Item save is not present or cannot be accessed";
	}

}

Game::~Game()
{
	
	for (auto thing : activeEntities)
	{
		delete[] thing;
	}
	for (auto item : activeItems)
	{
		delete[] item;
	}
	activeEntities.clear();
	activeItems.clear();
	delete dungeon;

	cout << "Game dtor" << endl;
}

void Game::FillCatalog() // fills item catalog from a .txt file
{
	fstream file("itemcatalog.txt");
	string line;
	string tok;
	switch (file.is_open())
	{
	case true:
		while (getline(file, line, '\n'))
		{
			stringstream temp(line);
			getline(temp, tok, ',');
			if (tok == "weapon")
			{
				weaponCatalog.push_back(line);
			}
			else if (tok == "armor")
			{
				armorCatalog.push_back(line);
			}
			else if (tok == "heal")
			{
				healthCatalog.push_back(line);
			}
		}
		file.close();
		break;
	case false:
		throw "itemcatalog could not be opened";
		break;
	}
}

void Game::PlaceObjects()//handles the creation and placement of Creatures and Items
{
	string tempname;
	string temptype;
	vector<int> temppos;
	vector<string> temptags;
	vector<vector<int*>> alphaPos;
	int alphanum{};
	activeEntities.clear();
	for (int y{}; y < dungeon->truesizey; y++)
	{
		for (int x{}; x < dungeon->truesizex; x++)
		{
			if (dungeon->map[y][x] == '@')//i know the y then x looks strange, how do you think i feel trying to do the mental gymnastics to make this work
			{
				activeEntities.insert(activeEntities.begin(), new Player(x, y)); // this will ALWAYS place the player at the start of the list in order to know for sure where player will always be in the list 
				player_pos = { x, y };
			
			}
			else if (dungeon->map[y][x] == 'k')
			{
				activeEntities.push_back(new Kobold(x, y));
			
			}
			else if (dungeon->map[y][x] == 'K')
			{
				activeEntities.push_back(new Kobold(1, x, y)); //if any amount of kobolds are on the map, at least 1 alpha kobold must be among them
				alphanum++;
				
				alphaPos.push_back({&(activeEntities.back()->pos_m[0]), &(activeEntities.back()->pos_m[1]) });

				
			}
			else if (dungeon->map[y][x] == 'G')
			{
				activeEntities.push_back(new Golem(x, y));
		
			}
			else if (dungeon->map[y][x] == 'S')
			{
				activeEntities.push_back(new Slime(x, y));
		;
			}
			else if (dungeon->map[y][x] == '!')
			{
				temptags.clear();
				string temp;
				int attacktemp;
				random_device dev;
				mt19937 scug(dev());
				uniform_int_distribution<int> dis(0, weaponCatalog.size()-1);
				int lazy = dis(scug);
				stringstream tempstream(weaponCatalog[lazy]);
				getline(tempstream, temptype, ',');
				getline(tempstream, tempname, ',');
				getline(tempstream, temp, ',');
				attacktemp = stoi(temp);
				while (getline(tempstream, temp, ','))
				{
					temptags.push_back(temp);
				}
				activeItems.push_back(new Weapon(tempname, temptype, { x,y }, attacktemp, temptags));
			}
			else if (dungeon->map[y][x] == '[')
			{
				temptags.clear();
				string temp;
				int deftemp;
				random_device dev;
				mt19937 scug(dev());
				uniform_int_distribution<int> dis(0, armorCatalog.size() - 1);
				int lazy = dis(scug);
				stringstream tempstream(armorCatalog[lazy]);
				getline(tempstream, temptype, ',');
				getline(tempstream, tempname, ',');
				getline(tempstream, temp, ',');
				deftemp = stoi(temp);
				while (getline(tempstream, temp, ','))
				{
					temptags.push_back(temp);
				}
				activeItems.push_back(new Armor(tempname, temptype, { x,y }, deftemp, temptags));
			}
			else if (dungeon->map[y][x] == '%')
			{

				string temp;
				int healtemp;
				random_device dev;
				mt19937 scug(dev());
				uniform_int_distribution<int> dis(0, healthCatalog.size() - 1);
				int lazy = dis(scug);
				stringstream tempstream(healthCatalog[lazy]);
				getline(tempstream, temptype, ',');
				getline(tempstream, tempname, ',');
				getline(tempstream, temp, ',');
				healtemp = stoi(temp);
				activeItems.push_back(new Healitem (tempname, temptype, { x,y }, healtemp));
			}
			else if (dungeon->map[y][x] == '?')
			{
				activeItems.push_back(new Item("Idol", "Idol", { x,y }));
				idolpos = { x,y };
			}
		}
	}
	for (auto thing : activeEntities)
	{
		if (thing->name == "Kobold")
		{
			thing->SelectLeader(alphaPos);
		}
	}

}

void Game::MovePhase()
{
	string k = "Kobold";
	string ka = "Kobold Alpha";
	string g = "Golem";
	string s = "Slime";
	vector<int> vtemp;
	int i{};
	bool playerloop = true;
	bool playerattack = false;
	Player* player = (Player*)activeEntities[0];
	if (player->slimed)
	{
		player->slimed = false;
		playerloop = false;
		Sleep(2000);
	}
	while (playerloop)
	{

		player->MoveChoose();
		if (player->exitflag)
		{
			system("cls");
			cout << "exiting" << endl;
			endflag = true;
			break;
		}
		else if (player->saveflag)
		{
			player->saveflag = false;
			system("cls");
			cout << "Saving state" << endl;
			//Save();
			system("pause");
			UpdateScreen();
		}
		else if (player->healflag)
		{
			player->Heal();
			player->healflag = false;
			playerloop = false;
			UpdateScreen();
		}
		else if (!(player->requestfail))
		{
			

			for (auto entity : activeEntities)
			{
				if (i > 0)
				{
					if (player->requested_pos == entity->pos_m)
					{
						player->Attack(entity);
						player_pos = player->pos_m;
						player->attackflag = true;
						player->attacktarget = entity->name;
						playerloop = false;
						playerattack = true;
					}
				}
				i++;
			}
			if (!playerattack)
			{
				if (dungeon->map[player->requested_pos[1]][player->requested_pos[0]] != '#')
				{
					int i{};
					bool itemfind = false;
					for (auto item : activeItems)
					{
						if (player->requested_pos == item->pos_m)
						{
							player->inventory.Append(item);
							itemfind = true;
							player->itemflag = true;
							player->itemfound = item->title;
							switch (player->requested_pos == idolpos)
							{
							case true:
								idolflag = false;
								dooropen = true;
							}
							break;
						}
						i++;
					}
					switch (itemfind)
					{
					case true:
						
						activeItems.erase(activeItems.begin() + i);
						player->InventoryCheck();
						break;
					}
					playerloop = false;
					dungeon->map[player->pos_m[1]][player->pos_m[0]] = ' ';
					player->MoveTrue();
					player_pos = player->pos_m;
					if (player_pos == exitpos && dooropen)
					{
						winflag = true;
					}
				}

			}
		}
		else
		{
			player->requestfail = false;
		}
	}
	
	
	
	if (!endflag)
	{
		//npc detect phase
		//npc movephase, 
		i = 0;
		for (Creature* entity : activeEntities)
		{
			if (entity->name != player->name)
			{

				if ((entity->name == k || entity->name == ka) && !(entity->slimed))
				{
					bool kflag = true;
					entity->target_pos_m = player_pos;
					entity->Detect();
					entity->MoveChoose();
					for (Creature* thing : activeEntities)
					{
						if (thing->name !=  k && thing->name != ka)
						{
							if (entity->requested_pos == thing->pos_m)
							{
								switch (thing->pos_m == player_pos)
								{
								case true:
									hitplayerlast = entity->name;
									break;
								}
								entity->Attack(thing);
								kflag = false;
							}
						}
					}


					if (kflag && dungeon->map[entity->requested_pos[1]][entity->requested_pos[0]] == ' ' )
					{
						dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
						entity->MoveTrue();
						kflag = false;
					}

					else if (kflag && dungeon->map[entity->requested_pos[1]][entity->requested_pos[0]] != ' ' )
					{
						bool found = false;
						for (int x{}; x < 8; x++)
						{
							if (x == 6)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0]] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0], entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 2)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0] - 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 5)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0] + 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 3)
							{
								if (dungeon->map[entity->pos_m[1]][entity->pos_m[0] + 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}

							else if (x == 7)
							{
								if (dungeon->map[entity->pos_m[1]][entity->pos_m[0] - 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 0)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0] - 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 4)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0] + 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 1)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0]] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0], entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
						}


						if (!found)
						{
							entity->requested_pos = { entity->pos_m[0], entity->pos_m[1] };
							entity->MoveTrue();
						}
					}

				}

				else if (!(entity->slimed))
				{
					bool sflag = true;
					if (entity->name != g)
					{
						entity->target_pos_m = player_pos;
						entity->Detect();
					}
					else
					{
						for (auto scug : activeEntities)
						{
							if (scug->name != g)
							{
								entity->Detect(scug);
							}
						}
						entity->SelectTarget();
					}
					
					entity->MoveChoose();
					for (Creature* thing : activeEntities)
					{
						if (entity->name != thing->name)
						{
							if (entity->requested_pos == thing->pos_m)
							{
								switch (thing->pos_m == player_pos)
								{
								case true:
									hitplayerlast = entity->name;
									break;
								}
								entity->Attack(thing);
								sflag = false;
							}
						}
					}


					if (sflag && dungeon->map[entity->requested_pos[1]][entity->requested_pos[0]] == ' ')
					{
						dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
						entity->MoveTrue();
						sflag = false;
					}

					else if (sflag && dungeon->map[entity->requested_pos[1]][entity->requested_pos[0]] == ' ' )
					{
						bool found = false;
						for (int x{}; x < 8; x++)
						{
							if (x == 6)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0]] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0], entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 2)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0] - 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 5)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0] + 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 3)
							{
								if (dungeon->map[entity->pos_m[1]][entity->pos_m[0] + 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}

							else if (x == 7)
							{
								if (dungeon->map[entity->pos_m[1]][entity->pos_m[0] - 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 0)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0] - 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 4)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0] + 1] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 1)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0]] == ' ')
								{
									entity->requested_pos = { entity->pos_m[0], entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
						}

						if (!found)
						{
							entity->requested_pos = { entity->pos_m[0], entity->pos_m[1] };
							entity->MoveTrue();
						}
					}
				}
			}
		}
	}
	
}


 void Game::DeadCheck()
{
	int i = 0;
	vector<int> list;
	Player* player = (Player*)activeEntities[0];
	if (!(player->status))
	{
		gameoverflag = true;
	}
	for (auto entity : activeEntities)
	{
			if (!(entity->status))
			{
				dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
				
				list.insert(list.begin(), i);
			}
		i++;
	}

	for (int index : list)
	{
		delete[] activeEntities[index];
		activeEntities.erase(activeEntities.begin() + index);
		activeEntities.shrink_to_fit();
	}
}

void Game::UpdateScreen()
{
	dungeon->map[exitpos[1]][exitpos[0]] = 'X';
	Player* player = (Player*)activeEntities[0];
	dungeon->map[player->pos_m[1]][player->pos_m[0]] = '@';
	
	for (Item* item : activeItems)
	{
		if (item->type == "weapon")
		{
			dungeon->map[item->pos_m[1]][item->pos_m[0]] = '!';
		}
		else if (item->type == "armor")
		{
			dungeon->map[item->pos_m[1]][item->pos_m[0]] = '[';
		}
		else if (item->type == "heal")
		{
			dungeon->map[item->pos_m[1]][item->pos_m[0]] = '%';
		}
		else if (item->type == "Idol")
		{
			dungeon->map[item->pos_m[1]][item->pos_m[0]] = '?';
		}
	}
	for (Creature* entity : activeEntities)
	{
		if (entity->name != "Player")
		{
			if (entity->name == "Kobold" || entity->name == "Kobold Alpha")
			{
				Kobold* ktemp = (Kobold*)entity;
				if (ktemp->alpha)
				{
					dungeon->map[ktemp->pos_m[1]][ktemp->pos_m[0]] = 'K';
				}
				else
				{
					dungeon->map[ktemp->pos_m[1]][ktemp->pos_m[0]] = 'k';
				}
			}
			else if (entity->name == "Golem")
			{
				dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = 'G';
			}
			else
			{
				dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = 'S';
			}
		}
	}
	system("cls");
	cout << "\n HP: " << player->hp_current_m << "/" << player->hp_max_m << " | Press (h) to heal | press (s) to save\n Current Weapon: ";
	switch ((player->equippedWeapon == nullptr))
	{
	case false:
		cout << player->equippedWeapon->ReturnName() << " | Attack: " << player->equippedWeapon->ReturnAttack();
		break;
	default:
		cout << "Fists | Attack: " << player->attack_m;
	}
	cout << "  Current Armor: ";
	switch ((player->equippedArmor == nullptr))
	{
	case false:
		cout << player->equippedArmor->ReturnName() << " | Defense: " << player->equippedArmor->ReturnDef();
		break;
	default:
		cout << "Shirt | Defense: " << player->defense_m;
	}
	cout << "\n Heal items: " << player->healitemnum << endl;
	switch (player->slimed)
	{
	case true:
		cout << "You've been slimed! you cannot act for 1 turn" << endl;
		break;
	default:
		cout << endl;
	}
	switch (player->attackflag)
	{
	case true:
		cout << "You attacked " << player->attacktarget << endl;
		player->attacktarget.clear();
		player->attackflag = false;
		break;
	default:
		cout << endl;
	}
	switch (player->itemflag)
	{
	case true:
		cout << "You found " << player->itemfound << endl;
		player->itemfound.clear();
		player->itemflag = false;
		break;
	default:
		cout << endl;
	}
	dungeon->display();
}


void Game::Run()
{
	while (!endflag)
	{
		UpdateScreen();
		MovePhase();
		DeadCheck();
		if (gameoverflag == true)
		{
			endflag = true;
			system("cls");
			cout << "Game Over, you died\nYou were killed by a " << hitplayerlast << endl;
			Sleep(3000);
			system("pause");
			break;
		}
		else if (winflag == true)
		{
			endflag = true;
			system("cls");
			cout << "Victory! You've retrieved the Idol and escaped the dungeon!" << endl;
			Sleep(5000);
			system("pause");
			break;
		}
		
	}
	system("cls");
	cout << "Ending" << endl;
}

/*
void Game::Save()
{
	ofstream file("Creaturessave.dat");
	string temp;
	vector<char*> entorder;
	vector<char*> itorder;
	if (file.is_open())
	{
		
		for (auto thing : activeEntities)
		{
			if (thing->name == "Player")
			{
				entorder.push_back((char*)"p");
				Player* player = (Player*)thing;
				file.write((char*)*&player, sizeof(Player*));
			}
			else if (thing->name == "Kobold")
			{
				entorder.push_back((char*)"k");
				Kobold* kobold = (Kobold*)thing;
				file.write((char*)*&kobold, sizeof(Kobold*));
			}
			else if (thing->name == "Golem")
			{
				entorder.push_back((char*)"g");
				Golem* golem = (Golem*)thing;
				file.write((char*)*&golem, sizeof(Golem*));
			}
			else if (thing->name == "Slime")
			{
				entorder.push_back((char*)"s");
				Slime* slime = (Slime*)thing;
				file.write((char*)*&slime, sizeof(Slime*));
			}
		}
		switch (file.bad())
		{
		case(true):
			file.close();
			throw "Error during creature save";
			break;
		}
		file.close();
	}
	else
	{
		throw "Save could not be created";
	}
	file.open("itemsave.dat");
	if (file.is_open())
	{
		for (auto thing : activeItems)
		{
			if (thing->type == "weapon")
			{
				itorder.push_back((char*)"w");
				Weapon* weapon = (Weapon*)thing;
				file.write((char*)*&weapon, sizeof(Weapon*));
			}
			else if (thing->type == "armor")
			{
				itorder.push_back((char*)"a");
				Armor* armor = (Armor*)thing;
				file.write((char*)*&armor, sizeof(Armor*));
			}
			else if (thing->type == "heal")
			{
				itorder.push_back((char*)"h");
				Healitem* heal = (Healitem*)thing;
				file.write((char*)*&heal, sizeof(Healitem *));
			}
			else if (thing->type == "Idol")
			{
				itorder.push_back((char*)"i");
				Item* item = (Item*)thing;
				file.write((char*)*&item, sizeof(Item*));
			}
		}
		switch (file.bad())
		{
		case(true):
			file.close();
			throw "Error during item save";
			break;
		}
		file.close();
	}
	else
	{
		throw "Save could not be created";
	}
	file.open("typesave.txt");
	if (file.is_open())
	{
		temp = to_string(dungeon->type) + '\n';
		file.write(temp.c_str(), temp.size());
		temp = to_string(activeEntities.size()) + '\n';
		file.write(temp.c_str(), temp.size());
		for (auto x : entorder)
		{
			temp = x + '\n';
			file.write(temp.c_str(), temp.size());
		}
		temp = to_string(activeItems.size()) + '\n';
		file.write(temp.c_str(), temp.size());
		for (auto x : itorder)
		{
			temp = x + '\n';
			file.write(temp.c_str(), temp.size());
		}
		switch (file.bad())
		{
		case(true):
			file.close();
			throw "Error during map save";
			break;
		}
		file.close();


	}
	else
	{
		throw "Save could not be created";
	}
}
*/




