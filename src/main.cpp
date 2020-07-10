/*****************************************
*Author: CHR-onicles
*Date: 10/06/2020 00:30GMT
*Revised date: 10/07/2020 16:05GMT
*****************************************/

#include <iostream>
#include "Game.h"

int main() {
	Game tictac; //creating Game object
	tictac.initialization();
	int numOfMoves{ 0 };

	do {
		tictac.userInput();
		tictac.displayBoard();
		numOfMoves++;
		if (tictac.checkForWinner() == 'X') {
			std::cout << "\nGAME OVER! Player X wins!!" << std::endl;
			break;
		}
		else if (tictac.checkForWinner() == 'O') {
			std::cout << "\nGAME OVER! Player O wins!!" << std::endl;
			break;
		}
		else if (tictac.checkForWinner() == 'd' && numOfMoves == 9) {
			std::cout << "\nGAME OVER! It's a DRAW." << std::endl;
			break;
		}
		tictac.playerToggle();
	} while (numOfMoves != 9);

	tictac.removeTempFile();
	std::cout << "\n";
	return 0;
}