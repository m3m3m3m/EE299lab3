
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/command.h"
#include "../headers/control.h"

#define RANDOM_CLOCKWIZE random(0, 2)

#define NUM 0
#define SPEED 1
#define DIFFI 2
#define SETTING_MENU(x, l) command::settingMenu(x, *settings[x], l)

namespace game {

	int num = 7;	// number of boxes
	int speed = 5;	// the speed level
					// minspeed = (speed + 1) / 2
					// maxspeed = (speed + 4) / 2
	int diffi = 1;	// the times of moving = 5 * diffi + 5
	int choice = 0;
	int select = 0;
	int settingLine = NUM;
	int cursorLine = 0;

	int *settings[] = {&num, &speed, &diffi};

	inline int _step() {
		return random((speed + 1) / 2, (speed + 4) / 2);
	}

	bool chooseLeft() {
		if (choice != 0) {
			choice -= 1;
			command::choose(choice);
		}
		return true;
	}

	bool chooseRight() {
		if (choice != num - 1) {
			choice += 1;
			command::choose(choice);
		}
		return true;
	}

	bool selectLeft() {
		if (select != 0) {
			select -= 1;
			command::choose(select);
		}
		return true;
	}

	bool selectRight() {
		if (select != num - 1) {
			select += 1;
			command::choose(select);
		}
		return true;
	}

	bool goToSetting() {
		setting();
		return true;
	}

	bool settingUp() {
		switch (settingLine) {
			case 0: 
				break;
			case 1: 
				settingLine -= 1;
				SETTING_MENU(1, 1);
				SETTING_MENU(0, 0);
				break;
			case 2:
				settingLine -= 1;
				SETTING_MENU(2, 1);
				SETTING_MENU(1, 0);
				break;
		}
		cursorLine = 0;
		return true;
	}

	bool settingDown() {
		switch (settingLine) {
			case 0: 
				settingLine += 1;
				SETTING_MENU(0, 0);
				SETTING_MENU(1, 1);
				break;
			case 1: 
				settingLine += 1; 
				SETTING_MENU(1, 0);
				SETTING_MENU(2, 1);
				break;
			case 2:
				break;
		}
		cursorLine = 1;
		return true;
	}

	bool settingRight() {
		if (*settings[settingLine] < _max[settingLine]) {
			*settings[settingLine] += 1;
			SETTING_MENU(settingLine, cursorLine);
		}
		return true;
	}

	bool settingLeft() {
		if (*settings[settingLine] > _min[settingLine]) {
			*settings[settingLine] -= 1;
			SETTING_MENU(settingLine, cursorLine);
		}
		return true;
	}
}

using control::nothing;
using control::confirm;

void game::newGame() {
	command::moveBegin(num,speed);
	choice = 0;
	command::gameStart();
	delay(1000);
	// command::choose(choice);
	control::attachPad(
		&nothing, &chooseRight, &nothing, &chooseLeft, 
		&goToSetting, &confirm, &nothing, &nothing
	);

	command::ready("3");
	delay(1000);
	command::ready("2");
	delay(1000);
	command::ready("1");
	delay(1000);
	command::ready("Go");
	delay(500);

	command::moveBegin(num, speed);
	for(int i = 5 * diffi + 5; i > 0; i --) {
		// generate random 2 boxes
		int box1 = random(0, num);
		int box2 = random(1, num);
		if (box2 == box1) {
			box2 = 0;
		}
		if (box1 == choice) {
			choice = box2;
		} else if (box2 == choice) {
			choice = box1;
		}
		command::moveSwap(box1,box2);
		int gap = box1 - box2;
		if (gap < 0) gap = -gap;
		int delayTime = (2 * gap * (LCD_WIDTH / num) + 2) * 6 * (72 + diffi) / (2 * speed + 1);
		delay(delayTime);
	}
	command::moveEnd();

	// move::begin(boxes);
	// display::plotAnima(boxes);
	// DELAY;
	// while (move::nextFrame(boxes)) {
	// 	display::plotAnima(boxes);
	// 	DELAY;
	// }
	// for (int i = 5 * diffi + 5; i > 0; i --) {
	// 	// generate random 2 boxes
	// 	int box1 = random(0, num);
	// 	int box2 = random(1, num);
	// 	if (box2 == box1) {
	// 		box2 = 0;
	// 	}
	// 	if (box1 == choice) {
	// 		choice = box2;
	// 	} else if (box2 == choice) {
	// 		choice = box1;
	// 	}
	// 	move::swap(
	// 		boxes, box1, box2, 
	// 		RANDOM_CLOCKWIZE,
	// 		_step()
	// 	);
	// 	while (move::nextFrame(boxes)) {
	// 		display::plotAnima(boxes);
	// 		DELAY;
	// 	}
	// }
	// move::end();
	// while (move::nextFrame(boxes)) {
	// 	display::plotAnima(boxes);
	// 	DELAY;
	// }

	WAIT_FOR_CONFIRMING;
	select = 0;
	command::gameEnd();

	control::attachPad(
		&nothing, &selectRight, &nothing, &selectLeft, 
		&nothing, &confirm, &nothing, &nothing
	);

	command::gameOpen(select);
	delay(1000);
	command::ready("");
	if (choice == select) {
		command::rightOpen(select);
		delay(1000);
		command::ready("You Win! :)");
	} else {
		command::wrongOpen(select);
		delay(1000);
		command::ready("You Lose! :(");
		WAIT_FOR_CONFIRMING;
		command::ready("The answer is:");
		delay(1000);
		command::gameOpen(choice);
		delay(1000);
		command::ready("");
		command::rightOpen(choice);
	}
	
	control::attachButton(
		&nothing,
		&confirm,
		&nothing,
		&nothing
	);
}

void game::setting() {
	settingLine = NUM;
	cursorLine = 0;
	command::settingStart();
	SETTING_MENU(SPEED, 1);
	SETTING_MENU(NUM, 0);
	control::attachPad(
		&settingUp,
		&settingRight,
		&settingDown,
		&settingLeft,
		&confirm,
		&confirm,
		&nothing,
		&nothing
	);
	command::moveBegin(num,speed);
	choice = 0;
	command::gameStart();
}
