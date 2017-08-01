
#include "../headers/game.h"
#include "../headers/move.h"
#include "../headers/display.h"

namespace game {

	int num = 3;	// number of boxes
	int speed = 1;	// the speed level
					// minspeed = speed + 1 / 2, maxspeed = (speed + 2) / 2

	void newGame() {
		Boxes boxes = {.num=num};
		move::begin(boxes);
		display::gameStart(boxes);
	}
}
