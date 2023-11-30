#include "HangMan.h"
#include <Menu.h>
#include <iostream>
#include <time.h>
#include <string>
#include <vector>

using namespace std;

static void _windowClear() 
{
	system("cls");
}

class HM_Game_obj {

public:
	//reset the whole game
	void resetGameConstruct()
	{
		attempts = 0;
		lettersSaid = "";
		gameWord = "";
		maskedWord = "";
	}

	//single player mode
	void singlePlayerMode()
	{
		resetGameConstruct();
		deffGameWord();
		maskWord();
		PlayLoop();
		win_loose();
	}

	//multiplayer game mode
	void multyPlayerMode()
	{
		resetGameConstruct();
		manualDeffGameWord();
		maskWord();
		PlayLoop();
		win_loose();
	}

	//main single player loop
	void PlayLoop()
	{
		char letter;

		while (MAXattempts - attempts > 0 and !checkEOG()) {

			_windowClear();

			showGameStatus();
			cin >> letter;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			if (!checkTryWholeWord(letter)) {
				addLetterToList(letter);
				checkIfAttemptExist(letter);
			}
			else {
				string wholeWord;

				showTryWholeWord();
				cin >> wholeWord;

				checkIfWholeWordOK(wholeWord);
			}
		}
	}

	//see if the option of trying the whole word was selected
	bool checkTryWholeWord(char letter) {
		return letter == '1';
	}

	//find letter used on the list, if not it adds to it
	void addLetterToList(char letter) 
	{
		if (lettersSaid.find(letter) == string::npos) {
			lettersSaid += letter;
		}
	}

	//check if the letter was already used
	void checkIfAttemptExist(char letter)
	{
		int control = 0;

		for (int i = 0; i < gameWord.size(); i++) {
			if (gameWord[i] == letter) {
				cout << i << endl;
				maskedWord[i] = gameWord[i];
				control++;
			}
		}
		if (control == 0) {
			attempts++;
		}
	}

	//checking if the attempt on the whole word in ok
	void checkIfWholeWordOK(string word)
	{
		if (gameWord == word) {
			maskedWord = word;
		}
		attempts = MAXattempts;
	}

	//check if the masked word has been reveled (End Of Game)
	bool checkEOG()
	{
		return maskedWord == gameWord;
	}

	//basic text on the screen for game loop
	void showGameStatus() 
	{
		cout << "Word: " << maskedWord << " (Size: " << gameWord.size() << ")" << endl;
		cout << "Attempts left: " << MAXattempts - attempts << endl;
		cout << "Letters used: ";
		showLettersSaid();
		cout << "Your letter: ";
	}

	//show option to try the whole word
	void showTryWholeWord(){
		_windowClear();
		cout << "Take your chance!" << endl;
		cout << "Word: " << maskedWord << " (Size: " << gameWord.size() << ")" << endl;
		cout << "Your word: ";
	}

	//show all letters already used
	void showLettersSaid() {
		for (const auto i : lettersSaid) {
			cout << i << " ";
		}
		cout << endl;
	}

	//inform if game was won or lost
	void win_loose() {
		if (checkEOG()) {
			_windowClear();
			cout << "You win!!!!!" << endl;
			cout << "Word: " << gameWord << endl;
			system("pause");
		}
		else {
			_windowClear();
			cout << "Better luck next time..." << endl;
			cout << "Word: " << gameWord << endl;
			system("pause");
		}
	}

	//multiplayer word difine
	void manualDeffGameWord() {
		_windowClear();
		cout << "Say the word to be guessed: ";
		cin >> gameWord;
	}

	//mask the word
	void maskWord() {
		for (int i = 0; i < gameWord.size(); i++) {
			maskedWord += "_";
		}
	}

	//define the word for the game
	void deffGameWord() 
	{
		gameWord = words[rand() % words.size()];
	}
		

private:
	vector<string> words = { "github", "multiplayer", "unreal" };
	string lettersSaid;
	string gameWord;
	string maskedWord;
	int attempts = 0;
	int MAXattempts = 7;
};

void HM_option() {

	int op = 0;

	while (true) {

		HM_Game_obj HMgameobj;

		_windowClear();

		cout << "Welcome to Hang Man\n" << endl;
		cout << "1 - 1 Player" << endl;
		cout << "2 - 2 Players" << endl;
		cout << "3 - Main menu" << endl;
		cout << "4 - Quit" << endl;
		cout << "> ";
		cin >> op;

		switch (op) {
		case 1:
			//play game
			HMgameobj.singlePlayerMode();
			break;
		case 2:
			//multiplayer
			HMgameobj.multyPlayerMode();
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

void Run_HangMan() {

	srand((unsigned)time(NULL));

	HM_option();
}
