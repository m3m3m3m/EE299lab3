
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/command.h"
#include "../headers/display.h"

#define TERMINATOR '\t'

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

	inline void transferString(char const* str) {
		Serial.print(str);
		Serial.print(TERMINATOR);
	}

	inline void transferNum(int num) {
		Serial.print(num);
		Serial.print(' ');
	}

	inline void transferBox(Boxes& boxes) {
		transferNum(boxes.num);
		for(int i = 0;i<boxes.num;i++) {
			transferNum(boxes.pos[i].c);
			transferNum(boxes.pos[i].r);
		}
	}

	inline void transferFinish() {
		Serial.print('\n');
	}

	inline void parseBoxes(Boxes& boxes) {
		boxes.num = Serial.parseInt();
		for(int i = 0;i<boxes.num;i++) {
			boxes.pos[i].c = Serial.parseInt();
			boxes.pos[i].r = Serial.parseInt();
		}
	}

	inline void parseMenu() {

	}
}

void command::plotAnima(Boxes& boxes) {
	transferNum(Command::PLOT_ANIMA);
	transferBox(boxes);
	transferFinish();
}

void command::choose(Boxes& boxes, int boxNo) {
	transferNum(Command::CHOOSE);
	transferBox(boxes);
	transferNum(boxNo);
	transferFinish();
}

void command::gameStart(Boxes& boxes) {
	transferNum(Command::GAME_START);
	transferBox(boxes);
	transferFinish();
}

void command::gameEnd(Boxes& boxes) {
	transferNum(Command::GAME_END);
	transferBox(boxes);
	transferFinish();
}

void command::gameOpen(Boxes& boxes, int choice) {
	transferNum(Command::GAME_OPEN);
	transferBox(boxes);
	transferNum(choice);
	transferFinish();
}

void command::rightOpen(Boxes& boxes, int choice) {
	transferNum(Command::RIGHT_OPEN);
	transferBox(boxes);
	transferNum(choice);
	transferFinish();
}

void command::wrongOpen(Boxes& boxes, int choice) {
	transferNum(Command::WRONG_OPEN);
	transferBox(boxes);
	transferNum(choice);
	transferFinish();
}

void command::ready(char const* info) {
	transferNum(Command::READY);
	transferString(info);
	transferFinish();
}

void command::settingStart() {
	transferNum(Command::SETTING_START);
	transferFinish();
}

void command::settingMenu
(char const* item, int value, int min, int max, int line) {
	transferNum(Command::SETTING_MENU);
	transferString(item);
	transferNum(value);
	transferNum(min);
	transferNum(max);
	transferNum(line);
	transferFinish();
}

void command::receiveEvent() {
	Boxes boxes;
	int recNum;
	int menuVal0,menuVal1,menuVal2,menuVal3;
	char* recStr;
	Command cmd = (Command) Serial.parseInt();
	switch(cmd) {
		case Command::PLOT_ANIMA:
			parseBoxes(boxes);
			display::plotAnima(boxes);
			break;
		case Command::CHOOSE:
			parseBoxes(boxes);
			recNum = Serial.parseInt();
			display::choose(boxes,recNum);
			break;
		case Command::GAME_START:
			parseBoxes(boxes);
			display::gameStart(boxes);
			break;
		case Command::GAME_END:
			parseBoxes(boxes);
			display::gameEnd(boxes);
			break;
		case Command::GAME_OPEN:
			parseBoxes(boxes);
			recNum = Serial.parseInt();
			display::gameOpen(boxes,recNum);
			break;
		case Command::RIGHT_OPEN:
			parseBoxes(boxes);
			recNum = Serial.parseInt();
			display::rightOpen(boxes,recNum);
			break;
		case Command::WRONG_OPEN:
			parseBoxes(boxes);
			recNum = Serial.parseInt();
			display::wrongOpen(boxes,recNum);
			break;
		case Command::READY:
			recStr = Serial.readStringUntil(TERMINATOR).c_str();
			display::ready(recStr);
			break;
		case Command::SETTING_START:
			display::settingStart();
			break;
		case Command::SETTING_MENU:
			recStr = Serial.readStringUntil(TERMINATOR).c_str();
			menuVal0 = Serial.parseInt();
			menuVal1 = Serial.parseInt();
			menuVal2 = Serial.parseInt();
			menuVal3 = Serial.parseInt();
			display::settingMenu(recStr,menuVal0,menuVal1,menuVal2,menuVal3);
			break;
	}
	Serial.read();
}

