
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/command.h"

namespace command {
	enum Command {
		PLOT_ANIMA,
		CHOOSE,
		GAME_START,
		GAME_END,
		GAME_OPEN,
		RIGHT_OPEN,
		WRONG_OPEN,
		READY,
		SETTING_START,
		SETTING_MENU
	};

	void transferString(char const* str) {
		Serial.print(str);
		Serial.print('\n');
	}

	void transferNum(int num) {
		Serial.print(num);
		Serial.print(' ');
	}

	void transferBox(Boxes& boxes) {
		transferNum(boxes.num);
		for(int i = 0;i<boxes.num;i++) {
			transferNum(boxes.pos[i].c);
			transferNum(boxes.pos[i].r);
		}
	}


}

void command::plotAnima(Boxes& boxes) {
	transferNum(Command::PLOT_ANIMA);
	transferBox(boxes);
}

void command::choose(Boxes& boxes, int boxNo) {
	transferNum(Command::CHOOSE);
	transferBox(boxes);
	transferNum(boxNo);
}

void command::gameStart(Boxes& boxes) {
	transferNum(Command::GAME_START);
	transferBox(boxes);
}

void command::gameEnd(Boxes& boxes) {
	transferNum(Command::GAME_END);
	transferBox(boxes);
}

void command::gameOpen(Boxes& boxes, int choice) {
	transferNum(Command::GAME_OPEN);
	transferBox(boxes);
	transferNum(choice);
}

void command::rightOpen(Boxes& boxes, int choice) {
	transferNum(Command::RIGHT_OPEN);
	transferBox(boxes);
	transferNum(choice);
}

void command::wrongOpen(Boxes& boxes, int choice) {
	transferNum(Command::WRONG_OPEN);
	transferBox(boxes);
	transferNum(choice);
}

void command::ready(char const* info) {
	transferNum(Command::READY);
	transferString(info);
}

void command::settingStart() {
	transferNum(Command::SETTING_START);
}

void command::settingMenu
(char const* item, int value, int min, int max, int line) {
	transferNum(Command::SETTING_MENU);
	transferString(item);
	transferNum(value);
	transferNum(min);
	transferNum(max);
	transferNum(line);
}
