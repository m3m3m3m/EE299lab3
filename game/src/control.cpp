
#include "Arduino.h"
#include "../headers/constant.h"
#include "../headers/control.h"

#define UNTIL_FLASE(pin) while (digitalRead(pin)) delay(5)

void control::begin() {
	pinMode(CONFIRM_PIN, INPUT);
	pinMode(SETTING_PIN, INPUT);
}

bool control::confirm() {
	if (digitalRead(CONFIRM_PIN)) {
		UNTIL_FLASE(CONFIRM_PIN);
		return true;
	} else {
		return false;
	}
}
