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

struct BoatList {

	struct Boatinfo {
		int Line;
		int Column;
		int size;
	};

	Boatinfo Boat4[4];
	Boatinfo Boat3[3];
	Boatinfo Boat2[3];
	Boatinfo Boat1[2];
};

class BS_Game_obj {

public:

	void singleplayerMode()
	{
		populateBoard();
		PopulateBoats();
		AutoSetBoatPosition();
		playLoop();
	}

	void playLoop()
	{
		while (true) {

			_windowClear();

			showMaskedBoard();
			XY();
		}
	}

	//bot seting boat opsition
	void AutoSetBoatPosition()
	{
		for (int i = 0; i < 5; i++) {
			int L = RandVal(10);
			int C = RandVal(10);
			int Roation = RandVal(2); // 0 Vertical, 1 Horizontal

			if (RealBoard[L][C] == '~') {
				RealBoard[L][C] = '*';
			}
			else {
				i--;
			}
		}
	}

	int RandVal(int maxValue) {
		return rand() % maxValue;
	}

	//give at the start of the game
	void PopulateBoats() {
		Boats.Boat1->size = 2;
		Boats.Boat2->size = 3;
		Boats.Boat3->size = 3;
		Boats.Boat4->size = 4;
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
				cout << " " << MaskedBoard[i][j];			//TODO change the "realboard" to "maskedboard"
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