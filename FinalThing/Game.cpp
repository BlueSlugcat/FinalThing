#include "Game.h"

Game::Game() : idolflag(true), dooropen(false), winflag(false), gameoverflag(false), endflag(false)
{
	bool flag = true;
	cout << "Choose Dungeon or press ESC to close game" << endl
		<< "1. small\n"
		<< "2. medium\n"
		<< "3. large (Recommended you increase window size by a little bit\n"
		<< "4. random\n";
	while (flag)
	{
		switch (_getch())
		{
		case 49:
			flag = false;
			dungeon = new Dungeon(1);
			break;
		case 50:
			flag = false;
			dungeon = new Dungeon(2);
			break;
		case 51:
			flag = false;
			dungeon = new Dungeon(3);
			break;
		case 52:
			flag = false;
			dungeon = new Dungeon(4);
			break;
		case 27:
			flag = false;
			endflag = true;
			break;
		default:
			cout << "Invaild, choose from given list" << endl;
			system("pause");
		}



	}
	
	PlaceCreatures();
	Run();
}

Game::~Game()
{
	for (auto item : activeEntities)
	{
		delete item;
	}
	delete dungeon;
	cout << "Game dtor" << endl;
}

void Game::PlaceCreatures()
{
	
	vector<vector<int*>> alphaPos;
	int alphanum{};
	activeEntities.clear();
	for (int y{}; y < dungeon->truesizey; y++)
	{
		for (int x{}; x < dungeon->truesizex; x++)
		{
			if (dungeon->map[y][x] == '@')//i know the y then x looks strange, how do you think i feel trying to do the mental gymnastics to make this work
			{
				activeEntities.insert(activeEntities.begin(), new Player(x, y)); // this will ALWAYS place the player at the start of the list, making it so the player acts first 
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
		else if (!(player->requestfail))
		{


			for (auto entity : activeEntities)
			{
				if (i > 0)
				{
					if (player->requested_pos == entity->pos_m)
					{
						player->Attack(*entity);
						player_pos = player->pos_m;
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
					playerloop = false;
					dungeon->map[player->pos_m[1]][player->pos_m[0]] = ' ';
					player->MoveTrue();
					player_pos = player->pos_m;
					//add conditionals for items on ground
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
		//npc movephase, this is a horrific jumble of code that somehow works, and im not going to even try to get into detail as to how it does
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
								entity->Attack(*thing);
								kflag = false;
							}
						}
					}


					if (kflag && dungeon->map[entity->requested_pos[1]][entity->requested_pos[0]] == ' ')
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
								entity->Attack(*thing);
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
			Sleep(50);
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
		if (entity != *&player)
		{
			if (!(entity->status) && entity->name != "Player")
			{
				dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = ' ';
				
				list.insert(list.begin(), i);
			}
		}
		i++;
	}

	for (int index : list)
	{
		activeEntities.erase(activeEntities.begin() + index);
		activeEntities.shrink_to_fit();
	}
}

void Game::UpdateScreen()
{
	system("cls");
	cout << "\nHP: " << activeEntities[0]->hp_current_m << "/" << activeEntities[0]->hp_max_m << endl;
	
	bool gflag = false;
	vector<int> temppos;
	Player* player = (Player*)activeEntities[0];
	dungeon->map[player->pos_m[1]][player->pos_m[0]] = '@';
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
				gflag = true;
				temppos = entity->target_pos_m;
			}
			else
			{
				dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = 'S';
			}
		}
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
			cout << "Game Over, you died" << endl;
			system("pause");
		}
	}
	system("cls");
	cout << "Ending" << endl;
}

