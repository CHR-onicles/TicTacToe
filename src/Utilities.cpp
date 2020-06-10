#include "Utilities.h"
#include <iostream>
#include <fstream> //for remove()
#include <chrono> //for sleep timer
#include <thread> //for sleep timer

/*===================================================
*Function: delayTimer()
*Description: For delays in startup screen causing a
			 kind of loading effect.
===================================================*/
void delayTimer(int durationInMillisecs) {
	std::chrono::milliseconds dura(durationInMillisecs);
	std::this_thread::sleep_for(dura);
}

/*===================================================
*Function: removeTempFile()
*Description: Deletes the temporary file the game was
			  running on.
===================================================*/
void removeTempFile() {
	if (remove("temp.txt") != 0)
		std::cerr << "\nError removing temp file" << std::endl;
}