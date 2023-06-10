#include "Dungeon.h"

Dungeon::Dungeon()
{
	//testroom and testroom3 will work, testroom2 and 4 are there to test error flags, not built for save system
	fstream test("trueDungeon.txt");
	string line;
	string tok;
	size_t flag{};
	if (test.is_open())
	{
		getline(test, line, '\n');
		stringstream temp(line);
		getline(temp, tok, ',');
		if (stoi(tok) < 3)
		{
			throw std::out_of_range("Invalid room size, x and y must be >= 3");
		}
		truesizex = stoi(tok);
		getline(temp, tok,',');
		if (stoi(tok) < 3)
		{
			throw std::out_of_range("Invalid room size, x and y must be >= 3");
		}
		truesizey = stoi(tok);
		temp.str(string());
		temp.clear();
		tok.clear();
		map = new char* [truesizey];
		for (int i{}; i < truesizey; i++)
		{
			map[i] = new char[truesizex + 1];
		}
		while (getline(test, line, '\n'))
		{
			if (flag >= truesizey || line.length() > truesizex)
			{
				throw std::out_of_range("Dungeon map does not match given parameters");
			}
			strcpy(map[flag], line.c_str());
			flag++;
		}
		test.close();
	}
	else
	{
		throw "Map file could not be opened";
	}

}

Dungeon::Dungeon(int game, bool thing)
{
	string filename;
	int result = game;
	if (result == 4)
	{
		srand(time(NULL));
		result = rand() % 3 + 1;
	}
	if (result == 1)
	{
		filename = "truedungeon.txt";
		type = 1;
	}
	else if (result == 2)
	{
		filename = "truedungeon2.txt";
		type = 2;
	}
	else
	{
		filename = "truedungeon3.txt";
		type = 3;
	}
	fstream layout("dungeon\\" + filename);
	string line;
	string tok;
	size_t flag{};
	if (layout.is_open())
	{
		getline(layout, line, '\n');
		stringstream temp(line);
		getline(temp, tok, ',');
		if (stoi(tok) < 3)
		{
			throw std::out_of_range("Invalid room size, x and y must be >= 3");
		}
		truesizex = stoi(tok);
		getline(temp, tok, ',');
		if (stoi(tok) < 3)
		{
			throw std::out_of_range("Invalid room size, x and y must be >= 3");
		}
		truesizey = stoi(tok);
		temp.str(string());
		temp.clear();
		tok.clear();
		map = new char* [truesizey];
		for (int i{}; i < truesizey; i++)
		{
			map[i] = new char[truesizex + 1];
		}
		while (getline(layout, line, '\n'))
		{
			if (flag >= truesizey || line.length() > truesizex)
			{
				throw std::out_of_range("Dungeon map does not match given parameters");
			}
			strcpy(map[flag], line.c_str());
			flag++;
		}
		layout.close();
	}
	else
	{
		throw "Map file could not be opened";
	}
}

Dungeon::Dungeon(int ver) : type(ver)
{
	fstream layout("truebase" + to_string(ver) + ".txt");
	string line;
	string tok;
	size_t flag{};
	if (layout.is_open())
	{
		getline(layout, line, '\n');
		stringstream temp(line);
		getline(temp, tok, ',');
		if (stoi(tok) < 3)
		{
			throw std::out_of_range("Invalid room size, x and y must be >= 3");
		}
		truesizex = stoi(tok);
		getline(temp, tok, ',');
		if (stoi(tok) < 3)
		{
			throw std::out_of_range("Invalid room size, x and y must be >= 3");
		}
		truesizey = stoi(tok);
		temp.str(string());
		temp.clear();
		tok.clear();
		map = new char* [truesizey];
		for (int i{}; i < truesizey; i++)
		{
			map[i] = new char[truesizex + 1];
		}
		while (getline(layout, line, '\n'))
		{
			if (flag >= truesizey || line.length() > truesizex)
			{
				throw std::out_of_range("Dungeon map does not match given parameters");
			}
			strcpy(map[flag], line.c_str());
			flag++;
		}
		layout.close();
	}
	else
	{
		throw "Map file could not be opened";
	}
}

Dungeon::~Dungeon()
{
	for (int i{}; i < truesizey; i++)
	{
		delete map[i];
	}
	delete[] map;

	cout << "dungeon dtor" << endl;
}

void Dungeon::display()
{
	for (int i{}; i < truesizey; i++)
	{
		cout << map[i] << endl;
	}
}