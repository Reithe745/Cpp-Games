/*
  ____          _    _    _             _      _
 |  _ \        | |  | |  | |           | |    (_)
 | |_) |  __ _ | |_ | |_ | |  ___  ___ | |__   _  _ __
 |  _ <  / _` || __|| __|| | / _ \/ __|| '_ \ | || '_ \
 | |_) || (_| || |_ | |_ | ||  __/\__ \| | | || || |_) |
 |____/  \__,_| \__| \__||_| \___||___/|_| |_||_|| .__/
												 | |
												 |_|
*/

#include "Battleship.h"
#include <Menu.h>
#include <iostream>
#include <string>
#include <time.h>

using namespace std;

static void _windowClear()
{
	system("cls");
}

struct BoatPosition {
	int Line;
	int Column;
	int size;
};

struct BoatList {
	BoatPosition Boat4_4[4];
	BoatPosition Boat3_3[3];
	BoatPosition Boat2_3[3];
	BoatPosition Boat1_2[2];
};

class BS_Game_obj {

public:

	void singleplayerMode()
	{
		populateBoard();
		AutoSetBoatPosition();
		playLoop();
	}

	void playLoop()
	{
		while (true) {

			_windowClear();

			showMaskedBoard();
			XY();
		}
	}

	//bot seting boat opsition 
	void AutoSetBoatPosition()
	{
		for (int i = 0; i < 5; i++) {
			int L = rand() % 10;
			int C = rand() % 10;

			if (RealBoard[L][C] == 'A') {
				RealBoard[L][C] = '*';
			}
			else {
				i--;
			}
		}
	}

	//get a line and column from the player
	void XY()
	{
		int line, column;

		cout << "Bomb Line: ";
		cin >> line;
		cout << "Bomb Column: ";
		cin >> column;

		if (!CheckIfSpotWasBombed(line, column)) {
			MaskedBoard[line][column] = RealBoard[line][column];
		}
	}

	//unmask the spot chosen
	bool CheckIfSpotWasBombed(int i, int j)
	{
		return MaskedBoard[i][j] == RealBoard[i][j];
	}

	//show the hole board
	void showMaskedBoard()
	{
		cout << "  ";
		for (int k = 0; k < 10; k++) {
			cout << " " << k;
		}
		cout << endl;

		for (int i = 0; i < 10; i++) {
			cout << i << " ";
			for (int j = 0; j < 10; j++) {
				cout << " " << RealBoard[i][j];			//TODO change the "realboard" to "maskedboard"
			}
			cout << endl;
		}
	}

	//populate board with a "empty" char
	void populateBoard()
	{
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				RealBoard[i][j] = 'A';
				MaskedBoard[i][j] = '*';
			}
		}
	}

private:

	BoatList * Boats;
	char RealBoard[10][10];
	char MaskedBoard[10][10];
	char PlayerBoard[10][10];

};

void BattleshipLogo()
{
	cout << "Welcome to Battleship\n" << endl;
}

void BS_option() {
	
	int op = 0;

	while (true) {

		BS_Game_obj BSgameobj;

		_windowClear();

		BattleshipLogo();

		cout << "1 - Single Player" << endl;
		cout << "2 - Multi Player" << endl;
		cout << "3 - Main menu" << endl;
		cout << "4 - Quit" << endl;
		cout << "> ";
		cin >> op;

		switch (op) {
		case 1:
			//play game
			BSgameobj.singleplayerMode();
			break;
		case 2:
			//multiplayer
			break;
		case 3:
			//menu
			Run_Menu();
			return;
			break;
		case 4:
			//quit
			return;
			break;
		default:
			break;
		}
	}
}

void Run_Battleship()
{
	srand((unsigned) time(NULL));
	BS_option();
}
