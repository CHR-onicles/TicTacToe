#include "GameFunctions.h"
#include "Utilities.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <cctype> //toupper(),tolower()
#include <limits> //cin.ignore()

//Initializing Global Variables
char player{ 'X' };

//locations of fields(in bytes) in game board
	//in order to access them directly and
	//not loop through the whole board
	//which will make it difficult implementing
	//some game logic
long long f1{};
long long f4{};
long long f7{};
long long adjacentdif{};//difference between adjacent numbers i.e 1 and 2 for every board

/*===================================================
*Function: playerToggle()
*Description: To toggle player turns.
===================================================*/
void playerToggle() {
	if (player == 'X')
		player = 'O';
	else player = 'X';
}

/*===================================================
*Function: initialization()
*Description: Displays splash Screen loaded from file
===================================================*/
void initialization() {
	//change console colour to aqua if on windows
	//still looking for linux equivalent
#ifdef _WIN32
	system("color 0b");
#endif // _WIN32

	delayTimer(5000);
	std::ifstream ifs{ "Splash.txt" };
	if (!ifs) {
		std::cerr << "Error loading Splash Screen." << std::endl;
		return;
	}
	std::string line;
	std::cout << "\n\n\n\n\n\n\n\n";

	while (std::getline(ifs, line)) {
		delayTimer(155);
		std::cout << "\t\t\t\t" << line << std::endl;
	}
	delayTimer(2000);

	//SetConsoleOutputCP(1252); //to show copyright symbol correctly
	std::cout << "\n\t\t\t\t" << "Powered by CHR-onicles" << std::endl;
	delayTimer(5000);
	ifs.close();

	//showcase all boards
	cls();
	char read{};
	bool valid{ false };
	int choice{};
	std::string boardnames[] = { "board3.txt","board4.txt","board5.txt","board6.txt" };
	std::cout << "\tCheck these guys out!\n\n" << std::endl;
	delayTimer(3000);
	for (int i{ 0 }; i <= 3; ++i) {
		//cls();
		std::ifstream ifs{ boardnames[i].c_str() };
		while (ifs.get(read)) {
			std::cout << read;
		}
		std::cout << "\n\n\n";
		delayTimer(3000);
	}
	ifs.close();

	do {
		std::cout << "\n\nWhich would you like to play with? [1/2/3/4]: ";
		std::cin >> choice;
		if (choice > 0 && choice < 5) {
			//display board
			cls();
			std::fstream ifs2{ boardnames[choice - 1].c_str(),std::ios::in | std::ios::out };
			if (!ifs2) {
				std::cerr << "Error loading board" << std::endl;
				return;
			}

			//temp file is going to be modified as the game goes on
			//and deleted at the end of game
			//char read{};
			std::fstream fs{ "temp.txt", std::ios::out | std::ios::binary };
			while (ifs2.get(read)) {
				fs.put(read);
			}
			fs.close();
			//loop through game board and get where numbers are
			//for every different board instead of manually
			//checking myself.
			std::fstream ipt{ "temp.txt",std::ios::in };
			int counter{ 0 };
			while (ipt.get(read)) {
				counter++;
				std::cout << read;
				if (read == '1')
					f1 = counter;
				if (read == '2')
					adjacentdif = counter - f1;
				if (read == '4')
					f4 = counter;
				if (read == '7')
					f7 = counter;
			}

			//Game board done displaying
			std::cout << "\n\tPlayer 1: 'X'" << std::endl;
			std::cout << "\tPlayer 2: 'O'" << std::endl;

			ifs2.close();
			//fs.close();
			ipt.close();
			valid = true;
		}
		else {
			std::cerr << "Invalid option" << std::endl;

			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cin.clear();
		}
	} while (!valid);
}

/*===================================================
*Function: displayBoard()
*Description: displays current state of game board.
===================================================*/
void displayBoard() {
	cls();
	std::fstream fs("temp.txt", std::ios::in);
	if (!fs) {
		std::cerr << "Error displaying temp board" << std::endl;
		return;
	}
	char read{};
	while (fs.get(read)) {
		std::cout << read;
	}

	std::cout << "\n\tPlayer 1: 'X'" << std::endl;
	std::cout << "\tPlayer 2: 'O'" << std::endl;
	fs.close();
}

/*===================================================
*Function: modifyBoard()
*Description: Inserts player's character into game
			  board.
===================================================*/
bool modifyBoard(char player, long long location) {
	std::fstream fs{ "temp.txt",std::ios::in | std::ios::out };
	if (!fs) {
		std::cerr << "Error loading board to be modified" << std::endl;
		return false;
	}
	char read1{};

	//double location{};
	//while (fs.get(read)) {
	//	if (read == index) {
	//		location = fs.tellp();
	//		break;
	//	}
	//}
	//fs.clear(); //clear state of file - EOF
	//fs.seekp(location - 1, std::ios::beg);
	//fs.put(player);
	//fs.close();
	fs.seekg(location - 1, std::ios::beg);
	fs.get(read1);
	if (isdigit(read1)) {
		fs.seekp(location - 1, std::ios::beg);
		fs.put(player);
		fs.close();
		return true;
	}
	else if (isalpha(read1)) {
		std::cerr << "The field is already occupied" << std::endl;
		fs.close();
		return false;
	}
	return false;
}

/*===================================================
*Function: userInput()
*Description: Asks user for input
===================================================*/
void userInput() {
	char input;

	bool inputValid{ false };
	do {
		std::cout << "\nPlayer: " << player << ", Enter the number of the field to be occupied: ";
		std::cin >> input;
		switch (input) {
		case '1':
			if (modifyBoard(player, f1))
				inputValid = true;
			break;

		case '2':
			if (modifyBoard(player, f1 + adjacentdif))
				inputValid = true;
			break;

		case '3':
			std::cout << "Entered 3" << std::endl;
			if (modifyBoard(player, f1 + (adjacentdif * 2)))
				inputValid = true;
			break;

		case '4':
			if (modifyBoard(player, f4))
				inputValid = true;

			break;
		case '5':
			if (modifyBoard(player, f4 + adjacentdif))
				inputValid = true;
			break;

		case '6':
			if (modifyBoard(player, f4 + (adjacentdif * 2)))
				inputValid = true;
			break;

		case '7':
			if (modifyBoard(player, f7))
				inputValid = true;
			break;

		case '8':
			if (modifyBoard(player, f7 + adjacentdif))
				inputValid = true;
			break;

		case '9':
			if (modifyBoard(player, f7 + (adjacentdif * 2)))
				inputValid = true;
			break;

		default:
			std::cerr << "Invalid option" << std::endl;
			inputValid = false;
			break;
		}
	} while (!inputValid);
}

/*===================================================
*Function: checkForWinner()
*Description: Checks gameboard if there's a winner or
			  a draw.
===================================================*/
char checkForWinner() {
	char read1{};
	char read2{};
	char read3{};

	std::ifstream ifs{ "temp.txt" };
	if (!ifs) {
		std::cerr << "Error opening temp file to check for winner" << std::endl;
		std::exit(2); //trying to avoid returning anything since function
					  //actually returns a value
	}

	//checking horizontally on 1st row
	ifs.seekg(f1 - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(f1 + adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(f1 + (adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return player;

	//checking horizontally on 2nd row
	ifs.seekg(f4 - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(f4 + adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(f4 + (adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return player;

	//checking horizontally on 3rd row
	ifs.seekg(f7 - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(f7 + adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(f7 + (adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return player;

	//checking vertically on 1st column
	ifs.seekg(f1 - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(f4 - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(f7 - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return player;

	//cheking vertically on 2nd column
	ifs.seekg(f1 + adjacentdif - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(f4 + adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(f7 + adjacentdif - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return player;

	//checking vertically on 3rd column
	ifs.seekg(f1 + (adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(f4 + (adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(f7 + (adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return player;

	//checking left diagonal
	ifs.seekg(f1 - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(f4 + adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(f7 + (adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return player;

	//checking right diagonal
	ifs.seekg(f1 + (adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(f4 + adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(f7 - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return player;

	//else its a draw
	return 'd';
}