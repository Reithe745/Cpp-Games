/*
  __  __         _          __  __
 |  \/  |       (_)        |  \/  |
 | \  / |  __ _  _  _ __   | \  / |  ___  _ __   _   _
 | |\/| | / _` || || '_ \  | |\/| | / _ \| '_ \ | | | |
 | |  | || (_| || || | | | | |  | ||  __/| | | || |_| |
 |_|  |_| \__,_||_||_| |_| |_|  |_| \___||_| |_| \__,_|

*/

#include "Menu.h"
#include <Hangman/HangMan.h>
#include <Battleship/Battleship.h>
#include <Hash/Hash.h>
#include <iostream>

using namespace std;

static void _windowClear() {
	system("cls");
}

void about() {
	_windowClear();
	cout << "List of games as a study project of C++ developed by Yuri Lacerda\n" << endl;
	cout << "Use this project as a template or sujest at the isues area some other game ideas" << endl;
	system("pause");
}

void mainMenu() {

	int op = 0;

	while (true) {

		_windowClear();

		cout << "Welcome to the C++ game hub\n" << endl;
		cout << "1: Play Hang Man" << endl;
		cout << "2: Play Battleship" << endl;
		cout << "3: Hash" << endl;
		cout << "4: About" << endl;
		cout << "5: Quit" << endl;
		cout << "> ";
		cin >> op;

		switch (op) {
		case 1:
			//play game
			Run_HangMan();
			return;
			break;
		case 2:
			//battleship
			Run_Battleship();
			return;
			break;
		case 3:
			//hash
			Run_Hash();
			return;
			break;
		case 4:
			//about
			about();
			break;
		case 5:
			//quit
			return;
			break;
		default:
			break;
		}
	}
}

//main game
void Run_Menu(){
	
	mainMenu();

}
