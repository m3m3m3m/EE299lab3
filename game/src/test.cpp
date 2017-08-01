
#include "Arduino.h"
#include "../headers/display.h"
#include "../headers/move.h"

Boxes boxes = {
	.num = 8,
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
		for (int i = 1; i > 0; i --)
			if (!move::nextFrame(boxes)) {
				move::swap(boxes, 0, 5, false);
			}
		display::plotAnima(boxes);
		delay(200);
	}
}
