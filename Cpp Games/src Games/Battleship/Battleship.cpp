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
	int nameNumber;
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
		populateBoard();
		PopulateBoats();
		AutoSetBoatPosition(Boats.Boat1);
		playLoop();
	}

	void playLoop()
	{
		while (true) {
			_windowClear();
			cout << Boats.Boat1.Line[0] << endl; // debug
			showMaskedBoard();
			system("pause");
			singleplayerMode();
			//XY();
		}
	}

	bool checkValidPostion(int L, int C, int Rot, int BoatSize) {
		if (Rot == 0) {
			return C + BoatSize < 10;
		}
		else {
			return L + BoatSize < 10;
		}
	}

	//bot seting boat opsition
	void AutoSetBoatPosition(Boatinfo boat)
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
				boat.Column[i] = C - i;
				this->RealBoard[L][C - i] = 'A';
			}
			else {
				boat.Line[i] = L - i;
				this->RealBoard[L - i][C] = 'N';
			}
			//Need to fix bug, on the autosetboatlocation, it can appear at the end of the line and go to the other
		}

		//for (int i = 0; i < 5; i++) {
		//	int L = RandVal(10);
		//	int C = RandVal(10);
		//	int Roation = RandVal(2); // 0 Vertical, 1 Horizontal

		//	if (RealBoard[L][C] == '~') {
		//		RealBoard[L][C] = '*';
		//	}
		//	else {
		//		i--;
		//	}
		//}
	}

	int RandVal(int maxValue) {
		return rand() % maxValue;
	}

	//give at the start of the game
	void PopulateBoats() {
		Boats.Boat1.Line = Boats.Boat1.Column = new int[2];
		Boats.Boat2.Line = Boats.Boat2.Column = new int[3];
		Boats.Boat3.Line = Boats.Boat3.Column = new int[3];
		Boats.Boat4.Line = Boats.Boat4.Column = new int[4];

		Boats.Boat1.size = 2;
		Boats.Boat2.size = 3;
		Boats.Boat3.size = 3;
		Boats.Boat4.size = 4;

		Boats.Boat1.nameNumber = 1;
		Boats.Boat2.nameNumber = 2;
		Boats.Boat3.nameNumber = 3;
		Boats.Boat4.nameNumber = 4;
	}

	//get a line and column from the player
	void XY()
	{
		int line, column;

		cout << "Bomb Line: ";
		cin >> line;
		cout << "Bomb Column: ";
		cin >> column;

		if (!CheckIfSpotWasBombed(line, column)) {
			MaskedBoard[line][column] = RealBoard[line][column];
		}
	}

	//unmask the spot chosen
	bool CheckIfSpotWasBombed(int i, int j)
	{
		return MaskedBoard[i][j] == RealBoard[i][j];
	}

	//show the hole board
	void showMaskedBoard()
	{
		cout << "  ";
		for (int k = 0; k < 10; k++) {
			cout << " " << k;
		}
		cout << endl;

		for (int i = 0; i < 10; i++) {
			cout << i << " ";
			for (int j = 0; j < 10; j++) {
				cout << " " << RealBoard[i][j];			//TODO change the "realboard" to "maskedboard"
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
	char PlayerBoard[10][10];

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

/*
const int tamanhoTabuleiro = 10;

struct Barco {
	int tamanho;
	char direcao; // 'H' para horizontal, 'V' para vertical
	int linha;
	int coluna;
};

class BatalhaNaval {
public:
	BatalhaNaval() {
		inicializarTabuleiro();
		posicionarBarcos();
		exibirTabuleiro();
	}

private:
	char tabuleiro[tamanhoTabuleiro][tamanhoTabuleiro];

	void inicializarTabuleiro() {
		for (int i = 0; i < tamanhoTabuleiro; ++i) {
			for (int j = 0; j < tamanhoTabuleiro; ++j) {
				tabuleiro[i][j] = '~'; // '~' representa água
			}
		}
	}

	bool posicaoValida(int linha, int coluna, int tamanho, char direcao) {
		if (direcao == 'H') {
			return coluna + tamanho <= tamanhoTabuleiro;
		} else if (direcao == 'V') {
			return linha + tamanho <= tamanhoTabuleiro;
		}
		return false;
	}

	void posicionarBarco(Barco& barco) {
		do {
			barco.linha = rand() % tamanhoTabuleiro;
			barco.coluna = rand() % tamanhoTabuleiro;
			barco.direcao = (rand() % 2 == 0) ? 'H' : 'V';
		} while (!posicaoValida(barco.linha, barco.coluna, barco.tamanho, barco.direcao));

		for (int i = 0; i < barco.tamanho; ++i) {
			if (barco.direcao == 'H') {
				tabuleiro[barco.linha][barco.coluna + i] = 'B'; // 'B' representa um pedaço de barco
			} else if (barco.direcao == 'V') {
				tabuleiro[barco.linha + i][barco.coluna] = 'B';
			}
		}
	}

	void posicionarBarcos() {
		Barco barco2 = {2, ' ', 0, 0};
		Barco barco3 = {3, ' ', 0, 0};
		Barco barco4 = {4, ' ', 0, 0};

		posicionarBarco(barco2);
		posicionarBarco(barco3);
		posicionarBarco(barco4);
	}
*/