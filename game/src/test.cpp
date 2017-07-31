
#include "Arduino.h"
#include "../headers/constant.h"
#include "../headers/display.h"

namespace test {
	void setup() {
		display::begin();
	}

	void loop() {
		delay(1000);
	}
}
