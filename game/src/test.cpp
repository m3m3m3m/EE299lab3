
#include "Arduino.h"
#include "../headers/display.h"
#include "../headers/move.h"
#include "../headers/control.h"
#include "../headers/game.h"

void test::setup() {
	Serial.begin(BAUD_RATE);
	display::begin();
	control::begin();
	randomSeed(analogRead(0));
}

void test::loop() {
	game::newGame();
}
