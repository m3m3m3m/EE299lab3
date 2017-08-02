#ifndef COMMAND_H
#define COMMAND_H

namespace command{
	void plotAnima();			// plot animation
	void choose(int);			// select one box
	void gameStart();			// the start screen
	void gameEnd();				// the end screen
	void gameOpen(int);			// open the box
	void rightOpen(int);		// open right
	void wrongOpen(int);		// open wrong
	void ready(char const*);	// display info in the first line
	void settingStart();		// prepare for the setting page
	void settingMenu(			// display a line of setting item
		int,int,int);
	void receiveEvent();		// receive a command and execute it
	void moveBegin(int,int);	// begin moving
	void moveSwap(int,int);		// swap two boxes
	void moveEnd();				// end moving
	void moveSetup(int,int);	// setting number and speed
	void tutorialStart();
	bool tutorialEnd();
	bool tutorialUp();
	bool tutorialDown();
}
#endif	// COMMAND_H