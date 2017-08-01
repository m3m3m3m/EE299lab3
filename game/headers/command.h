#ifndef COMMAND_H
#define COMMAND_H

namespace command{
	void plotAnima(Boxes&);		// plot animation
	void choose(Boxes&, int);	// select one box
	void gameStart(Boxes&);		// the start screen
	void ready(char const*);	// display info in the first line
}
#endif	// COMMAND_H