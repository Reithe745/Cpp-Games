#include "Hash.h"
#include "Menu.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class H_Game_Object {
	public:

};

static void _windowClear()
{
	system("cls");
}

void HashLogo()
{
	cout << "Welcome to Hash\n" << endl;
}

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
