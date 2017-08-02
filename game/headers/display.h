
#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"
#include "Arduino.h"

namespace display {
	void clear();
	void begin();				// initialize lcd
	void plotAnima(Boxes&);		// plot animation
	void choose(Boxes&, int);	// select one box
	void gameStart(Boxes&);		// the start screen
	void gameEnd(Boxes&);		// the end screen
	void gameOpen(Boxes&, int);	// open the box
	void rightOpen(Boxes&, int);// open right
	void wrongOpen(Boxes&, int);// open wrong
	void ready(char const*);	// display info in the first line
	void ready(String&);
	void settingStart();		// prepare for the setting page
	void settingMenu(			// display a line of setting item
		char const*,int,int,int,int);
	void tutorialStart();
	void tutorialUp();
	void tutorialDown();
}

#endif	// DISPLAY_H
