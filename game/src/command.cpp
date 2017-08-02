
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/command.h"
#include "../headers/display.h"
#include "../headers/move.h"

#define TERMINATOR '\t'

namespace command {
	int moveStep;
	Boxes boxes;

	enum Command {
		PLOT_ANIMA = 1,
		CHOOSE,
		GAME_START,
		GAME_END,
		GAME_OPEN,
		RIGHT_OPEN,
		WRONG_OPEN,
		READY,
		SETTING_START,
		SETTING_MENU,
		MOVE_BEGIN,
		MOVE_SWAP,
		MOVE_END,
		MOVE_SETUP
	};

	inline void transferString(char const* str) {
		Serial.print(str);
		Serial.print(TERMINATOR);
	}

	inline void transferNum(int num) {
		Serial.print(num);
		Serial.print(' ');
	}

	inline void transferFinish() {
		Serial.print('\n');
	}

	inline void keepMoving(Boxes& boxes) {
		do {
			display::plotAnima(boxes);
			delay(20);
		} while(move::nextFrame(boxes));
	}

}

void command::plotAnima() {
	transferNum(Command::PLOT_ANIMA);
	transferFinish();
}

void command::choose(int boxNo) {
	transferNum(Command::CHOOSE);
	transferNum(boxNo);
	transferFinish();
}

void command::gameStart() {
	transferNum(Command::GAME_START);
	transferFinish();
}

void command::gameEnd() {
	transferNum(Command::GAME_END);
	transferFinish();
}

void command::gameOpen(int choice) {
	transferNum(Command::GAME_OPEN);
	transferNum(choice);
	transferFinish();
}

void command::rightOpen(int choice) {
	transferNum(Command::RIGHT_OPEN);
	transferNum(choice);
	transferFinish();
}

void command::wrongOpen(int choice) {
	transferNum(Command::WRONG_OPEN);
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

void command::moveBegin() {
	transferNum(Command::MOVE_BEGIN);
	transferFinish();
}

void command::moveSwap(int boxA, int boxB, bool clockwise) {
	transferNum(Command::MOVE_SWAP);
	transferNum(boxA);
	transferNum(boxB);
	transferNum((int) clockwise);
	transferFinish();
}

void command::moveEnd() {
	transferNum(Command::MOVE_END);
	transferFinish();
}

void command::moveSetup(int num, int speed) {
	transferNum(Command::MOVE_SETUP);
	boxes.num = num;
	move::begin(boxes);
	transferNum(speed);
	transferFinish();
}

void command::receiveEvent() {
	int recVal0,recVal1,recVal2,recVal3;
	char const* recStr;
	Command cmd = (Command) Serial.parseInt();
	switch(cmd) {
		case Command::PLOT_ANIMA:
			Serial.println("plotAnima");
			display::plotAnima(boxes);
			break;
		case Command::CHOOSE:
			recVal0 = Serial.parseInt();
			Serial.println("choose");
			display::choose(boxes,recVal0);
			break;
		case Command::GAME_START:
			Serial.println("gameStart");
			display::gameStart(boxes);
			break;
		case Command::GAME_END:
			Serial.println("gameEnd");
			display::gameEnd(boxes);
			break;
		case Command::GAME_OPEN:
			recVal0 = Serial.parseInt();
			Serial.println("gameOpen");
			display::gameOpen(boxes,recVal0);
			break;
		case Command::RIGHT_OPEN:
			recVal0 = Serial.parseInt();
			Serial.println("rightOpen");
			display::rightOpen(boxes,recVal0);
			break;
		case Command::WRONG_OPEN:
			recVal0 = Serial.parseInt();
			Serial.println("wrongOpen");
			display::wrongOpen(boxes,recVal0);
			break;
		case Command::READY:
			recStr = Serial.readStringUntil(TERMINATOR).c_str();
			Serial.println("ready");
			display::ready(recStr);
			break;
		case Command::SETTING_START:
			display::settingStart();
			Serial.println("settingStart");
			break;
		case Command::SETTING_MENU:
			recStr = Serial.readStringUntil(TERMINATOR).c_str();
			recVal0 = Serial.parseInt();
			recVal1 = Serial.parseInt();
			recVal2 = Serial.parseInt();
			recVal3 = Serial.parseInt();
			Serial.println("settingMenu");
			display::settingMenu(recStr,recVal0,recVal1,recVal2,recVal3);
			break;
		case Command::MOVE_BEGIN:
			Serial.println("moveBegin");
			move::begin(boxes);
			keepMoving(boxes);
			break;
		case Command::MOVE_SWAP:
			recVal0 = Serial.parseInt();
			recVal1 = Serial.parseInt();
			recVal2 = Serial.parseInt();
			Serial.println("moveSwap");
			move::swap(boxes,recVal0,recVal1,(bool)recVal2,moveStep);
			keepMoving(boxes);
			break;
		case Command::MOVE_END:
			Serial.println("moveEnd");
			move::end();
			keepMoving(boxes);
			break;
		case Command::MOVE_SETUP:
			int speed = Serial.parseInt();
			moveStep = random((speed + 1) / 2, (speed + 4) / 2);
			Serial.println("moveSetup");
			break;
	}
}



