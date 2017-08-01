
#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/control.h"

void master::setup() {
	Serial.begin(BAUD_RATE);
	control::begin();
}

void master::loop() {
	Serial.println("HAPPY");
	WAIT_FOR_CONFIRMING delay(20);
	//game::newGame();
}
