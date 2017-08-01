
#include "Arduino.h"
#include "../headers/display.h"
#include "../headers/move.h"

Boxes boxes = {
	.num = 7,
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
		randomSeed(analogRead(0));
	}

	void loop() {
		game::newGame();
	}
}
