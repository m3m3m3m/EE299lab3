
#include "Arduino.h"
#include "../headers/constant.h"
#include "../headers/control.h"

#define UNTIL_RELEASE(pin) while (!digitalRead(pin)) delay(5)
#define UNTIL_RETURN(mode) while(mode) delay(5)

namespace control {
	bool confirm() { return false; }
	bool nothing() { return true; }
}

void control::begin() {
	pinMode(SETTING_PIN, INPUT);
	pinMode(CONFIRM_PIN, INPUT);
	pinMode(TUTORIAL_PIN, INPUT);
	pinMode(RESTART_PIN, INPUT);
	pinMode(X_PIN, INPUT);
	pinMode(Y_PIN, INPUT);
}

void control::attachButton(callback up, callback right, callback down, callback left) {
	bool flag = true;
	while (flag) {
		if (!digitalRead(UP_PIN)) {
			UNTIL_RELEASE(UP_PIN);
			flag = (*up)();
		} else if (!digitalRead(RIGHT_PIN)) {
			UNTIL_RELEASE(RIGHT_PIN);
			flag = (*right)();
		} else if (!digitalRead(DOWN_PIN)) {
			UNTIL_RELEASE(DOWN_PIN);
			flag = (*down)();
		} else if (!digitalRead(LEFT_PIN)) {
			UNTIL_RELEASE(LEFT_PIN);
			flag = (*left)();
		}
		delay(5);
	}
}

void control::attachRod(callback up, callback right, callback down, callback left) {
	bool flag = true;
	while (flag) {
		if (Y_UP(analogRead(Y_PIN))) {
			UNTIL_RETURN(Y_UP(analogRead(Y_PIN)));
			flag = (*up)();
		} else if (X_RIGHT(analogRead(X_PIN))) {
			UNTIL_RETURN(X_RIGHT(analogRead(X_PIN)));
			flag = (*right)();
		} else if (Y_DOWN(analogRead(Y_PIN))) {
			UNTIL_RETURN(Y_DOWN(analogRead(Y_PIN)));
			flag = (*down)();
		} else if (X_LEFT(analogRead(X_PIN))) {
			UNTIL_RETURN(X_LEFT(analogRead(X_PIN)));
			flag = (*left)();
		}
		delay(5);
	}
}

void control::attachPad(
	callback rodUp, callback rodRight, callback rodDown, callback rodLeft,
	callback buttonUp, callback buttonRight, callback buttonDown, callback buttonLeft) {
	bool flag = true;
	while (flag) {
		if (Y_UP(analogRead(Y_PIN))) {
			UNTIL_RETURN(Y_UP(analogRead(Y_PIN)));
			flag = (*rodUp)();
		} else if (X_RIGHT(analogRead(X_PIN))) {
			UNTIL_RETURN(X_RIGHT(analogRead(X_PIN)));
			flag = (*rodRight)();
		} else if (Y_DOWN(analogRead(Y_PIN))) {
			UNTIL_RETURN(Y_DOWN(analogRead(Y_PIN)));
			flag = (*rodDown)();
		} else if (X_LEFT(analogRead(X_PIN))) {
			UNTIL_RETURN(X_LEFT(analogRead(X_PIN)));
			flag = (*rodLeft)();
		} else if (!digitalRead(UP_PIN)) {
			UNTIL_RELEASE(UP_PIN);
			flag = (*buttonUp)();
		} else if (!digitalRead(RIGHT_PIN)) {
			UNTIL_RELEASE(RIGHT_PIN);
			flag = (*buttonRight)();
		} else if (!digitalRead(DOWN_PIN)) {
			UNTIL_RELEASE(DOWN_PIN);
			flag = (*buttonDown)();
		} else if (!digitalRead(LEFT_PIN)) {
			UNTIL_RELEASE(LEFT_PIN);
			flag = (*buttonLeft)();
		}
		delay(5);
	}
}
