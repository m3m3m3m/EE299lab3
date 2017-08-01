#include "../headers/display.h"

namespace command {
	
}
void command::plotAnima(Boxes& boxes) {
	display::plotAnima(boxes);
}

void command::choose(Boxes& boxes, int boxNo) {
	display::choose(boxes, boxNo);
}

void command::gameStart(Boxes& boxes) {
	display::gameStart(boxes);
}

void command::gameEnd(Boxes& boxes) {
	display::gameEnd(boxes);
}

void command::gameOpen(Boxes& boxes, int choice) {
	display::gameOpen(boxes, choice);
}

void command::rightOpen(Boxes& boxes, int choice) {
	display::rightOpen(boxes, choice);
}

void command::wrongOpen(Boxes& boxes, int choice) {
	display::wrongOpen(boxes, choice);
}

void command::ready(char const* info) {
	display::ready(info);
}

void command::settingStart() {
	display::settingStart();
}

void command::settingMenu(char const* item, int value, int min, int max, int line) {
	display::settingMenu(item, value, min, max, line);
}