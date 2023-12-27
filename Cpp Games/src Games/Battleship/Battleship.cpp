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

/*
1 - Menu
	Single player mode
	1.1 - Ask the position all 4 boats
	1.2 - add the boats to RealBoard 1 and variables 1
	1.3 - bot chooses it's positions in the board
	1.4 - add the boats to RealBoard 0 and variables 0
	1.5 - play game
*/

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define BLUE    "\033[34m"      /* Blue */
#define RED     "\033[31m"

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

	Boatinfo Boat4[3];
	Boatinfo Boat3[3];
	Boatinfo Boat2[3];
	Boatinfo Boat1[3];
};

class BS_Game_obj {

public:

	void singleplayerMode()
	{
		bool singlePlayerMode = true;

		initSinglePlayerConstruct();
		populateBoard();
		InitBoats();
		SetBOTBoats();
		SetPlayerBoats(1);
		maxPointForPlayer(0, singlePlayerMode);
		maxPointForPlayer(1, singlePlayerMode);
		playLoop();
	}

	void playLoop()
	{
		while (!verifyWin(1) and !verifyWin(0)) {

			_windowClear();

			showScore(0);
			showScore(1);
			showMaskedBoard(0);
			//showRealBoard(0);
			showRealBoard(1);

			singlePlayerInput();
			BotInput();
		}

		_windowClear();

		Winner();
		system("pause");
	}

	//reset all
	void initSinglePlayerConstruct()
	{
		for (int i = 0; i < 3; i++) {
			maxPointPlayer[i] = 0;
			scorePlayer[i] = 0;
		}
	}

	//check if current points are equal to max points
	bool verifyWin(int player)
	{
		return maxPointPlayer[player] == scorePlayer[player];
	}

	//set max numer of points can be made
	void maxPointForPlayer(int player, bool singleplayer)
	{
		switch (player)
		{
		case 0:

			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (RealBoard[1][i][j] != '~') {
						maxPointPlayer[0]++;
					}
				}
			}
			break;

		case 1:
			if (singleplayer == true) {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						if (RealBoard[0][i][j] != '~') {
							maxPointPlayer[1]++;
						}
					}
				}
			}
			else {
				for (int i = 0; i < 10; i++) {
					for (int j = 0; j < 10; j++) {
						if (RealBoard[2][i][j] != '~') {
							maxPointPlayer[1]++;
						}
					}
				}
			}

		default:
			break;
		}
	}

	//see if position tryed is valid for a boat
	bool checkValidPostion(int L, int C, int Rot, int BoatSize)
	{
		if (Rot == 0) {
			return C + BoatSize <= 10;
		}
		else {
			return L + BoatSize <= 10;
		}
	}

	//those 2 are linked
	//1 - make all boats apear
	void SetBOTBoats()
	{
		AutoSetBoatPosition(Boats.Boat4[0]);
		AutoSetBoatPosition(Boats.Boat3[0]);
		AutoSetBoatPosition(Boats.Boat2[0]);
		AutoSetBoatPosition(Boats.Boat1[0]);
	}

	void SetPlayerBoats(int player)
	{
		PlayerSetBoatPosition(Boats.Boat4[player], player);
		PlayerSetBoatPosition(Boats.Boat3[player], player);
		PlayerSetBoatPosition(Boats.Boat2[player], player);
		PlayerSetBoatPosition(Boats.Boat1[player], player);
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
				RealBoard[0][L][C] = boat.nameNumber;

				C++;
			}
			else {

				boat.Line[i] = L;
				boat.Column[i] = C;
				RealBoard[0][L][C] = boat.nameNumber;

				L++;
			}
		}
	}

	//player input to set boats in the board
	void PlayerSetBoatPosition(Boatinfo& boat, int player)
	{
		int L = 10;
		int C = 10;
		int Rotation = 0; // 0 Vertical, 1 Horizontal

		_windowClear();

		while (!checkValidPostion(L, C, Rotation, boat.size)) {
			
			cout << "Player " << player << ", choose the location of boat" << "\n";
			cout << "Boat size -> " << boat.size << "\n\n";

			showRealBoard(player);

			cout << "Choose your boat LINE position: ";
			cin >> L;
			cout << "Choose your boat COLUMN position: ";
			cin >> C;
			cout << "0 - Vertical\n1 - Horizontal\nChoose your boat ROTATION position: ";
			cin >> Rotation;
		}

		for (int i = 0; i < boat.size; i++) {
			if (Rotation == 0) {

				boat.Column[i] = C;
				boat.Line[i] = L;
				RealBoard[player][L][C] = boat.nameNumber;

				C++;
			}
			else {

				boat.Line[i] = L;
				boat.Column[i] = C;
				RealBoard[player][L][C] = boat.nameNumber;

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
	void InitBoats()
	{
		for (int i = 0; i < 3; i++) {
			Boats.Boat1[i].Line = new int[2];
			Boats.Boat2[i].Line = new int[3];
			Boats.Boat3[i].Line = new int[3];
			Boats.Boat4[i].Line = new int[4];

			Boats.Boat1[i].Column = new int[2];
			Boats.Boat2[i].Column = new int[3];
			Boats.Boat3[i].Column = new int[3];
			Boats.Boat4[i].Column = new int[4];

			Boats.Boat1[i].size = 2;
			Boats.Boat2[i].size = 3;
			Boats.Boat3[i].size = 3;
			Boats.Boat4[i].size = 4;

			Boats.Boat1[i].nameNumber = '1';
			Boats.Boat2[i].nameNumber = '2';
			Boats.Boat3[i].nameNumber = '3';
			Boats.Boat4[i].nameNumber = '4';
		}
	}

	//get a line and column from the player
	void singlePlayerInput()
	{
		int line = 0, column = 0;

		cout << "Bomb Line: ";
		cin >> line;
		cout << "Bomb Column: ";
		cin >> column;

		if (CheckHit(line, column, 0) and MaskedBoard[0][line][column] == '*') {
			scorePlayer[1]++;
		}

		MaskedBoard[0][line][column] = RealBoard[0][line][column];		//TODO - Change the showing board
	}

	void BotInput()
	{
		int line = RandVal(10);
		int column = RandVal(10);

		while (MaskedBoard[1][line][column] != '*') {
			line = RandVal(10);
			column = RandVal(10);
		}

		if (CheckHit(line, column, 1) and MaskedBoard[1][line][column] == '*') {
			scorePlayer[0]++;
		}

		MaskedBoard[1][line][column] = RealBoard[1][line][column];		//TODO - Change the showing board
		RealBoard[1][line][column] = '*';
	}

	//check if the player hit water of boat
	bool CheckHit(int L, int C, int player)
	{
		return RealBoard[player][L][C] != '~';
	}

	//show the current P1 score
	void showScore(int player) {
		
		string name;

		if (player == 0) name = "BOT";
		else name = "Player " + to_string(player);
		
		cout << name << " points: " << scorePlayer[player] << endl;
	}

	//show the hole board
	void showMaskedBoard(int player)
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
				if (MaskedBoard[player][i][j] == '~') cout << BLUE << " " << MaskedBoard[player][i][j] << RESET;
				else cout << " " << MaskedBoard[player][i][j];
			}
			cout << endl;
		}
	}

	//DEBUG -----------------------------------------------
	void showRealBoard(int player)
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
				if (RealBoard[player][i][j] == '*') cout << RED << " " << RealBoard[player][i][j] << RESET;
				else cout << " " << RealBoard[player][i][j];
			}
			cout << endl;
		}
	}

	//populate board with a "empty" char
	void populateBoard()
	{
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				RealBoard[0][i][j] = '~';
				RealBoard[1][i][j] = '~';
				RealBoard[2][i][j] = '~';
				MaskedBoard[0][i][j] = '*';
				MaskedBoard[1][i][j] = '*';
				MaskedBoard[2][i][j] = '*';
			}
		}
	}

	void Winner() {
		if (maxPointPlayer[0] == scorePlayer[0]) cout << "The bot has won!!!!" << "\n";
		else if (maxPointPlayer[1] == scorePlayer[1]) cout << "Player 1 has won!!!!" << "\n";
		else cout << "Player 2 has won!!!!" << "\n";
	}

private:

	BoatList Boats;
	char RealBoard[3][10][10];		//0 - bot ; 1 - P1 ; 2 - P2
	char MaskedBoard[3][10][10];	//0 - bot ; 1 - P1 ; 2 - P2
	int maxPointPlayer[3];			//0 - bot ; 1 - P1 ; 2 - P2
	int scorePlayer[3];				//0 - bot ; 1 - P1 ; 2 - P2
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