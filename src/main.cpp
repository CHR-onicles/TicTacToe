/*****************************************
*Author: CHR-onicles
*Date: 10/06/2020 00:30GMT
*Last updated: 10/08/2020 17:00GMT
*****************************************/

#include <iostream>
#include <conio.h> //for _getch()
#include "Game.h"

int main() {
	char choice{};
	do {
		Game tictac; //creating Game object
		int numOfMoves{ 0 };

		do {
			tictac.userInput();
			numOfMoves++;
			tictac.displayBoard();
			if (tictac.finalCheck(numOfMoves))
				break;
			tictac.playerToggle();
			tictac.computerTurn();
			numOfMoves++;
			tictac.displayBoard();
			if (tictac.finalCheck(numOfMoves))
				break;
			tictac.playerToggle();
		} while (numOfMoves != 10);
		std::cout << "Try again? [Any key to continue/Esc to quit]: ";
		choice = _getch();
	} while (choice != 27);

	std::cout << "\n";
	return 0;
}