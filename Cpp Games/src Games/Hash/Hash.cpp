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
	
	void SinglePLayerMode() {

		PopulateTableDEBUG();
		PrintTable();

		system("pause");
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

	void PopulateTableDEBUG()
	{
		for (int i = 0; i <= 2; i++) {
			for (int j = 0; j <= 2; j++) {
				Table[i][j] = '~';
			}
		}
	}

private:
	char Table[3][3];			// game table


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
			HGameObject.SinglePLayerMode();
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

void Run_Hash()
{
	H_option();
}
