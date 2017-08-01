
#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"

namespace display {
	void begin();				// initialize lcd
	void plotAnima(Boxes&);		// plot animation
	void choose(Boxes&, int);	// select one box
	void gameStart(Boxes&);		// the start screen
	void ready(char*);			// display info in the first line
}

#endif	// DISPLAY_H
