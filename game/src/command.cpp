#include "../headers/display.h"

namespace command {
	void plotAnima(Boxes& boxes) {
		display::plotAnima(boxes);
	}

	void choose(Boxes& boxes, int boxNo) {
		display::choose(boxes, boxNo);
	}

	void gameStart(Boxes& boxes) {
		display::gameStart(boxes);
	}

	void ready(char const* info) {
		display::ready(info);
	}
}