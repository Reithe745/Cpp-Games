#include "Template.h"						//CHANGE TO THE FINAL NAME OF THE ".h" FILE
#include <Menu.h>
#include <iostream>

using namespace std;

//BASIC COMMAND FOR CLEANING THE CMD WINDOW
static void _windowClear()
{
	system("cls");
}

//CLASS WHERE INFORMATION AND MECHANICS WILL BE STORED AND DEVELOPED
class GAME_Game_obj {						// CHANGE FOR THE FINAL NAME OF THE FILE

public:

private:

};

//GAME LOGO
void GameLogo()								// CHANGE FOR THE FINAL NAME OF THE FILE
{
	cout << "Welcome to ...\n" << endl;		// CHANGE FOR THE FINAL NAME OF THE FILE
}

//GAME MENU
void GAME_option()							// CHANGE FOR THE FINAL NAME OF THE FILE
{
	int op = 0;

	GAME_Game_obj GAMEgameobj;				// CHANGE FOR THE FINAL NAME OF THE FILE

	GameLogo();								// CHANGE FOR THE FINAL NAME OF THE FILE

	while (true){

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

//MAIN FUNCTION
void Run_GAME()								// CHANGE FOR THE FINAL NAME OF THE FILE
{
	GAME_option();							// CHANGE FOR THE FINAL NAME OF THE FILE
}
