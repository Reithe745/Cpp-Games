#include "HangMan.h"
#include <Menu.h>
#include <iostream>

using namespace std;

static void _windowClear() {
	system("cls");
}

void HM_option() {

	int op = 0;

	while (true) {

		_windowClear();

		cout << "Welcome to Hang Man\n" << endl;
		cout << "1 - Play" << endl;
		cout << "2 - Main menu" << endl;
		cout << "3 - Quit" << endl;
		cout << "> ";
		cin >> op;

		switch (op) {
		case 1:
			//play game
			break;
		case 2:
			//menu
			Run_Menu();
			return;
			break;
		case 3:
			//quit
			return;
			break;
		default:
			break;
		}
	}
}

void Run_HangMan(){
	HM_option();
}