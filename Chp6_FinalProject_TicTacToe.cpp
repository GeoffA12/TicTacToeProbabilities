// Chp6_FinalProject_TicTacToe.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define NOMINMAX
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime> 
#include <Windows.h>
using namespace std;

void rules();
void display(const vector<vector<char>>&);
void createBoard(vector<vector<char>>&);
const int ROWS = 3;
const int COLUMNS = 3;
int getPlayers();
bool play2(vector<vector<char>>&);
bool getFirst();
static char getChar(string);
string getUserChoice(string, string);
bool isValidNumber(string, string);
bool isEmptySpace(vector<vector<char>>&, int, int);
bool hasWon(vector<vector<char>>);
bool play1(vector<vector<char>>&);
bool computerLogic(vector<vector<char>>&, string, char, char, int);
static bool compMove(string, char, vector<vector<char>>&, int*, char);
static bool playerMove(string, char, vector<vector<char>>&, int*);
static bool wantToPlayAgain(bool, string);
int main()
{
	bool again = true;
	while (again) {
		vector<vector<char>> myVec;
		vector<vector<char>>& master = myVec;
		const vector<vector<char>>& copier = myVec;
		cout << "\t\t\t\t\t\t\t\TIC-TAC-TOE\n";
		createBoard(master);
		rules();
		display(master);
		int k = getPlayers();
		if (k == 2) {
			again = play2(master);
		}
		else if (k == 1) {
			again = play1(master);
		}
	}
	cout << "\nGoodbye!";
	Sleep(2000);
    return 0;
}

// Create the tic tac toe board using a 2d vector reference. In this program, this vector constantly be updated and modified. Note that 
// a different data structure could be used, such as wrapping a 1d vector. An example of this data structre is seen in the other tictactoe program
// in this repository. 
static void createBoard(vector<vector<char>>& s) {
	s.resize(4);
	for (int i = 0; i < ROWS; i++) {
		s[i].resize(4);
		for (int j = 0; j < COLUMNS; j++) {
			s[i][j] = '_';
		}
	}

}
static void rules() {
	cout << "\nHi. Welcome to the Tic-Tac-Toe game. In this game, the goal is to align three of your characters either diagonally, in a straight line horizontally, or\n";
	cout << " in a straight line vertically. You can choose whether or not you want to play against the computer, play against a friend, or \n";
	cout << "have the computer play against itself. You will also choose whether you want your characters to be 'X' or 'O', but which player goes first will be deicded by an RNG.\n";
	cout << "Here is how the game board looks: \n";
}

// This is the function will be written as inline because we need to constantly accessthe game board, or print the 2d vector which stores the 
// the tic tac toe board as the game progresses. 
static inline void display(const vector<vector<char>>& m) {
	cout << "\nBOARD\n\n";
	cout << "  012 " << endl;
	for (int i = 0; i < ROWS; i++) {
		cout << i;
		cout << "|";
		for (int j = 0; j < COLUMNS; j++) {
			cout << m[i][j];
		}
		cout << "|";
		cout << i;
		cout << endl;
	}
	cout << "  012 " << endl;
}

// Return the number of players who will be playing. The user can only enter either 1 or 2 as an option. Any other input will return false on the 
// while condition on line 106.
static int getPlayers() {
	bool key = false;
	string input;
	while (key == false) {
		cout << "\nHow many players will be playing? ";
		cin >> input;
		if (input.size() > 1) {
			cout << "\nYour input can only be 1 or 2. Try again: ";
			continue;
		}
		else if (input != "1" && input != "2") {
			cout << "\nPlease enter number between 1 and 2. Try again: ";
			continue;
		}
		key = true;
	}
	return stoi(input);
}


static bool getFirst() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	string a;
	cout << "\nWe will do a coin flip to see who gets to make the first move.\n";

	char charArray[2];
	int check;
	char retVal;
	cout << "\nPlayer 1, enter h for heads or t for tails: ";
	while (true) {
		cin.getline(charArray, 2, '\n');
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nYou can only enter one character. Try again: ";
			continue;
		}
		retVal = charArray[0];
		// Convert the first and only character in the char array container to an integer so we can check its ascii value.
		check = retVal;
		if (check == 0) {
			cout << "\nYou need to enter at least one character! Try again: ";
		}
		// Ignore the case sensitive h or t characters, but make sure you catch cases in which they enter an invalid character
		else if (retVal != 'h' && retVal != 'H' && retVal != 't' && retVal != 'T') {
			cout << "\nYou need to enter h for heads or t for tails. Try again: ";
			continue;
		}
		else {
			break;
		}
	}

	// This line sets a random seed to ensure the number is truly randomly generated. 
	srand(static_cast<unsigned int>(time(0)));
	// This should return a randomly generated number between 1 and 2 tin order to decide which player will move first. 
	int coinFlip = rand()%(2 - 1 + 1) + 1;
	return ((coinFlip == 1 && (retVal == 'h' ||retVal == 'H')) || (coinFlip == 2 && (retVal == 't' || retVal == 'T'))) ? true : false;
}

// This function will return an X or O tic tac toe charater from the player who is moving first. 
// Note that if user selected a one player game, then the first player, or user, will always be prompted for which character they want. 
static char getChar(string firstMove) {
	cout << "\n" << firstMove << " will move first. \n";
	// Handle the edge case in which the user entered into a one player game, but the computer will move first. In this case, the firstMove string passed
	// in will be assigned to computer. However, we wouldn't want the firstMove string to equal 'Computer' on line 147 either. So here, we're just changing 
	// the string to Player so that the cout statement on line 147 is correct in all cases. 
	if (firstMove == "Computer") {
		firstMove = "Player 1";
	}
	char container [2];
	int check;
	char retVal;
	cout << "\n" << firstMove << " ,do you want X's or O's? Enter either x or o: ";
	while (true) {
		cin.getline(container, 2, '\n');
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "\nYou can only enter one character. Try again: ";
			continue;
		}
		retVal = container[0];

		// Convert the first and only character in the char array container to an integer so we can check its ascii value.
		check = retVal;
		if (check == 0) {
			cout << "\nYou need to enter at least one character! Try again: ";
		}
		else if (retVal != 'X' && retVal != 'x' && retVal != 'O' && retVal != 'o') {
			cout << "\nYou need to enter either an X or O. Try again: ";
		}
		else {
			break;
		}
	}

	// 120 and 111 are the ascii code characters for "x" and "o". If the user entered in a lowercase, we want to convert it to uppercase 
	// for display purposes. 
	if (check == 120 || check == 111) {
		retVal = toupper(retVal);
	}
	return retVal;
}

static string getUserChoice(string g, string c) {
	string y;
	cout << "\n"<< g << ", please enter a " << c << " value between 0-2: ";
	cin >> y;
	return y;
}
static inline bool isValidNumber(string c, string b) {
	if (c.length() > 1) {
		cout << "\nYour input was too long. Try again.";
		return false;
	}
	else if (c != "0" && c != "1" && c != "2") {
		cout << "\nYour move for the " << b << " value must be between 0-2. Try again.";
		return false;
	}
	else {
		return true;
	}
}

// Helper function to check and see if there is an empty character on the 2d vector where the user entered their x and y coordinates. Return
// false if the space has already been taken, and true if the space is open. 
static inline bool isEmptySpace(vector<vector<char>>& q, int x, int y) {
	if (q[x][y] != '_') {
		return false;
	}
	else {
		return true;
	}
}

// Thie helper function checks all possible winning combinations on the 2d vector to see if either player or computer has won the game. Note that this boolean function can
// be written much simpler by creating an array of winning combinations, and checking for membership inside the array of winning combinations. 
static bool hasWon(vector<vector<char>> u) {
	if ((u[0][0] == 'X' && u[1][1] == 'X' && u[2][2] == 'X') || (u[0][0] == 'X' && u[1][0] == 'X' && u[2][0] == 'X') || (u[0][0] == 'X' && u[0][1] == 'X' && u[0][2] == 'X') || (u[1][0] == 'X' && u[1][1] == 'X' && u[1][2] == 'X') || (u[2][0] == 'X' && u[2][1] == 'X' && u[2][2] == 'X') || (u[2][0] == 'X' && u[1][1] == 'X' && u[0][2] == 'X') || (u[0][1] == 'X' && u[1][1] == 'X' && u[2][1] == 'X') || (u[0][2] == 'X' && u[1][2] == 'X' && u[2][2] == 'X') || (u[0][0] == 'O' && u[1][1] == 'O' && u[2][2] == 'O') || (u[0][0] == 'O' && u[1][0] == 'O' && u[2][0] == 'O') || (u[0][0] == 'O' && u[0][1] == 'O' && u[0][2] == 'O') || (u[1][0] == 'O' && u[1][1] == 'O' && u[1][2] == 'O') || (u[2][0] == 'O' && u[2][1] == 'O' && u[2][2] == 'O') || (u[2][0] == 'O' && u[1][1] == 'O' && u[0][2] == 'O') || (u[0][1] == 'O' && u[1][1] == 'O' && u[2][1] == 'O') || (u[0][2] == 'O' && u[1][2] == 'O' && u[2][2] == 'O')) {
		return true;
	}
	else {
		return false;
	}
}

// This is a console display function we will call in both play1 and play2 functions once we know that someone has won the game, and have identified the winner. 
// The string whoWon which is taken as a parameter represents the player who won the game. 
static bool wantToPlayAgain(bool winner, string whoWon) {
	// If false was passed into this function for the winner parameter, we know the game was a draw. Therefore, we need a different display message here. 
	if (!winner) {
		cout << "\n\nIt was a draw! would you like to play again? Enter y to play again: ";
	}
	else {
		cout << "\nCongratulations," << whoWon << ", you're the winner!";
		cout << "\n\nEnter y for a rematch:";
	}
	string again;
	cin >> again;
	// Return true or false to caller. This boolean return value will be used by main() to determine whether or not a new game should start.
	if (again == "y" || again == "Y") {
		return true;
	}
	else {
		return false;
	}
}

// This is the logic function when the user plays a 2-player tic-tac-toe game with their friend. 
static bool play2(vector<vector<char>>& gameGrid) {
	char first_char = '*';
	char second_char = '*';
	string firstName = "";
	string secondName = "";
	bool win = false;
	bool playAgain = false;

	// Do a dice role which will return true if the first player is going to go first. Return false if the second player goes first 
	bool firstPlayerIsFirst = getFirst();

	// This if/else block is purely meant to initialize variables defined on lines 261-266
	if (firstPlayerIsFirst) {
		firstName = "Player 1";
		secondName = "Player 2";
		first_char = getChar(firstName);
		if (first_char == 'X') {
			second_char = 'O';
		}
		else {
			second_char = 'X';
		}
	}
	else {
		firstName = "Player 2";
		secondName = "Player 1";
		first_char = getChar(firstName);
		if (first_char == 'X') {
			second_char = 'O';
		}
		else {
			second_char = 'X';
		}
	}

	// numMoves will keep track on the total number of moves that have been made by both players inside the while loop so that we know when to display
	// a message that the game was a draw. 
	int numMoves = 0;
	// Both current name and current char will be used for string and console output formatting purposes. 
	char currentChar;
	string currentName;
	outerLoop:
	while (win == false) {

		// This if/else block will determine which player is currently playing, and which character they're using. 
		// This way, we can repeatedly use these variables throughout the while loop, or inner game. 
		// Use a modulus 2 operation here because numMoves will start at 0. Therefore, we're guaranteed that the even iterations 
		// of numMoves will be the first player's turn. The odd numbered iterations of numMoves will be the second player's turn.
		if (numMoves % 2 == 0) {
			currentChar = first_char;
			currentName = firstName;
		}
		else {
			currentChar = second_char;
			currentName = secondName;
		}

		if (numMoves >= 9) {
			// Nobody won because the game was a tie. 
			playAgain = wantToPlayAgain(false, "");
			return playAgain;
		}
		
		cout << "\n" << currentName << ", it's your turn! \n";
		bool isValidRow = false;
		bool isValidColumn = false;
		bool isGoodSpace = false;
		int fy;
		int fx;

		// This nested while loop will call two functions - getUserChoice() and testValid(). These two functions will get user input strings. The first 
		// while loop controls the Row value the user wants to enter. The value in getUserChoice is stored as a string and passed into isValidNumber() 
		// which checks that the value entered was valid. 
		while (!isGoodSpace) {
			while (isValidRow == false) {

				string r = getUserChoice(currentName, "Row");
				bool testValid = isValidNumber(r, "Row");
				if (!testValid) {
					continue;
				}
				fx = stoi(r);
				isValidRow = true;
			}
			while (isValidColumn == false) {
				string r = getUserChoice(currentName, "Column");
				bool testValid = isValidNumber(r, "Column");

				if (!testValid) {
					continue;
				}
				fy = stoi(r);
				isValidColumn = true;
			}

			// The isEmptySpace needs to be called once the two integers have been validated to make sure the spot the user wants to move is empty. 
			// If row and column value entered isn't empty, repeat the outer while loop. 
			isGoodSpace = isEmptySpace(gameGrid, fx, fy);
			if (!isGoodSpace) {
				cout << "\nThe space you picked has already been taken!";
			}
		}

		// update the game board by replacing the '_' character with the current character of the player who is currently playing. 
		gameGrid[fx][fy] = currentChar;
		numMoves++;
		cout << "\nHere's how the board looks: \n";
		display(gameGrid);
		
		// Once the number of moves has risen past 3, there could be a potential winner. Therefore, we need check if their was a winner 
		// by using the hasWon() function. 
		if (numMoves > 3) {
			bool h = hasWon(gameGrid);
			if (h) {
				playAgain = wantToPlayAgain(true, currentName);
				win = true;
			}
		}
	}
	return playAgain;
}

// Function which executes when the user selects a one player game. The core ideas behind this function lie inside the computerLogic function. 
// The user and the computer swap turns until either the user wins, loses, or the game goes to a draw. 
static bool play1(vector<vector<char>>& masterBoard) {
	//Random number generation method that picks who will move first
	bool playerGoesFirst = getFirst();
	bool winCF = false;
	bool someoneWon = false;
	bool playAgain;
	string firstMover = "";
	string secondMover = "";
	char firstChar;
	char secondChar;
	int *numMoves;
	int startingNum = 0;
	numMoves = &startingNum;
	if (playerGoesFirst) {
		firstMover = "Player 1";
		secondMover = "Computer";
		firstChar = getChar(firstMover);
		if (firstChar == 'X') {
			secondChar = 'O';
		}
		else {
			secondChar = 'X';
		}
		while (!someoneWon) {
			someoneWon = playerMove(firstMover, firstChar, masterBoard, numMoves);
			if (someoneWon) {
				playAgain = wantToPlayAgain(true, firstMover);
				return playAgain;
			}
			if (*numMoves >= 9) {
				playAgain = wantToPlayAgain(false, "");
				return playAgain;
			}
			someoneWon = compMove(secondMover, secondChar, masterBoard, numMoves, firstChar);
			if (someoneWon) {
				playAgain = wantToPlayAgain(true, secondMover);
				return playAgain;
			}
			if (*numMoves >= 9) {
				playAgain = wantToPlayAgain(false, "");
				return playAgain;
			}

		}

	}

	//This is the game loop where the computer will move first. 
	else {
		firstMover = "Computer";
		secondMover = "Player 1";
		secondChar = getChar(firstMover);
		if (secondChar == 'X') {
			firstChar = 'O';
		}
		else {
			firstChar = 'X';
		}

		while (!someoneWon) {
			someoneWon = compMove(firstMover, firstChar, masterBoard, numMoves, secondChar);
			if (someoneWon) {
				playAgain = wantToPlayAgain(true, firstMover);
				return playAgain;
			}
			if (*numMoves >= 9) {
				playAgain = wantToPlayAgain(false, "");
				return playAgain;
			}
			someoneWon = playerMove(secondMover, secondChar, masterBoard, numMoves);
			if (someoneWon) {
				playAgain = wantToPlayAgain(true, secondMover);
				return playAgain;
			}
			if (*numMoves >= 9) {
				playAgain = wantToPlayAgain(false, "");
				return playAgain;
			}

		}
	}
}

// This function is called inside the play1() function. This function will execute whenever it's the computer's turn to move. 
// Note that the computerLogic function is called in this function. The computerLogic function is where the probability calculations
// are executed. 
// The pointer numMoves is passed in as an argument, which will increment the integer value it stores after the computer the moves. 
static bool compMove(string computerName, char computerChar, vector<vector<char>>& masterBoard, int * numMoves, char playerChar) {
	cout << "\nNum moves is: " << *numMoves << endl;
	// This boolean will be returned to the caller inside play1() function because we need to know whether or not we should be ending the game. 
	// Aka, we're using it to know if someone has won. 
	bool winners = false;
	//computer's turn
	cout << "\nNow it's the computer's turn.";
	int passed = *numMoves;
	bool c = computerLogic(masterBoard, computerName, computerChar, playerChar, passed);

	cout << "\nThe computer made their move.";
	// Increment the value inside numMoves pointer so we know when to check for ties and winners. 
	(*numMoves)++;

	cout << "\nHere is how the board looks: ";
	display(masterBoard);
	if ((*numMoves) > 3) {
		bool h = hasWon(masterBoard);
		if (h == true) {
			winners = true;
		}
	}
	return winners;
}

// This function is called inside the play1() function. This function will execute when it's the player's turn to move.
// There are two basic input checks we must consider in this function. This function validates both the user's input 
// for a row choice and a column choice. After this initial validation, a check on the ordered pair inside the tic tac toe
// board is tested to see whether or not the space has already been taken. If the move is valid, then the pointer numMoves 
// will increment its value by one. 
static bool playerMove(string playerName, char firstChar, vector<vector<char>>& masterBoard, int * numMoves) {
	bool winners = false;
	bool isGoodSpace = false;
	bool isValidRow = false;
	bool isValidColumn = false;
	int fy;
	int fx;
	//Outer while loop ensures the move hasn't already been taken 
	while (!isGoodSpace) {
		// Two inner while loops validate the row and column inputs to make sure they're valid and in range of 0-2 by 
		// calling both getUserChoice and isValidNumber functions. 
		while (isValidRow == false) {
			string r = getUserChoice(playerName, "Row");
			bool testValid = isValidNumber(r, "Row");
			if (!testValid) {
				continue;
			}
			fx = stoi(r);
			isValidRow = true;
		}
		while (isValidColumn == false) {
			string r = getUserChoice(playerName, "Column");
			bool testValid = isValidNumber(r, "Column");

			if (!testValid) {
				continue;
			}
			fy = stoi(r);
			isValidColumn = true;
		}

		// The isEmptySpace needs to be called once the two integers have been validated to make sure the spot the user wants to move is empty. 
		// If row and column value entered isn't empty, repeat the outer while loop. 
		isGoodSpace = isEmptySpace(masterBoard, fx, fy);
		if (!isGoodSpace) {
			cout << "\nThe space you picked has already been taken!";
		}
	}
	//Update the game board because the move is valid and increment the value inside pointer numMoves. 
	masterBoard[fx][fy] = firstChar;
	(*numMoves)++;

	cout << "\nHere's how the board looks: \n";
	display(masterBoard);
	//Display the board and then check to see if Player has won the game
	if ((*numMoves) > 3) {
		bool h = hasWon(masterBoard);
		if (h == true) {
			winners = true;
		}
	}
	return winners;
}

// This function is called inside compMove() and is used by the comptuer to process the entire game board to determine \
// which move gives the computer the best probability to win the game. 
// I will refactor this function in the future so that the variable names are more semantic, there are more helper functions involved, and
// less repetition of code. 
static bool computerLogic(vector<vector<char>>& y, string comp, char pc, char p, int zO) {
	cout << "\nThe computer will make their turn now.\n";
	// empty character represents that the space on the game board is currently open. 
	char empty = '_';
	
	// This initial boolean check to see if the computer can currently win. If the computer can currently win, then the computer
	// will move to the empty space and win the game. 
	if (zO >= 3) {
		int index = 0;
		int p1 = 1;
		int p2 = 2;
		//Test the diagonal (top left to bottom right permutations to see if the computer can win on this turn. If so, move to that space so the computer will win.
		for (; index < COLUMNS; index++) {
			if (index == 1) {
				p1 = 0;
				p2 = 2;
			}
			if (index == 2) {
				p1 = 0;
				p2 = 1;
			}
			if (y[index][index] == empty && y[p1][p1] == pc && y[p2][p2] == pc) {
				y[index][index] = pc;
				return true;
			}
		}
		int x;
		int d;
		int d1;
		int d2;
		int s1;
		int s2;
		int ct = 2;
		//Test the next diaongal permutations (bottom left to top right) to see if the computer can win on this turn. If so, move to that empty space and win. 
		for (; ct >= 0; ct--) {
			if (ct == 2) {
				d = 1;
				x = 1;
				d1 = 0;
				d2 = 2;
				s2 = 0;
				s1 = 2;
			}
			if (ct == 1) {
				d2 = 1;
				d1 = 1;
				d = 2;
				x = 0;
				s2 = 0;
				s1 = 2;
			}
			if (ct == 0) {
				d2 = 0;
				d1 = 2;
				d = 1;
				x = 1;
				s2 = 2;
				s1 = 0;
			}
			if (y[d2][d1] == empty && y[d][x] == pc && y[s2][s1] == pc) {
				y[d2][d1] = pc;
				return true;
			}
		}
		//Test each row on the board for each permutation to see if there is a possibility the computer can use a straight horizontal line. If so, move to that empty space and win. 
		int i = 0;
		int fc = 1;
		int fe = 2;
		for (i; i < ROWS; i++) {
			fc = 1;
			fe = 2;
			for (int fv = 0; fv < COLUMNS; fv++) {
				if (fv == 1) {
					fc = 0;
					fe = 2;
				}
				if (fv == 2) {
					fc = 1;
					fe = 0;
				}
				if (y[i][fv] == empty && y[i][fc] == pc && y[i][fe] == pc) {
					y[i][fv] = pc;
					return true;
				}
			}
		}
		int iY = 0;
		int fcY;
		int feZ;
		//Test each vertical column on the board to see if there is an empty space that the computer can move to and win. If so, move to that space and win. 
		for (iY; iY < COLUMNS; iY++) {
			fcY = 1;
			feZ = 2;
			for (int fv = 0; fv < ROWS; fv++) {
				if (fv == 1) {
					fcY = 0;
					feZ = 2;
				}
				if (fv == 2) {
					fcY = 1;
					feZ = 0;
				}
				if (y[fv][iY] == empty && y[fcY][iY] == pc && y[feZ][iY] == pc) {
					y[fv][iY] = pc;
					return true;
				}
			}
		}

		//****** Start testing here to see if the opponent is in position to win. Here we test the first diagonal, (top right to left bottom) to see if the opponent can win on their next turn
		//If so, block them at that empty space which would be the winning move.
		int in = 0;
		for (; in < COLUMNS; in++) {
			if (in == 1) {
				p1 = 0;
				p2 = 2;
			}
			if (in == 2) {
				p1 = 0;
				p2 = 1;
			}
			if (y[in][in] == empty && y[p1][p1] == p && y[p2][p2] == p) {
				y[in][in] = pc;
				return true;
			}
		}
		int x1;
		int dB;
		int dL;
		int dO;
		int sF;
		int sE;
		int cT = 2;


		// Test the next diaongal permutations (bottom left to top right) to see if the opponent can win on this turn. 
		// If so, move to that empty space and block them. 
		for (; cT >= 0; cT--) {
			if (cT == 2) {
				dB = 1;
				x1 = 1;
				dL = 0;
				dO = 2;
				sE = 0;
				sF = 2;
			}
			if (cT == 1) {
				dO = 1;
				dL = 1;
				dB = 2;
				x1 = 0;
				sE = 0;
				sF = 2;
			}
			if (cT == 0) {
				dO = 0;
				dL = 2;
				dB = 1;
				x1 = 1;
				sE = 2;
				sF = 0;
			}
			if (y[dO][dL] == empty && y[dB][x1] == p && y[sE][sF] == p) {
				y[dO][dL] = pc;
				return true;
			}
		}

		//Test each row on the board for each permutation to see if there is a possibility the opponent can use a straight horizontal line. If so, move to that empty space and win. 
		int iT = 0;
		int fcC = 1;
		int feE = 2;
		for (iT; iT < ROWS; iT++) {
			fcC = 1;
			feE = 2;
			for (int fv = 0; fv < COLUMNS; fv++) {
				if (fv == 1) {
					fcC = 0;
					feE = 2;
				}
				if (fv == 2) {
					fcC = 1;
					feE = 0;
				}
				if (y[iT][fv] == empty && y[iT][fcC] == p && y[iT][feE] == p) {
					y[iT][fv] = pc;
					return true;
				}
			}
		}
		//Test each vertical column on the board to see if there is an empty space that the opponent can move to and win. If so, move to that space and block them. 
		int fcCC;
		int feEE;
		for (int iP = 0; iP < COLUMNS; iP++) {
			fcCC = 1;
			feEE = 2;
			for (int fv = 0; fv < ROWS; fv++) {
				if (fv == 1) {
					fcCC = 0;
					feEE = 2;
				}
				if (fv == 2) {
					fcCC = 1;
					feEE = 0;
				}
				if (y[fv][iP] == empty && y[fcCC][iP] == p && y[feEE][iP] == p) {
					y[fv][iP] = pc;
					return true;
				}
			}
		}
	}

	// Each of these characters are shorthand for spaces on the masterBoard, or y, which
	// oo

	char corner = y[0][0];
	char corner2 = y[0][2];
	char corner3 = y[2][0];
	char corner4 = y[2][2];
	char diamond1 = y[0][1];
	char diamond2 = y[1][0];
	char diamond3 = y[1][2];
	char diamond4 = y[2][1];
	char middle = y[1][1];
	int highT = 0;
	char select;
	char work;
	int storeB;
	int storeU;
	bool haveBroken = false;

	// If we've reached this point in the function, then nobody in the game could currently win. 
	// This means that the computer will now process every location on the board and calculate a 
	// probability for each space using nested for loops and keeping track of maximum probability 
	// values. 
	outerFor:
	for (int b = 0; b < ROWS; b++) {
	innerFor:
		for (int u = 0; u < COLUMNS; u++) {
			//It needs to be an empty index check before you start running through probabilities
			if (y[b][u] == '_') {
				work = y[b][u];
				//If the middle is open, go there. Forget about the other probabilities and break out of the loop
				if (b == 1 && u == 1) {
					storeB = b;
					storeU = u;
					haveBroken = true;
					break;
				}
				//cout << "\nHi";
				//Left corner spot has three permutations that you need to check. u == 0 and b == 0 are the offset of the vector -> vect[b][u] == vect[0][0] since
				//we are inside a nested for loop. So this should theoretically be the first offset checked assuming player 1 hasn't moved to the top left corner.
				else if (b == 0 && u == 0) {
					//Each corner slot needs to have 3 different probabilities checked. The probability that of moving vertically, horizontally, and diagonally. We will test
					//each probability of this offset and then update the local and grand probabilities as need be. 
					int highL = 0;
					int prob1 = 0;
					int prob2 = 0;
					int prob3 = 0;
					for (int j = 1; j < COLUMNS; j++) {
						//cout << "\nI'm going through the left corner 1st probability.";
						int i = 0;
						if (y[i][j] == empty) {
							//Add one to this local probability if compiler sees an empty spot in top middle spot.
							prob1++;
						}
						if (y[i][j] == pc) {
							prob1 = prob1 + 2;
						}
						if (y[i][j] == p) {
							prob1--;
						}
						//int highL is set to 0 within each empty offset so that each probability is independent. So unless the 
						if (prob1 >= highL) {
							highL = prob1;
						}
					}
					int bs = 1;
					for (int i = 1; i < ROWS; i++) {
						if (y[i][bs] == empty) {
							prob2++;
							bs++;
						}
						else if (y[i][bs] == pc) {
							prob2 = prob2 + 2;
							bs++;
						}
						else if (y[i][bs] == p) {
							prob2--;
							bs++;
						}
						if (prob2 >= highL) {
							highL = prob2;
						}

					}
					for (int j = 1; j < ROWS; j++) {
						int i = 0;
						if (y[j][i] == empty) {
							prob3++;
						}
						if (y[j][i] == pc) {
							prob3 = prob3 + 2;
						}
						if (y[j][i] == p) {
							prob3--;
						}
						if (prob3 >= highL) {
							highL = prob3;
						}
					}
					//Once each local probability has been updated, highL should store the greatest total probability from that offset. Now we test this local high value
					//against the total high probability of the entire board which is first set to 0. Here, highT will likely be updated every instance to store the 
					//indices of this left corner offset since the highT is initialized to 0.
					if (highL >= highT) {
						highT = highL;
						storeB = b;
						storeU = u;
					}
				}
				else if (b == 0 && u == 1) {
					int highL = 0;
					int prob1 = 0;
					int prob2 = 0;
					for (int i = 0; i < COLUMNS - 1; i++) {
						int b = 0;
						if (i == 1) {
							i = 2;
						}
						if (y[b][i] == empty) {
							prob1++;
						}
						if (y[b][i] == pc) {
							prob1 = prob1 + 2;
						}
						if (y[b][i] == p) {
							prob1--;
						}
						if (prob1 >= highL) {
							highL = prob1;
						}
					}

					for (int p = 1; p < ROWS; p++) {
						int yd = 1;
						if (y[p][yd] == empty) {
							prob2++;
						}
						if (y[p][yd] == pc) {
							prob2 = prob2 + 2;
						}
						if (y[p][yd] == p) {
							prob2--;
						}
						if (prob2 >= highL) {
							highL = prob2;
						}
					}
					if (highL >= highT) {
						highT = highL;
						storeB = b;
						storeU = u;
					}
				}
				else if (b == 0 && u == 2) {
					int prob1 = 0;
					int prob2 = 0;
					int prob3 = 0;
					int highL = 0;
					int dr = 1;
					for (int t = 1; t < ROWS; t++) {
						if (y[t][dr] == empty) {
							prob1++;
						}
						if (y[t][dr] == pc) {
							prob1 = prob1 + 2;
						}
						if (y[t][dr] == p) {
							prob1--;
						}
						if (prob1 >= highL) {
							highL = prob1;
						}
						dr--;
					}
					int r = 0;
					for (int u = 0; u < COLUMNS - 1; u++) {
						if (y[r][u] == empty) {
							prob2++;
						}
						if (y[r][u] == pc) {
							prob2 = prob2 + 2;
						}
						if (y[r][u] == p) {
							prob2--;
						}
					}
					int rb = 2;
					for (int i = 1; i < ROWS; i++) {
						if (y[i][rb] == empty) {
							prob3++;
						}
						if (y[i][rb] == pc) {
							prob3 = prob3 + 2;
						}
						if (y[i][rb] == p) {
							prob3--;
						}
						if (prob3 >= highL) {
							highL = prob3;
						}
					}
					if (highL >= highT) {
						highT = highL;
						storeB = b;
						storeU = u;
					}
				}
				else if (b == 1 && u == 0) {
					int prob1 = 0;
					int prob2 = 0;
					int highL = 0;
					int op = 0;
					for (int i = 0; i < ROWS - 1; i++) {
						if (i == 1) {
							i = 2;
						}
						if (y[op][i] == empty) {
							prob1++;
						}
						if (y[op][i] == pc) {
							prob1 = prob1 + 2;
						}
						if (y[op][i] == p) {
							prob1--;
						}
					}
					int f5 = 1;
					for (int i = 1; i < COLUMNS; i++) {
						if (y[f5][i] == empty) {
							prob2++;
						}
						if (y[f5][i] == pc) {
							prob2 = prob2 + 2;
						}
						if (y[f5][i] == p) {
							prob2--;
						}
					}
					if (highL >= highT) {
						highT = highL;
						storeB = b;
						storeU = u;
					}
				}
				else if (b == 1 && u == 2) {
					int prob1 = 0;
					int prob2 = 0;
					int highL = 0;
					int yu = 2;
					for (int i = 0; i < ROWS - 1; i++) {
						if (i == 1) {
							i = 2;
						}
						if (y[i][yu] == empty) {
							prob1++;
						}
						if (y[i][yu] == pc) {
							prob1 = prob1 + 2;
						}
						if (y[i][yu] == p) {
							prob1--;
						}
					}
					int l = 1;
					for (int i = 0; i < COLUMNS - 1; i++) {
						if (y[1][i] == empty) {
							prob2++;
						}
						if (y[l][i] == pc) {
							prob2 = prob2 + 2;
						}
						if (y[l][i] == p) {
							prob2--;
						}
					}
					if (highL >= highT) {
						highT = highL;
						storeB = b;
						storeU = u;
					}
				}
				else if (b == 2 && u == 0) {
					int prob1 = 0; 
					int prob2 = 0;
					int prob3 = 0;
					int highL = 0;
					for (int g = 1; g >= 0; g--) {
						if (y[g][g] == empty) {
							prob1++;
						}
						if (y[g][g] == pc) {
							prob1 = prob1 + 2;
						}
						if (y[g][g] == p) {
							prob1--;
						}
						if (prob1 >= highL) {
							highL = prob1;
						}
					}
					int s = 0;
					for (int i = 0; i < ROWS - 1; i++) {
						if (y[s][i] == empty) {
							prob2++;
						}
						if (y[s][i] == pc) {
							prob2 = prob2 + 2;
						}
						if (y[s][i] == p) {
							prob2--;
						}
						if (prob2 >= highL) {
							highL = prob2;
						}
					}
					int bb = 2;
					for (int i = 1; i < COLUMNS; i++) {
						if (y[bb][i] == empty) {
							prob3++;
						}
						if (y[bb][i] == pc) {
							prob3 = prob3 + 2;
						}
						if (y[bb][i] == p) {
							prob3--;
						}
						if (prob2 >= highL) {
							highL = prob3;
						}
					}
					if (highL >= highT) {
						highT = highL;
						storeB = b;
						storeU = u;
					}
				}
				else if (b == 2 && u == 1) {
					int prob1 = 0;
					int prob2 = 0;
					int highL = 0;
					int rt = 2;
					for (int b = 0; b < COLUMNS - 1; b++) {
						if (y[rt][b] == empty) {
							prob1++;
						}
						if (y[rt][b] == pc) {
							prob1 = prob1 + 2;
						}
						if (y[rt][b] == p) {
							prob1--;
						}
						if (prob1 >= highL) {
							highL = prob1;
						}
					}
					int c = 1;
					for (int j = 1; j >= 0; j--) {
						if (y[j][c] == empty) {
							prob2++;
						}
						if (y[j][c] == pc) {
							prob2 = prob2 + 2;
						}
						if (y[j][c] == p) {
							prob2--;
						}
						if (prob2 >= highL) {
							highL = prob2;
						}
					}
					if (highL >= highT) {
						highT = highL;
						storeB = b;
						storeU = u;
					}
				}
				else if (b == 2 && u == 2) {
					int prob1 = 0;
					int prob2 = 0;
					int prob3 = 0;
					int highL = 0;
					for (int h = 1; h >= 0; h--) {
						if (y[h][h] == empty) {
							prob1++;
						}
						if (y[h][h] == pc) {
							prob1 = prob1 + 2;
						}
						if (y[h][h] == p) {
							prob1--;
						}
						if (prob1 >= highL) {
							highL = prob1;
						}
					}
					int kk = 2;
					for (int i = 0; i < COLUMNS - 1; i++) {
						if (y[kk][i] == empty) {
							prob2++;
						}
						if (y[kk][i] == pc) {
							prob2 = prob2 + 2;
						}
						if (y[kk][i] == p) {
							prob2--;
						}
						if (prob2 >= highL) {
							highL = prob2;
						}
					}
					for (int i = 0; i < ROWS - 1; i++) {
						if (y[i][kk] == empty) {
							prob3++;
						}
						if (y[i][kk] == pc) {
							prob3 = prob3 + 2;
						}
						if (y[i][kk] == p) {
							prob3--;
						}
						if (prob3 >= highL) {
							highL = prob3;
						}
					}
					if (highL >= highT) {
						highT = highL;
						storeB = b;
						storeU = u;
					}
				}
			}
		}
		if (haveBroken == true) {
			break;
		}
	}
	y[storeB][storeU] = pc;
	return true;
}

