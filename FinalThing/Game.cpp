#include "Game.h"

Game::Game() : idolflag(true), dooropen(false), winflag(false), gameoverflag(false), dungeon(new Dungeon(true)), endflag(false)
{
	PlaceCreatures();
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
					dungeon->map[player->pos_m[1]][player->pos_m[0]] = '*';
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
		i = 0;//will go back and change all for each using an int "iterator" if i have the time
		for (auto entity : activeEntities)
		{
			if (entity->name != "Player")
			{

				if (entity->name == k || entity->name == ka)
				{
					entity->target_pos_m = player_pos;
					entity->Detect();
				}
				if (entity->name == g)
				{
					Golem* gtemp = (Golem*)entity;
					for (auto thing : activeEntities)
					{
						if (*&thing != *&entity)
						{
							if (thing->name != g)
							{
								gtemp->Detect(thing);
							}
						}
					}
				}
				else
				{
					entity->target_pos_m = player_pos;
					entity->Detect();
				}

			}
			i++;
		}
		vector<vector<int>> used;
		//npc movephase, this is a horrific jumble of code that somehow works, and im not going to even try to get into detail as to how it does
		bool nogo = false;
		i = 0;
		for (Creature* entity : activeEntities)
		{
			if (entity->name != player->name)
			{

				if (entity->name == k || entity->name == ka)
				{
					bool kflag = true;
					entity->target_pos_m = player_pos;
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


					if (kflag && dungeon->map[entity->requested_pos[1]][entity->requested_pos[0]] == '*')
					{
						dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
						entity->MoveTrue();
						kflag = false;
					}

					else if (kflag && dungeon->map[entity->requested_pos[1]][entity->requested_pos[0]] != '*' )
					{
						bool found = false;
						for (int x{}; x < 8; x++)
						{
							if (x == 6)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0]] == '*')
								{
									entity->requested_pos = { entity->pos_m[0], entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 2)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0] - 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 5)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0] + 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 3)
							{
								if (dungeon->map[entity->pos_m[1]][entity->pos_m[0] + 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}

							else if (x == 7)
							{
								if (dungeon->map[entity->pos_m[1]][entity->pos_m[0] - 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 0)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0] - 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 4)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0] + 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 1)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0]] == '*')
								{
									entity->requested_pos = { entity->pos_m[0], entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
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

				else if (entity->name == "Golem")
				{
					bool gflag = true;
					Golem* gtemp = (Golem*)entity;
					gtemp->MoveChoose();
					for (Creature* thing : activeEntities)
					{
						if (*&gtemp != *&thing && thing->name != "Golem")
						{
							if (gtemp->requested_pos == thing->pos_m)
							{
								gtemp->Attack(*thing);
								gflag = false;
							}
						}
					}
					while (gflag)
					{
						gtemp->MoveChoose();
						if (dungeon->map[gtemp->requested_pos[1]][gtemp->requested_pos[0]] != '#')
						{
							dungeon->map[gtemp->pos_m[1]][gtemp->pos_m[0]] = '*';
							gtemp->MoveTrue();
							gflag = false;
						}

						else if (gtemp->detected)
						{
							while (gflag)
							{
								srand(time(NULL));
								int xmod = rand() % 1 - 1;
								srand(time(NULL));
								int ymod = rand() % 1 - 1;
								vtemp = { (gtemp->requested_pos[0] + xmod), (gtemp->requested_pos[1] + ymod) };
								if (vtemp != gtemp->pos_m)
								{
									if (dungeon->map[vtemp[1]][vtemp[0]] != '#' && (vtemp[0] - gtemp->pos_m[0] > 1 && vtemp[0] - gtemp->pos_m[0] < -1) && (vtemp[1] - gtemp->pos_m[1] > 1 && vtemp[1] - gtemp->pos_m[1] < -1))
									{

										for (Creature* thing : activeEntities)
										{
											if (*&gtemp != *&thing)
											{
												if (gtemp->requested_pos == thing->pos_m)
												{
													nogo = true;
												}
											}
										}
										if (!nogo)
										{
											gtemp->requested_pos = vtemp;
											dungeon->map[gtemp->pos_m[1]][gtemp->pos_m[0]] = '*';
											gtemp->MoveTrue();
											gflag = false;
											used.clear();
										}
										else
										{
											nogo = false;
											used.push_back(vtemp);
										}

									}
									else if ((vtemp[0] - gtemp->pos_m[0] > 1 && vtemp[0] - gtemp->pos_m[0] < -1) && (vtemp[1] - gtemp->pos_m[1] > 1 && vtemp[1] - gtemp->pos_m[1] < -1))
									{

										used.push_back(vtemp);
									}
								}
								if (used.size() >= 8)
								{
									gtemp->requested_pos = gtemp->pos_m;
									gtemp->MoveTrue();
									gflag = false;

								}
							}
						}
					}
				}

				else
				{
					bool sflag = true;
					entity->target_pos_m = player_pos;
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


					if (sflag && dungeon->map[entity->requested_pos[1]][entity->requested_pos[0]] == '*')
					{
						dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
						entity->MoveTrue();
						sflag = false;
					}

					else if (sflag && dungeon->map[entity->requested_pos[1]][entity->requested_pos[0]] == '*' )
					{
						bool found = false;
						for (int x{}; x < 8; x++)
						{
							if (x == 6)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0]] == '*')
								{
									entity->requested_pos = { entity->pos_m[0], entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 2)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0] - 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 5)
							{
								if (dungeon->map[entity->pos_m[1] - 1][entity->pos_m[0] + 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] - 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 3)
							{
								if (dungeon->map[entity->pos_m[1]][entity->pos_m[0] + 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}

							else if (x == 7)
							{
								if (dungeon->map[entity->pos_m[1]][entity->pos_m[0] - 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 0)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0] - 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] - 1, entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 4)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0] + 1] == '*')
								{
									entity->requested_pos = { entity->pos_m[0] + 1, entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
									entity->MoveTrue();
									found = true;
									break;
								}
							}
							else if (x == 1)
							{
								if (dungeon->map[entity->pos_m[1] + 1][entity->pos_m[0]] == '*')
								{
									entity->requested_pos = { entity->pos_m[0], entity->pos_m[1] + 1 };
									dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
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
		if (entity != *&player)
		{
			if (!(entity->status))
			{
				dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = '*';
				
				list.insert(list.begin(), i);
			}
		}
		i++;
	}

	for (int index : list)
	{
		activeEntities.erase(activeEntities.begin() + index-1);
		activeEntities.shrink_to_fit();
	}
}

void Game::UpdateScreen()
{
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
			}
			else
			{
				dungeon->map[entity->pos_m[1]][entity->pos_m[0]] = 'S';
			}
		}
	}

	system("cls");
	dungeon->display();
	for (auto thing : activeEntities)
	{
		cout << thing->hp_current_m << endl;
	}
	
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
		}
		
	}
	system("cls");
	cout << "Ending" << endl;
}

