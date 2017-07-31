
#include <LiquidCrystal.h>
#include "../headers/game.h"
#include "../headers/graph.h"

namespace display {

	LiquidCrystal *lcd;
	Char display[LCD_WIDTH][LCD_HEIGHT];

	void _initDisplay() {
		for (int i = 0; i < LCD_WIDTH; i ++) {
			for (int j = 0; j < LCD_HEIGHT; j ++) {
				display[i][j].smap = ' ';
			}
		}
	}

	void _refreshDisplay() {
		lcd->clear();
		lcd->setCursor(0, 0);
		for (int i = 0; i < LCD_WIDTH; i ++) {
			lcd->write(display[i][0].smap);
		}
		lcd->setCursor(0, 1);
		for (int i = 0; i < LCD_WIDTH; i ++) {
			lcd->write(display[i][1].smap);
		}
	}

	void begin() {
		lcd = new LiquidCrystal(LCD_PORT);
		lcd->begin(LCD_SIZE);
		_initDisplay();
		_refreshDisplay();
	}

}
