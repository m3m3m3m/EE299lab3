
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/control.h"
#include <time.h>

void master::setup() {
	Serial.begin(BAUD_RATE);
	control::begin();
	randomSeed((unsigned)time(NULL));
	game::tutorial();
}

void master::loop() {
	game::newGame();
}
