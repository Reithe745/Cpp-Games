#include "HangMan.h"
#include <iostream>

using namespace std;

void _windowClear() {

	system("cls");

}

//main game
void Run_HangMan(){
	
	int op = 0;

	while (op < 1 or op > 3) {
		cout << "Welcome to Hang Man\n" << endl;
		cout << "1 - Play" << endl;
		cout << "2 - About" << endl;
		cout << "3 - Quit" << endl;
		cout << "> ";
		cin >> op;

		switch (op) {
			case 1:
				//play game
				break;
			case 2:
				//credits
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
