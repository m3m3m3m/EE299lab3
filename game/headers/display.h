
#ifndef DISPLAY_H
#define DISPLAY_H

#include "game.h"

namespace display {
	void begin();				// initialize lcd
	void plotAnima(Boxes&);
	void choose(Boxes&, int);
	void gameStart(Boxes&);
	void ready();
}

#endif	// DISPLAY_H
