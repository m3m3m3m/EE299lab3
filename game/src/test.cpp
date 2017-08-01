
#include "Arduino.h"
#include "../headers/display.h"
#include "../headers/move.h"
#include "../headers/control.h"

namespace test {
	void setup() {
		Serial.begin(BAUD_RATE);
		display::begin();
		control::begin();
		randomSeed(analogRead(0));
	}

	void loop() {
		game::newGame();
	}
}
