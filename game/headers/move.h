//----------------------------------------------------------------
//  Module name:
//      move.h
//  Languange:
//      C++
//  Description:
//      The module defines coordinate computing methods for 
//		moving boxes
//  Author:
//      Man Sun
//----------------------------------------------------------------

#ifndef MOVE_H
#define MOVE_H

#include "game.h"

namespace move {
	void swap(Boxes&,int boxA, int boxB, bool clockwise, int step);
	void begin(Boxes&);
	void end();
	bool nextFrame(Boxes&);
}

#endif	// MOVE_H