#include "Game.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype> //toupper(),tolower()
#include <limits> //cin.ignore()
#include <fstream> //for remove(), getline()
#include <chrono> //for sleep timer
#include <thread> //for sleep time
#include <gsl/gsl> //for gsl::index
#include <cstdlib> //for rand()
#include <ctime> // for seeding random value

/*===================================================
*Function: cls()
*Description: To clear the screen based on platform
===================================================*/
#if defined (__linux__) || defined (__unix__)
void Game::cls() {
	system("clear");
}

#elif _WIN32
void Game::cls() {
	system("cls");
}
#endif

/*===================================================
*Function: Game constructor
*Description: Displays splash Screen loaded from file
===================================================*/
Game::Game() :m_player{ 'X' }, m_f1{}, m_f4{}, m_f7{}, m_adjacentdif{}{
	//change console colour to aqua if on windows
#ifdef _WIN32
	system("color 0b");
#endif // _WIN32

	srand(time(NULL));
	//delayTimer(5000);
	//std::ifstream ifs{ "Splash.txt" };
	//if (!ifs) {
	//	std::cerr << "Error loading Splash Screen." << std::endl;
	//	return;
	//}
	//std::string line;
	//std::cout << "\n\n\n\n\n\n\n\n";

	//while (std::getline(ifs, line)) {
	//	delayTimer(155);
	//	std::cout << "\t\t\t\t" << line << std::endl;
	//}
	//delayTimer(2000);

	////SetConsoleOutputCP(1252); //to show copyright symbol correctly
	//std::cout << "\n\t\t\t\t" << "Powered by CHR-onicles" << std::endl;
	//delayTimer(5000);
	//ifs.close();

	////showcase all boards
	//cls();
	char read{};
	bool valid{ false };
	int choice{};
	std::string boardnames[] = { "board1.txt","board2.txt","board3.txt","board4.txt","board5.txt","board6.txt" };
	//std::cout << "\tMake a choice from custom game board designs:\n\n" << std::endl;
	//delayTimer(3000);
	//for (gsl::index i{ 0 }; i <= 5; ++i) {
	//	std::ifstream ifs{ boardnames[i].c_str() };
	//	while (ifs.get(read)) {
	//		std::cout << read;
	//	}
	//	std::cout << "\n\n\n";
	//	delayTimer(3000);
	//}
	//ifs.close();

	do {
		std::cout << "\n\nWhich would you like to play with? [1/2/3/4/5/6]: ";
		std::cin >> choice;
		if (choice > 0 && choice < 7) {
			//display user chosen board
			cls();
			std::fstream ifs2{ boardnames[choice - 1].c_str(),std::ios::in | std::ios::out };
			if (!ifs2) {
				std::cerr << "Error loading board" << std::endl;
				return;
			}

			//temp file is going to be modified as the game goes on
			//and deleted at the end of game
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
					m_f1 = counter;
				if (read == '2')
					m_adjacentdif = counter - m_f1;
				if (read == '4')
					m_f4 = counter;
				if (read == '7')
					m_f7 = counter;
			}

			//Game board done displaying
			std::cout << "\n\tPlayer 1: 'X'" << std::endl;
			std::cout << "\tPlayer 2: 'O'" << std::endl;

			ifs2.close();
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
*Function: Game destructor
*Description: Deletes the temporary file the game was
			  running on.
===================================================*/
Game::~Game() {
	if (remove("temp.txt") != 0)
		std::cerr << "\nError removing temp file" << std::endl;
}

/*===================================================
*Function: delayTimer()
*Description: For delays in startup screen causing a
			 kind of loading effect.
===================================================*/
void Game::delayTimer(int durationInMillisecs) {
	std::chrono::milliseconds dura(durationInMillisecs);
	std::this_thread::sleep_for(dura);
}

/*===================================================
*Function: displayBoard()
*Description: displays current state of game board.
===================================================*/
void Game::displayBoard() {
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
	std::cout << "\tComputer: 'O'" << std::endl;
	fs.close();
}

/*===================================================
*Function: userInput()
*Description: Asks user for input
===================================================*/
void Game::userInput() {
	char input{};

	bool inputValid{ false };
	do {
		std::cout << "\nPlayer: " << m_player << ", Enter the number of the field to be occupied: ";
		std::cin >> input;
		switch (input) {
		case '1':
			if (modifyBoard(m_player, m_f1))
				inputValid = true;
			break;

		case '2':
			if (modifyBoard(m_player, m_f1 + m_adjacentdif))
				inputValid = true;
			break;

		case '3':
			if (modifyBoard(m_player, m_f1 + (m_adjacentdif * 2)))
				inputValid = true;
			break;

		case '4':
			if (modifyBoard(m_player, m_f4))
				inputValid = true;
			break;

		case '5':
			if (modifyBoard(m_player, m_f4 + m_adjacentdif))
				inputValid = true;
			break;

		case '6':
			if (modifyBoard(m_player, m_f4 + (m_adjacentdif * 2)))
				inputValid = true;
			break;

		case '7':
			if (modifyBoard(m_player, m_f7))
				inputValid = true;
			break;

		case '8':
			if (modifyBoard(m_player, m_f7 + m_adjacentdif))
				inputValid = true;
			break;

		case '9':
			if (modifyBoard(m_player, m_f7 + (m_adjacentdif * 2)))
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
*Function: playerToggle()
*Description: To toggle player turns.
===================================================*/
void Game::playerToggle() {
	/*if (m_player == 'X')
		m_player = 'O';
	else m_player = 'X';*/
	(m_player == 'X') ? m_player = 'O' : m_player = 'X';
}

/*===================================================
*Function: computerTurn()
*Description: Acts as AI to be played against.
===================================================*/
void Game::computerTurn() {
		char computerChoice{ (rand() % 9) + 1 };
		bool inputValid{ false };

		switch (computerChoice) {
			case '1':
				if (modifyBoard(m_player, m_f1))
				inputValid = true;
				std::cout << "Computer plays 1." << std::endl;
			break;

			case '2':
				if (modifyBoard(m_player, m_f1 + m_adjacentdif))
				inputValid = true;
				std::cout << "Computer plays 2." << std::endl;
			break;

			case '3':
				if (modifyBoard(m_player, m_f1 + (m_adjacentdif * 2)))
				inputValid = true;
				std::cout << "Computer plays 3." << std::endl;
			break;

			case '4':
				if (modifyBoard(m_player, m_f4))
				inputValid = true;
				std::cout << "Computer plays 4." << std::endl;
			break;

			case '5':
				if (modifyBoard(m_player, m_f4 + m_adjacentdif))
				inputValid = true;
				std::cout << "Computer plays 5." << std::endl;
			break;

			case '6':
				if (modifyBoard(m_player, m_f4 + (m_adjacentdif * 2)))
				inputValid = true;
				std::cout << "Computer plays 6." << std::endl;
			break;

			case '7':
				if (modifyBoard(m_player, m_f7))
				inputValid = true;
				std::cout << "Computer plays 7." << std::endl;
			break;

			case '8':
				if (modifyBoard(m_player, m_f7 + m_adjacentdif))
				inputValid = true;
				std::cout << "Computer plays 8." << std::endl;
			break;

			case '9':
				if (modifyBoard(m_player, m_f7 + (m_adjacentdif * 2)))
				inputValid = true;
				std::cout << "Computer plays 9." << std::endl;
			break;

			default:
				std::cerr << "Invalid option" << std::endl;
				inputValid = false;
			break;
		} while (!inputValid);
}


/*===================================================
*Function: modifyBoard()
*Description: Inserts player's character into game
			  board.
===================================================*/
bool Game::modifyBoard(char player, long long location) {
	std::fstream fs{ "temp.txt",std::ios::in | std::ios::out };
	if (!fs) {
		std::cerr << "Error loading board to be modified" << std::endl;
		return false;
	}
	char read1{};

	/*double location{};
		while (fs.get(read)) {
			if (read == index) {
			location = fs.tellp();
			break;
			}
		}
		fs.clear(); //clear state of file - EOF
		fs.seekp(location - 1, std::ios::beg);
		fs.put(player);
		fs.close();
	*/
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
*Function: checkForWinner()
*Description: Checks gameboard if there's a winner or
			  a draw.
===================================================*/
char Game::checkForWinner() {
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
	ifs.seekg(m_f1 - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(m_f1 + m_adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(m_f1 + (m_adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return m_player;

	//checking horizontally on 2nd row
	ifs.seekg(m_f4 - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(m_f4 + m_adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(m_f4 + (m_adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return m_player;

	//checking horizontally on 3rd row
	ifs.seekg(m_f7 - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(m_f7 + m_adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(m_f7 + (m_adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return m_player;

	//checking vertically on 1st column
	ifs.seekg(m_f1 - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(m_f4 - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(m_f7 - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return m_player;

	//cheking vertically on 2nd column
	ifs.seekg(m_f1 + m_adjacentdif - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(m_f4 + m_adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(m_f7 + m_adjacentdif - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return m_player;

	//checking vertically on 3rd column
	ifs.seekg(m_f1 + (m_adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(m_f4 + (m_adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(m_f7 + (m_adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return m_player;

	//checking left diagonal
	ifs.seekg(m_f1 - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(m_f4 + m_adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(m_f7 + (m_adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return m_player;

	//checking right diagonal
	ifs.seekg(m_f1 + (m_adjacentdif * 2) - 1, std::ios::beg);
	ifs.get(read1);
	ifs.seekg(m_f4 + m_adjacentdif - 1, std::ios::beg);
	ifs.get(read2);
	ifs.seekg(m_f7 - 1, std::ios::beg);
	ifs.get(read3);
	if (read1 == read2 && read2 == read3)
		return m_player;

	//else its a draw
	return 'd';
}