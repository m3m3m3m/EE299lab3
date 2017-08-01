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

	void gameEnd(Boxes& boxes) {
		display::gameEnd(boxes);
	}

	void gameOpen(Boxes& boxes, int choice) {
		display::gameOpen(boxes, choice);
	}

	void rightOpen(Boxes& boxes, int choice) {
		display::rightOpen(boxes, choice);
	}

	void wrongOpen(Boxes& boxes, int choice) {
		display::wrongOpen(boxes, choice);
	}

	void ready(char const* info) {
		display::ready(info);
	}

	void settingStart() {
		display::settingStart();
	}

	void settingMenu(char const* item, int value, int min, int max, int line) {
		display::settingMenu(item, value, min, max, line);
	}
}