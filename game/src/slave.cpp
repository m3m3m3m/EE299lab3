
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/command.h"
#include "../headers/display.h"

#define TILT 11
#define BUZZER 9

void slave::setup() {
	pinMode(BUZZER, OUTPUT);
	display::begin();
	Serial.begin(BAUD_RATE);
	randomSeed(analogRead(12));
}

void slave::loop() {
	if (Serial.available() > 0) {
		command::receiveEvent();
	}
	if (!digitalRead(TILT)) {
		display::clear();
	}
}
