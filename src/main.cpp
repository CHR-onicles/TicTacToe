/*****************************************
*Author: CHR-onicles
*Date: 10/06/2020 00:30GMT
*****************************************/

#include <iostream>
#include "GameFunctions.h"
#include "Utilities.h"

int main() {
	//system("color 0b"); //aqua effect on black background
	initialization();
	int numOfMoves{ 0 };

	do {
		userInput();
		displayBoard();
		numOfMoves++;
		if (checkForWinner() == 'X') {
			std::cout << "\nGAME OVER! Player X wins!!" << std::endl;
			break;
		}
		else if (checkForWinner() == 'O') {
			std::cout << "\nGAME OVER! Player O wins!!" << std::endl;
			break;
		}
		else if (checkForWinner() == 'd' && numOfMoves == 9) {
			std::cout << "\nGAME OVER! It's a DRAW." << std::endl;
			break;
		}
		playerToggle();
		
	} while (numOfMoves != 9);

	removeTempFile();
	std::cout << "\n";
	return 0;
}