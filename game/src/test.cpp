
#include "Arduino.h"
#include "../headers/display.h"
#include "../headers/move.h"
#include "../headers/control.h"
#include "../headers/game.h"

bool _up() {
	Serial.println("up");
	return true;
}

bool _right() {
	Serial.println("right");
	return false;
}

bool _down() {
	Serial.println("down");
	return true;
}

bool _left() {
	Serial.println("left");
	return true;
}

void test::setup() {
	Serial.begin(BAUD_RATE);
	control::begin();
}

void test::loop() {
	Serial.println("Start one");
	control::attachButton(&_up, &_right, &_down, &_left);
	Serial.println("Finish one");
}
