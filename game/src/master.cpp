
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/control.h"

void master::setup() {
	Serial.begin(BAUD_RATE);
	control::begin();
	randomSeed(analogRead(12));
	game::tutorial();
}

void master::loop() {
	game::newGame();
}
