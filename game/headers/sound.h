

#ifndef SOUND_H
#define SOUND_H
#define BUZZER_PORT 9

#include "pitches.h"

int melody[][5] = {
	{ NOTE_C4, NOTE_E4, NOTE_G4, NOTE_E4, NOTE_G4 },
	{ NOTE_G3, NOTE_G3 }
};

int noteDurations[][5]{
	{ 375, 125, 375, 125, 1000 },
	{ 500, 1500 }
};

void soundSuccess{
	for (i = 0; i < 5; i++) {
		tone(BUZZER_PORT, melody[0][i], noteDuration[0][i]);
		delay(noteDuration[0][i] * 1.30);
	}
}

void soundWA{
	for (i = 0; i < 2; i++) {
		tone(BUZZER_PORT, melody[1][i], noteDuration[1][i]);
		delay(noteDuration[1][i] * 1.30);
	}
}