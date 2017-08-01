
#include "Arduino.h"
#include "../headers/display.h"
#include "../headers/move.h"

Boxes boxes = {
	.num = 4,
	.pos = {
		{2, 8},
		{38, 8},
		{44, 8},
		{-2, 2}
	}
};

namespace test {
	void setup() {
		Serial.begin(BAUD_RATE);
		display::begin();
		move::begin(boxes);
		display::plotAnima(boxes);
		randomSeed(analogRead(0));
	}

	void loop() {
		for (int i = random(1, 3); i >= 0; i --)
			if (!move::nextFrame(boxes)) {
				move::swap(boxes, 1, 3, false);
			}
		display::plotAnima(boxes);
		delay(20);
	}
}
