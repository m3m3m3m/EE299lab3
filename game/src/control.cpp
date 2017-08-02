
#include "Arduino.h"
#include "../headers/constant.h"
#include "../headers/control.h"

#define UNTIL_RELEASE(pin) while (!digitalRead(pin)) delay(5)
#define UNTIL_RETURN(mode) while(!mode) delay(5)

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
	}
}

void control::attachButton(callback up, callback right, callback down, callback left) {
	
}
