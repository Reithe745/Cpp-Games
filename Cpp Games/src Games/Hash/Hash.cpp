#include "Hash.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Clear window
static void _windowClear()
{
	system("cls");
}

// Game class
class H_Game_Object {

public:
	
	void MultiplayerMode() {

		PopulateTableDEBUG();
		
		system("cls");

		while (plays < 9) {

			cout << "Player X" << "\n\n";

			PrintTable();

			while (!ChooseSpotPlayer(Player1Symbol));

			plays++;

			if ((VerifyWin(Player1Symbol, BotSymbol)) or plays == 9) break;

			system("cls");

			cout << "Player O" << "\n";

			PrintTable();

			while (!ChooseSpotPlayer(Player2Symbol));

			plays++;

			if ((VerifyWin(Player1Symbol, BotSymbol)) or plays == 9) break;

			system("cls");
		}

		system("cls");

		PrintTable();

		if (VerifyWin(Player1Symbol, BotSymbol)) {
			cout << "\n" << "The winner is " << WinnerSimbol << ", Congrats!!!" << "\n";
			system("pause");
		}
		else {
			cout << "\n" << "DRAW..." << "\n";
			system("pause");
		}
		plays = 0;
	}

	void PrintTable() 
	{
		for (int i = 0; i <= 2; i++) {
			for (int j = 0; j <= 2; j++) {
				
				cout << Table[i][j];

				if (j != 2) cout << "|";
			}
			
			if (i != 2) cout << "\n" << "-----" << "\n";
			
			else cout << "\n";
		}
	}

	bool ChooseSpotPlayer(char pS) 
	{
		int Row = -1, Column = -1;
		
		cout << "Choose a ROW from 1 to 3" << "\n";
		while (Row < 0 or Row > 3) cin >> Row;

		cout << "Choose a COLUMN from 1 to 3" << "\n";
		while (Column < 0 or Column > 3) cin >> Column;

		if (ValidPosition(Row - 1, Column - 1)) {

			Table[Row - 1][Column - 1] = pS;
			return true;
		}
		else {

			cout << "This position is taken" << "\n";
			return false;
		}
	}

	bool ValidPosition(int R, int C)
	{
		return Table[R][C] != 'X' and Table[R][C] != 'O';
	}

	bool VerifyWin(char p1S, char p2S)
	{
		for (int i = 0; i <= 2; i++) {
			if (Table[i][0] == p1S && Table[i][1] == p1S && Table[i][2] == p1S) {
				WinnerSimbol = 'X';
				return true;
			}
			if (Table[i][0] == p2S && Table[i][1] == p2S && Table[i][2] == p2S) {
				WinnerSimbol = 'O';
				return true;
			}
			if (Table[0][i] == p1S && Table[1][i] == p1S && Table[2][i] == p1S) {
				WinnerSimbol = 'X';
				return true;
			} 
			if (Table[0][i] == p2S && Table[1][i] == p2S && Table[2][i] == p2S) {
				WinnerSimbol = 'O';
				return true;
			}
		}
		if (Table[0][0] == p1S && Table[1][1] == p1S && Table[2][2] == p1S) {
			WinnerSimbol = 'X';
			return true;
		}
		if (Table[0][0] == p2S && Table[1][1] == p2S && Table[2][2] == p2S) {
			WinnerSimbol = 'O';
			return true;
		}
		if (Table[2][0] == p1S && Table[1][1] == p1S && Table[0][2] == p1S) {
			WinnerSimbol = 'X';
			return true;
		}
		if (Table[2][0] == p2S && Table[1][1] == p2S && Table[0][2] == p2S) {
			WinnerSimbol = 'O';
			return true;
		}

		return false;
	}

	void PopulateTableDEBUG()
	{
		for (int i = 0; i <= 2; i++) {
			for (int j = 0; j <= 2; j++) {
				Table[i][j] = ' ';
			}
		}
	}

private:
	char Table[3][3];			// game table
	char Player1Symbol = 'X';
	char Player2Symbol = 'O';
	char BotSymbol = 'O';
	char WinnerSimbol;
	int plays = 0;

};

// Logo
void HashLogo()
{
	cout << "Welcome to Hash\n" << endl;
}

// Hash menu
void H_option()
{
	int op = 0;

	H_Game_Object HGameObject;

	while (true) {

		_windowClear();

		HashLogo();

		cout << "1 - Single Player" << endl;
		cout << "2 - Multi Player" << endl;
		cout << "3 - Main menu" << endl;
		cout << "4 - Quit" << endl;
		cout << "> ";
		cin >> op;

		switch (op) {
		case 1:
			//play game
			break;
		case 2:
			//multiplayer
			HGameObject.MultiplayerMode();
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

void Run_Hash()
{
	H_option();
}
