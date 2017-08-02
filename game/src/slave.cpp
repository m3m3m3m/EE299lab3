
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/command.h"
#include "../headers/display.h"

void slave::setup() {
	display::begin();
	Serial.begin(BAUD_RATE);
	randomSeed(analogRead(0));
}

void slave::loop() {
	if (Serial.available() > 0) {
		command::receiveEvent();
	}
}
