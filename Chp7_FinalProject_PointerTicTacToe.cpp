// Chp7_FinalProject_PointerTicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;
const int MAX = 9;
const char open[MAX] = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
void fillBoard(char* const array);
void display(const char* const array);
void rules();
int getPlayers();
void play1(char* const array);
bool getFirst();
char getChar(string);
int getPlayerMove(string);
bool isValidMove(const char* const array, int);
bool winner(const char* const array);
bool checkWin(const char* const array);
bool computerLogic(char * const aray, int, char, char);
void play2(char* const array);
int main()
{
	cout << "\t\t\t\t\tTIC TAC TOE POINTERS\n";
	char master[MAX] = {};
	char* pArray = master;
	fillBoard(master);
	rules();
	display(master);
	int p = getPlayers();
	if (p == 1) {
		play1(master);
	}
	else {
		play2(master);
	}
	system("PAUSE");
    return 0;
}

static void fillBoard(char* const arr) {
	int counter = 0;
	for (int i = 1; i < MAX + 1; i++) {
		arr[counter] = '0' + i;
		counter++;
	}
}
static inline void display(const char* const m) {
	cout << "\n BOARD\n";
	int counter = 0;
	char a = 196;
	for (int i = 0; i < 3; i++) {
		cout << a << a << a << a << a << a << a;
		cout << "\n";
		cout << "|"; 
		for (int j = 0; j < 3; j++) {
			//cout << "|";
			cout << m[counter];
			counter++;
			cout << "|";
		}
		cout << endl;
	}
	cout << a << a << a << a << a << a << a;
	cout << "\n";
}

static void rules() {
	cout << "\nHi. Welcome to the Tic-Tac-Toe game. In this game, the goal is to align three of your characters either diagonally, in a straight line horizontally, or\n";
	cout << " in a straight line vertically. You can choose whether or not you want to play against the computer, play against a friend, or \n";
	cout << "have the computer play against itself. You will also choose whether you want your characters to be 'X' or 'O', but which player goes first will be deicded by an RNG.\n";
	cout << "Here is how the game board looks: \n";
}

static int getPlayers() {
	bool key = false;
	string input;
	while (key == false) {
		//int input;
		cout << "\nHow many players will be playing? ";
		cin >> input;
		if (input.size() > 1) {
			cout << "\nYour input is too long.\n";
			continue;
		}
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nYour input is bad.\n";
			continue;
		}
		if (input != "1" && input != "2") {
			cout << "\nPlease enter number between 1 and 2.\n";
			continue;
		}
		key = true;
	}
	int i = stoi(input);
	return i;
}

static bool getFirst() {
	cout << "\nWe will flip a coin to see who gets to move first.";
	string s;
	int counter = 0;
	do {
		if (counter >= 1) {
			cout << "\nEnter h for heads or t for tails.";
		}
		cout << "\nPlayer 1, heads or tails? ";
		cin >> s;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nYour input is bad.\n";
			continue;
		}
		if (s.size() > 1) {
			cout << "\nYour input is too long. Enter h for heads or t for tails.";
			continue;
		}
		counter++;
	} while (s != "h" && s != "t");
	srand(static_cast<unsigned int>(time(0)));
	int randoms = rand();
	int c = (randoms % 2) + 1;
	if ((c == 1 && s == "h") || (c == 2 && s == "t")) {
		return true;
	}
	else {
		return false;
	}
}

static inline char getChar(string g) {
	string s;
	int counter = 0;
	do {
		if (counter >= 1) {
			cout << "\nEnter an 'X' or 'O' to continue.";
		}
		cout << "\n" << g << ", please enter 'X' or 'O' as your piece: ";
		cin >> s;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nYour input is bad.\n";
			continue;
		}
		if (s.size() > 1) {
			cout << "\nYour input is too long.\n";
			continue;
		}
		counter++;
	} while (s != "X" && s != "O");
	const char *cstr = s.c_str();
	return *cstr;
}

static inline int getPlayerMove(string y) {
	string p;
	int counter = 0;
	do {
		if (counter >= 1) {
			cout << "\nEnter a number between 1-9 to continue.";
		}
		cout << "\n" << y << ", enter a number between 1-9: ";
		cin >> p;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nYour input is bad.\n";
			continue;
		}
		if (p.size() > 1) {
			cout << "\nYour input is too long.\n";
			continue;
		}
		counter++;
	} while (p != "1" && p != "2" && p != "3" && p != "4" && p != "5" && p != "6" && p != "7" && p != "8" && p != "9");
	int h = stoi(p);
	return h;
}

static inline bool isValidMove(const char* const v, int b) {
	if (v[b - 1] == 'X' || v[b - 1] == 'O') {
		return false;
	}
	else {
		return true;
	}
}
static inline bool checkWin(const char* const g) {
	int winners[8][3] = { {1, 2, 3},
	{1, 5, 9},
	{1, 4, 7},
	{7, 5, 3},
	{7, 8, 9},
	{2, 5, 8},
	{3, 6, 9},
	{4, 5, 6} };

	for (int i = 0; i < 8; i++) {
		int xCounter = 0;
		int oCounter = 0;
		for (int j = 0; j < 3; j++) {
			int k = winners[i][j];
			if (g[k - 1] == 'X') {
				xCounter++;
				if (xCounter >= 3) {
					return true;
				}
			}
			if (g[k - 1] == 'O') {
				oCounter++;
				if (oCounter >= 3) {
					return true;
				}
			}
		}
	}
	return false;
}

static bool computerLogic(char* const w, int x, char pc, char human) {
	//make this a global 2d array or pass it into the functions from main as a pointer.
	int winners[8][3] = { { 1, 2, 3 },
	{ 1, 5, 9 },
	{ 1, 4, 7 },
	{ 7, 5, 3 },
	{ 7, 8, 9 },
	{ 2, 5, 8 },
	{ 3, 6, 9 },
	{ 4, 5, 6 } };
	if (x >= 3) {
		for (int i = 0; i < 8; i++) {
			int esc = 0;
			int rCounter = 0;
			for (int j = 0; j < 3; j++) {
				rCounter++;
				int y = winners[i][j];
				cout << "\nHere is y: " << y << endl;
				if (w[y - 1] == pc) {
					cout << "\nI'm adding to your esc total";
					esc++;
				}
				if (w[y - 1] == human) {
					cout << "\nI saw your piece so i'm breaking from this winning permutation.";
					break;
				}
				if (esc == 2 && rCounter == 3) {
					cout << "\nI'm about to win!";
					for (int d = 0; d < 3; d++) {
						int test = winners[i][d];
						if (w[test - 1] != pc) {
							w[test - 1] = pc;
							return true;
						}
					}
				}
			}
		}
		cout << "\nDoesn't look like I can win right now. Let's check to see if i can block you from winning.";
		for (int i = 0; i < 8; i++) {
			int esc = 0;
			for (int j = 0; j < 3; j++) {
				int y = winners[i][j];
				if (w[y - 1] == human) {
					esc++;
				}
				if (w[y - 1] == pc) {
					cout << "\nI saw my own piece so i'm breaking from this winning permutation.";
					break;
				}
				if (esc == 2) {
					cout << "\nYou're about to win, but i'm going to block you.";
					for (int d = 0; d < 3; d++) {
						int test = winners[i][d];
						if (w[test - 1] != human) {
							w[test - 1] = pc;
							return true;
						}
					}
				}
			}
		}
	}
	cout << "\nDoesn't look like anyone can win right now. Let's get on with the game.\n";
	//Use iterator objects when editing some of the code.
	int bestSpots[MAX] = { 5, 1, 3, 7, 9, 2, 4, 6, 8 };
	for (int i = 0; i < MAX; i++) {
		int u = bestSpots[i];
		if (w[u - 1] != pc && w[u - 1] != human) {
			w[u - 1] = pc;
			return true;
		}
	}
	return true;
}
static void play1(char* const v) {
	char f;
	char s;
	bool r;
	bool hasWon = false;
	r = getFirst();
	if (r == true) {
		int z = 0;
		cout << "\nPlayer 1 will move first.";
		f = getChar("Player 1");
		if (f == 'X') {
			s = 'O';
		}
		else {
			s = 'X';
		}
		while (hasWon == false) {
			int u;
			u = getPlayerMove("Player 1");
			cout << "\nYou input was accepted, now lets see if its a valid move.";
			bool g = isValidMove(v, u);
			if (g == false) {
				cout << "\nYou tried moving to a spot that has already been taken. Try again.";
				continue;
			}
			v[u - 1] = f;
			z++;
			cout << "\n";
			display(v);
			if (z >= 9) {
				cout << "\nIt was a draw! Press y is you would like to play again: ";
				string again;
				cin >> again;
				if (again == "Y" || again == "y") {
					main();
				}
				else {
					cout << "\nCya!";
					exit(0);
				}
			}
			if (z >= 3) {
				bool w = checkWin(v);
				if (w == true) {
					cout << "\nCongratulations! Player 1 has won in " << z << " turns!\n";
					cout << "\nPress y is you would like to play again: ";
					string again;
					cin >> again;
					if (again == "Y" || again == "y") {
						main();
					}
					else {
						cout << "\nCya!";
						exit(0);
					}
				}
			}
			cout << "\nNow it's the computer's turn.";
			bool c = computerLogic(v, z, s, f);
			z++;
			cout << "\nThe computer made their move. Here is the board: \n";
			display(v);
			if (z >= 9) {
				cout << "\nIt was a draw! Press y is you would like to play again: ";
				string again;
				cin >> again;
				if (again == "Y" || again == "y") {
					main();
				}
				else {
					cout << "\nCya!";
					exit(0);
				}
			}
			if (z >= 3) {
				bool w = checkWin(v);
				if (w == true) {
					cout << "\nOh no! The Computer has won in " << z << " turns!\n";
					cout << "\nPress y is you would like to play again: ";
					string again;
					cin >> again;
					if (again == "Y" || again == "y") {
						main();
					}
					else {
						cout << "\nCya!";
						exit(0);
					}
				}
			}
			//system("PAUSE");
			continue;
		}
	}
	else {
		bool winner = false;
		int z = 0;
		cout << "\nThe Computer will move first.";
		s = getChar("Player 1");
		if (s == 'X') {
			f = 'O';
		}
		else {
			f = 'X';
		}
		while (winner == false) {
			bool h = computerLogic(v, z, f, s);
			z++;
			cout << "\nThe computer has made their move, here is the board: \n";
			display(v);
			if (z >= 9) {
				cout << "\nIt was a draw! Press y is you would like to play again: ";
				string again;
				cin >> again;
				if (again == "Y" || again == "y") {
					main();
				}
				else {
					cout << "\nCya!";
					exit(0);
				}
			}
			if (z >= 3) {
				bool w = checkWin(v);
				if (w == true) {
					cout << "\nOh no! The Computer has won in " << z << " turns!\n";
					cout << "\nPress y is you would like to play again: ";
					string again;
					cin >> again;
					if (again == "Y" || again == "y") {
						main();
					}
					else {
						cout << "\nCya!";
						exit(0);
					}
				}
			}
			cout << "\nPlayer 1, it's your turn!";
			int u;
			u = getPlayerMove("Player 1");
			cout << "\nYou input was accepted, now lets see if its a valid move.";
			bool g = isValidMove(v, u);
			if (g == false) {
				cout << "\nYou tried moving to a spot that has already been taken. Try again.";
				continue;
			}
			v[u - 1] = s;
			z++;
			cout << "\n";
			display(v);
			if (z >= 9) {
				cout << "\nIt was a draw! Press y is you would like to play again: ";
				string again;
				cin >> again;
				if (again == "Y" || again == "y") {
					main();
				}
				else {
					cout << "\nCya!";
					exit(0);
				}
			}
			if (z >= 3) {
				bool w = checkWin(v);
				if (w == true) {
					cout << "\nCongratulations! Player 1 has won in " << z << " turns!\n";
					cout << "\nPress y is you would like to play again: ";
					string again;
					cin >> again;
					if (again == "Y" || again == "y") {
						main();
					}
					else {
						cout << "\nCya!";
						exit(0);
					}
				}
			}
			//If you don't continue here, would a stop occur
			continue;
		}
	}
}

static void play2(char* const b) {
	char f;
	char s;
	bool n = getFirst();
	if (n == true) {
		int z = 0;
		bool winner = false;
		cout << "\nPlayer 1 will move first.";
		f = getChar("Player 1");
		if (f == 'X') {
			s = 'O';
		}
		else {
			s = 'X';
		}
		while (winner == false) {
			cout << "\nPlayer 1, it's your turn!";
			int u;
			u = getPlayerMove("Player 1");
			cout << "\nYour input was accepted, now lets see if its a valid move.";
			bool g = isValidMove(b, u);
			if (g == false) {
				cout << "\nYou tried moving to a spot that has already been taken. Try again.";
				continue;
			}
			b[u - 1] = f;
			z++;
			cout << "\n";
			display(b);
			if (z >= 9) {
				cout << "\nIt was a draw! Press y is you would like to play again: ";
				string again;
				cin >> again;
				if (again == "Y" || again == "y") {
					main();
				}
				else {
					cout << "\nCya!";
					exit(0);
				}
			}
			if (z >= 3) {
				bool w = checkWin(b);
				if (w == true) {
					cout << "\nCongratulations! Player 1 has won in " << z << " turns!\n";
					cout << "\nPress y is you would like to play again: ";
					string again;
					cin >> again;
					if (again == "Y" || again == "y") {
						main();
					}
					else {
						cout << "\nCya!";
						exit(0);
					}
				}
			}
			cout << "\nNow it's Player 2's turn.";
			innerAsk:
			int h;
			//innerAsk:
			h = getPlayerMove("Player 2");
			cout << "\nYour input was accepted, now lets see if its a valid move.";
			bool gL = isValidMove(b, h);
			if (gL == false) {
				cout << "\nYou tried moving to a spot that has already been taken. Try again.";
				gL = true;
				goto innerAsk;
			}
			b[h - 1] = s;
			z++;
			cout << "\n";
			display(b);
			if (z >= 9) {
				cout << "\nIt was a draw! Press y is you would like to play again: ";
				string again;
				cin >> again;
				if (again == "Y" || again == "y") {
					main();
				}
				else {
					cout << "\nCya!";
					exit(0);
				}
			}
			if (z >= 3) {
				bool w = checkWin(b);
				if (w == true) {
					cout << "\nCongratulations! Player 2 has won in " << z << " turns!\n";
					cout << "\nPress y is you would like to play again: ";
					string again;
					cin >> again;
					if (again == "Y" || again == "y") {
						main();
					}
					else {
						cout << "\nCya!";
						exit(0);
					}
				}
			}
			continue;
		}

	}
	else {
		cout << "\nPlayer 2 will move first.";
	}
}