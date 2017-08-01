
#include "Arduino.h"
#include "../headers/game.h"

void slave::setup() {
	Serial.begin(BAUD_RATE);
}

void slave::loop() {
	if (Serial.available() > 0) {
		Serial.println("Received");
		String a = Serial.readString();
		Serial.println(a);
	}
}
