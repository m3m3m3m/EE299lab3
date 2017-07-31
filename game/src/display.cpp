
#include <LiquidCrystal.h>
#include "../headers/game.h"
#include "../headers/graph.h"

namespace display {

	LiquidCrystal *lcd;
	Char display[LCD_WIDTH][LCD_HEIGHT];

	void begin() {
		lcd = new LiquidCrystal(LCD_PORT);
		lcd->begin(LCD_SIZE);
	}

	void _initDisplay() {
		
	}
}
