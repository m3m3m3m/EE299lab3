
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/control.h"

void master::setup() {
	Serial.begin(BAUD_RATE);
	control::begin();
}

void master::loop() {
	game::newGame();
}
