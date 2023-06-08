#include "Player.h"

Player::Player() :Creature("Player.txt", 1, 1), exitflag(false)
{
	name = "Player";
	
}

Player::Player(int x, int y) :Creature("Player.txt", x, y) , exitflag(false)
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
