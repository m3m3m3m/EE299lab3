#ifndef MOVE_H
#define MOVE_H

#include "game.h"

namespace move {
	void swap(Boxes&,int boxA, int boxB, bool clockwise);
	void begin(Boxes&);
	void end();
	bool nextFrame(Boxes&);
}

#endif