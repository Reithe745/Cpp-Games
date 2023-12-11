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

struct Boatinfo {
	int * Line;
	int * Column;
	int size;
	char nameNumber;
};

struct BoatList {

	Boatinfo Boat4;
	Boatinfo Boat3;
	Boatinfo Boat2;
	Boatinfo Boat1;
};

class BS_Game_obj {

public:

	void singleplayerMode()
	{
		initSinglePlayerConstruct();
		populateBoard();
		InitBoats();
		AutoSetAllBoats();
		maxPointForP1();
		// future: maxPountForBOT();
		playLoop();
	}

	void playLoop()
	{
		while (!verifyWin()) {

			_windowClear();

			cout << maxPointP1 << "\n" << verifyWin();

			showScore();
			showMaskedBoard();
			showRealBoard();

			singlePlayerInput();
		}
	}

	//reset all
	void initSinglePlayerConstruct()
	{
		scoreP1 = 0;
		maxPointP1 = 0;
		maxPointP2 = 0;
		maxPointBOT = 0;
	}

	//check if current points are equal to max points
	bool verifyWin()
	{
		return maxPointP1 == scoreP1;
	}

	//set max numer of points can be made
	void maxPointForP1()
	{
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (RealBoard[i][j] != '~') {
					maxPointP1++;
				}
			}
		}
	}

	//see if position tryed is valid for a boat
	bool checkValidPostion(int L, int C, int Rot, int BoatSize)
	{
		if (Rot == 0) {
			return C + BoatSize < 10;
		}
		else {
			return L + BoatSize < 10;
		}
	}

	//those 2 are linked
	//1 - make all boats apear
	void AutoSetAllBoats()
	{
		AutoSetBoatPosition(Boats.Boat4);
		AutoSetBoatPosition(Boats.Boat3);
		AutoSetBoatPosition(Boats.Boat2);
		AutoSetBoatPosition(Boats.Boat1);
	}

	//2 - bot seting boat opsition
	void AutoSetBoatPosition(Boatinfo &boat)
	{
		int L = 10;
		int C = 10;
		int Rotation = 0; // 0 Vertical, 1 Horizontal

		while (!checkValidPostion(L, C, Rotation, boat.size)) {
			L = RandVal(10);
			C = RandVal(10);
			Rotation = RandVal(2); // 0 Vertical, 1 Horizontal
		}

		for (int i = 0; i < boat.size; i++) {
			if (Rotation == 0) {

				boat.Column[i] = C;
				boat.Line[i] = L;
				RealBoard[L][C] = boat.nameNumber;

				C++;
			}
			else {

				boat.Line[i] = L;
				boat.Column[i] = C;
				RealBoard[L][C] = boat.nameNumber;

				L++;
			}
		}
	}

	//get a random value in a range
	int RandVal(int maxValue)
	{
		return rand() % maxValue;
	}

	//give at the start of the game
	void InitBoats() {
		Boats.Boat1.Line = new int[2];
		Boats.Boat2.Line = new int[3];
		Boats.Boat3.Line = new int[3];
		Boats.Boat4.Line = new int[4];

		Boats.Boat1.Column = new int[2];
		Boats.Boat2.Column = new int[3];
		Boats.Boat3.Column = new int[3];
		Boats.Boat4.Column = new int[4];

		Boats.Boat1.size = 2;
		Boats.Boat2.size = 3;
		Boats.Boat3.size = 3;
		Boats.Boat4.size = 4;

		Boats.Boat1.nameNumber = '1';
		Boats.Boat2.nameNumber = '2';
		Boats.Boat3.nameNumber = '3';
		Boats.Boat4.nameNumber = '4';
	}

	//get a line and column from the player
	void singlePlayerInput()
	{
		int line = 0, column = 0;

		cout << "Bomb Line: ";
		cin >> line;
		cout << "Bomb Column: ";
		cin >> column;

		if (CheckHit(line, column) and MaskedBoard[line][column] == '*') {
			scoreP1++;
		}

		MaskedBoard[line][column] = RealBoard[line][column];
	}

	//check if the player hit water of boat
	bool CheckHit(int L, int C)
	{
		return RealBoard[L][C] != '~';
	}

	//show the current P1 score
	void showScore() {
		cout << "Points: " << scoreP1 << endl << endl;
	}

	//show the hole board
	void showMaskedBoard()
	{
		cout << "  ";
		for (int k = 0; k < 10; k++) {
			cout << " " << k;
		}
		
		cout << endl;
		cout << "   | | | | | | | | | |\n";

		for (int i = 0; i < 10; i++) {
			cout << i << " ";
			for (int j = 0; j < 10; j++) {
				cout << " " << MaskedBoard[i][j];		//TODO change the "realboard" to "maskedboard"
			}
			cout << endl;
		}
	}

	//DEBUG -----------------------------------------------
	void showRealBoard()
	{
		cout << "  ";
		for (int k = 0; k < 10; k++) {
			cout << " " << k;
		}

		cout << endl;
		cout << "   | | | | | | | | | |\n";

		for (int i = 0; i < 10; i++) {
			cout << i << " ";
			for (int j = 0; j < 10; j++) {
				cout << " " << RealBoard[i][j];		//TODO change the "realboard" to "maskedboard"
			}
			cout << endl;
		}
	}

	//populate board with a "empty" char
	void populateBoard()
	{
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				RealBoard[i][j] = '~';
				MaskedBoard[i][j] = '*';
			}
		}
	}

private:

	BoatList Boats;
	char RealBoard[10][10];
	char MaskedBoard[10][10];
	int maxPointP1;
	int maxPointP2;
	int maxPointBOT;
	int scoreP1;
	//char PlayerBoard[10][10];

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