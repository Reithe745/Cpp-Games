#include "Menu.h"
#include <HangMan.h>
#include <iostream>

using namespace std;

static void _windowClear() {
	system("cls");
}

void about() {
	_windowClear();
	cout << "List of games as a study project of C++ developed by Yuri Lacerda\n" << endl;
	cout << "Use this project as a template or sujest at the isues area some other game ideas";
	system("pause");
}

void mainMenu() {

	int op = 0;

	while (true) {

		_windowClear();

		cout << "Welcome\n" << endl;
		cout << "1 - Play Hang Man" << endl;
		cout << "2 - About" << endl;
		cout << "3 - Quit" << endl;
		cout << "> ";
		cin >> op;

		switch (op) {
		case 1:
			Run_HangMan();
			//play game
			return;
			break;
		case 2:
			//about
			about();
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

//main game
void Run_Menu(){
	
	mainMenu();

}
