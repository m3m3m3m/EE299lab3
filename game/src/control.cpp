
#include "Arduino.h"
#include "../headers/constant.h"
#include "../headers/control.h"

#define UNTIL_FLASE(pin) while (digitalRead(pin)) delay(5)
#define UNTIL_TRUE(pin) while (!digitalRead(pin)) delay(5)

#define FOREVER whlie (true)

void control::begin() {
	pinMode(SETTING_PIN, INPUT);
	pinMode(CONFIRM_PIN, INPUT);
	pinMode(TUTORIAL_PIN, INPUT);
	pinMode(RESTART_PIN, INPUT);
	pinMode(X_PIN, INPUT);
	pinMode(Y_PIN, INPUT);
}

Position control::getButton(callback up, callback right, callback down, callback left) {
	FOREVER {
		if (!digitalRead(up)) {
			return up();
		} else if (!digitalRead(right)) {

		} else if (!digitalRead(down)) {

		} else if (!digitalRead(left){

		}
	}
}
