#ifndef COMMAND_H
#define COMMAND_H

namespace command{
	void plotAnima(Boxes&);		// plot animation
	void choose(Boxes&, int);	// select one box
	void gameStart(Boxes&);		// the start screen
	void gameEnd(Boxes&);		// the end screen
	void gameOpen(Boxes&, int);	// open the box
	void rightOpen(Boxes&, int);// open right
	void wrongOpen(Boxes&, int);// open wrong
	void ready(char const*);	// display info in the first line
	void settingStart();		// prepare for the setting page
	void settingMenu(			// display a line of setting item
		char const*,int,int,int,int);
	void receiveEvent();		// receive a command and execute it
}
#endif	// COMMAND_H