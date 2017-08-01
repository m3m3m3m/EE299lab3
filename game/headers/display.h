
#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"

namespace display {
	void begin();				// initialize lcd
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
}

#endif	// DISPLAY_H
