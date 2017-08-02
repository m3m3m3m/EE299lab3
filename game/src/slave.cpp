
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/command.h"
#include "../headers/display.h"

void slave::setup() {
	display::begin();
	Serial.begin(BAUD_RATE);
}

void slave::loop() {
	if (Serial.available() > 0) {
		Serial.println("Received");
		command::receiveEvent();
	}
}
