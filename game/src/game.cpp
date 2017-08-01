
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/move.h"
#include "../headers/display.h"

#define DELAY delay(20)
#define RANDOM_CLOCKWIZE random(0, 2)

namespace game {

	int num = 3;	// number of boxes
	int speed = 5;	// the speed level
					// minspeed = (speed + 1) / 2
					// maxspeed = (speed + 4) / 2
	int diffi = 1;	// the times of moving = 5 * diffi + 5
	int choice = 1;

	inline int step() {
		return random((speed + 1) / 2, (speed + 4) / 2);
	}

	void newGame() {
		Boxes boxes = {.num=num};
		move::begin(boxes);
		display::gameStart(boxes);
		delay(1000);
		display::choose(boxes, choice);
		delay(1000);
		display::ready("3");
		delay(1000);
		display::ready("2");
		delay(1000);
		display::ready("1");
		delay(1000);
		display::ready("Go");
		delay(500);

		move::begin(boxes);
		display::plotAnima(boxes);
		DELAY;
		while (move::nextFrame(boxes)) {
			display::plotAnima(boxes);
			DELAY;
		}
		for (int i = 5 * diffi + 5; i > 0; i --) {
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
			move::swap(
				boxes, box1, box2, 
				RANDOM_CLOCKWIZE,
				step()
			);
			while (move::nextFrame(boxes)) {
				display::plotAnima(boxes);
				DELAY;
			}
		}
		move::end();
		while (move::nextFrame(boxes)) {
			display::plotAnima(boxes);
			DELAY;
		}

		display::gameEnd(boxes);
		delay(1000);
		int select = random(0, num);
		display::choose(boxes, select);
		delay(1000);
		display::gameOpen(boxes, select);
		delay(1000);
		display::ready("");
		if (choice == select) {
			display::rightOpen(boxes, select);
			delay(1000);
			display::ready("You Win! :)");
		} else {
			display::wrongOpen(boxes, select);
			delay(1000);
			display::ready("You Lose! :(");
		}
		delay(1000);
	}
}
