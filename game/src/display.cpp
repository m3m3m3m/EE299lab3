
#include <LiquidCrystal.h>
#include "../headers/constant.h"

namespace display {

	LiquidCrystal *lcd;

	void begin() {
		lcd = new LiquidCrystal(LCD_PORT);
		lcd->begin(LCD_SIZE);
	}
}
