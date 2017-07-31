
#ifndef GAME_H
#define GAME_H

#include "constant.h"

struct Pos {
	int x, y;
};

struct Boxes {
	int num;
	Pos pos[MAX_BOXES];
};

struct Map {
	int cat, index;
	// cat from 0 to 4
	// index from 0 to 9
};

struct Char {
	char smap;	// the lcd mapping
	Map map;	// the global mapping
};

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
