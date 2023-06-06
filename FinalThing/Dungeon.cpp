#include "Dungeon.h"

Dungeon::Dungeon()
{
	//testroom and testroom3 will work, testroom2 and 4 are there to test error flags
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
		map = new char*[truesizey];
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
	delete map;
}



void Dungeon::display()
{
	for (int i{}; i < truesizey; i++)
	{
		cout << map[i] << endl;
	}
}