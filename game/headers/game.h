
#ifndef GAME_H
#define GAME_H

#include "constant.h"

struct Pos {
	int c, r;	// column and row in micro grid
};

struct Boxes {
	int num;
	Pos pos[MAX_BOXES];
};

typedef unsigned char *Char;

struct Map {
	char smap;	// the lcd mapping
	Char map;	// the global mapping
};

namespace game {
	void newGame();
	void settings();
}

namespace master {
	void setup();
	void loop();
}

namespace slave {
	void setup();
	void loop();
}

namespace test {
	void setup();
	void loop();
}

#endif	// GAME_H
