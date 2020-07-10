#pragma once

class Game {
private:
	//member variables with "m_" prefix
	char m_player{ 'X' };

	//locations of fields(in bytes) in game board
	//in order to access them directly and
	//not loop through the whole board
	//which will make it difficult implementing
	//some game logic
	long long m_f1{};
	long long m_f4{};
	long long m_f7{};
	long long m_adjacentdif{};//difference between adjacent numbers i.e 1 and 2 for every board

	//methods
public:
	void initialization();
	void displayBoard();
	void userInput();
	void playerToggle();
	bool modifyBoard(char player, long long location);
	char checkForWinner();

	//Utilities
	void delayTimer(int durationInMillisecs);
	void removeTempFile();
	void cls();
};