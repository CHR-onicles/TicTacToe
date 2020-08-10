/*****************************************
*Author: CHR-onicles
*Date: 10/06/2020 00:30GMT
*Last updated: 10/08/2020 16:00GMT
*****************************************/

#include <iostream>
#include "Game.h"

int main() {

	Game tictac; //creating Game object
	int numOfMoves{ 0 };

	do {
		tictac.userInput();
		numOfMoves++;
		tictac.displayBoard();
		tictac.finalCheck(numOfMoves);
		tictac.playerToggle();
		tictac.computerTurn();
		numOfMoves++;
		tictac.displayBoard();
		tictac.finalCheck(numOfMoves);
		tictac.playerToggle();
		
	} while (numOfMoves != 10);

	std::cout << "\n";
	return 0;
}