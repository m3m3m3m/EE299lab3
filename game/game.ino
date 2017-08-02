
#include "Arduino.h"
#include "headers/game.h"

#define ROLE MASTER

void setup() {
	#if ROLE == MASTER
	master::setup();
	#elif ROLE == SLAVE
	slave::setup();
	#elif ROLE == TEST
	test::setup();
	#endif	// ROLE
}

void loop() {
	#if ROLE == MASTER
	master::loop();
	#elif ROLE == SLAVE
	slave::loop();
	#elif ROLE == TEST
	test::loop();
	#endif	// ROLE
}
