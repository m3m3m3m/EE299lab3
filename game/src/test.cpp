
#include "Arduino.h"
#include "../headers/display.h"

namespace test {
	void setup() {
		Serial.begin(BAUD_RATE);
		display::begin();
		Boxes boxes = {
			.num = 4,
			.pos = {
				{2, 8},
				{38, 8},
				{44, 8},
				{65, 2}
			}
		};
		display::plotAnima(boxes);
	}

	void loop() {
		delay(1000);
	}
}
