
#include <LiquidCrystal.h>
#include "../headers/game.h"
#include "../headers/graph.h"

#define EACH_COL(i) (int i = 0; i < LCD_WIDTH; i ++)
#define EACH_ROW(i) (int i = 0; i < LCD_HEIGHT; i ++)
#define EACH_BOX(i) (int i = 0; i < boxes.num; i ++)

#define BOX (char)2
#define OPENBOX (char)3
#define OPENRIGHT (char)4
#define OPENWRONG (char)5
#define BRACKETL (char)6
#define BRACKETR (char)7

namespace display {

	LiquidCrystal *lcd;
	Map display[LCD_WIDTH][LCD_HEIGHT];
	Char charList[MAX_CHARS];
	int charListIndex;

	inline int _inCharList(Char ch) {
		for (int i = 0; i < charListIndex; i ++) {
			if (charList[i] == ch) {
				return i;
			}
		}
		return charListIndex;
	}

	inline int _gridCol(int col) {
		return col * 6 - 2;
	}

	inline int _gridRow(int row) {
		return row * 9 - 2;
	}

	inline int _gridColCenter(int col) {
		return col * 6 + 2;
	}

	inline int _gridRowCenter(int row) {
		return row == 0 ? 2: 14;
	}

	void _initDisplay() {
		for EACH_COL(i) {
			for EACH_ROW(j) {
				display[i][j].smap = ' ';
			}
		}
	}

	void _refreshDisplay() {
		for (int i = 0; i < charListIndex; i ++) {
			lcd->createChar(i, charList[i]);
		}
		lcd->setCursor(0, 0);
		for EACH_COL(i) {
			lcd->print(display[i][0].smap);
		}
		lcd->setCursor(0, 1);
		for EACH_COL(i) {
			lcd->print(display[i][1].smap);
		}
	}

	void begin() {
		lcd = new LiquidCrystal(LCD_PORT);
		lcd->begin(LCD_SIZE);
		_initDisplay();
		_refreshDisplay();
	}

	void plotAnima(Boxes& boxes) {
		charListIndex = 0;

		for EACH_COL(i) {
			for EACH_ROW(j) {
				int gridCol = _gridCol(i);
				int gridColCenter = _gridColCenter(i);
				int gridRow = _gridRow(j);
				int gridRowCenter = _gridRowCenter(j);
				int col_relative = -1;
				int row_relative = -1;

				for EACH_BOX(k) {
					// same row first, same col second
					if (boxes.pos[k].r == gridRowCenter) {
						int _relative = boxes.pos[k].c - gridCol;
						if (_relative >= 0 && _relative < 9)
							col_relative = _relative;
					} else if (boxes.pos[k].c == gridColCenter) {
						int _relative = boxes.pos[k].r - gridRow;
						if (_relative >= 0 && _relative < 12)
							row_relative = _relative;
					}
				}

				if (col_relative == -1 && row_relative == -1) {	// neither same row or col
					display[i][j].map = NULL;
					display[i][j].smap = ' ';
				} else {
					if (col_relative == -1) {					// same col without same row
						display[i][j].map = bitmaps[VERTICAL][row_relative];
					} else {
						if (row_relative == -1) {				// same row without same col
							display[i][j].map = bitmaps[
								j == 0 ? HORIZONTAL_LINE1 : HORIZONTAL_LINE2
							][col_relative];
						} else {								// both same row and col
							display[i][j].map = bitmaps[
								j == 0 ? HORIZONTAL_LINE1_WITH: HORIZONTAL_LINE2_WITH
							][col_relative];
						}
					}
					// insert the char to the list if it is a new char
					display[i][j].smap = (char)_inCharList(display[i][j].map);
					if (display[i][j].smap == (char)charListIndex) {
						charList[charListIndex++] = display[i][j].map;
					}
				}
			}
		}

		_refreshDisplay();
	}

	void choose(Boxes& boxes, int select) {
		for EACH_BOX(i) {
			int col = boxes.pos[i].c / 6;
			lcd->setCursor(col - 1, 1);
			lcd->print(' ');
			lcd->setCursor(col + 1, 1);
			lcd->print(' ');
		}
		int col = boxes.pos[select].c / 6;
		lcd->setCursor(col - 1, 1);
		lcd->print(BRACKETL);
		lcd->setCursor(col + 1, 1);
		lcd->print(BRACKETR);
	}

	void ready(char const *s) {
		lcd->setCursor(0, 0);
		lcd->print("                ");
		lcd->setCursor(0, 0);
		lcd->print(s);
	}

	void gameStart(Boxes& boxes) {
		lcd->createChar(BOX, box);
		lcd->createChar(BRACKETL, bracketL);
		lcd->createChar(BRACKETR, bracketR);
		for EACH_BOX(i) {
			int col = boxes.pos[i].c / 6;
			lcd->setCursor(col, 1);
			lcd->print(BOX);
		}
		choose(boxes, 0);
		ready("Choose to start:");
	}

	void gameEnd(Boxes& boxes) {
		lcd->createChar(BOX, box);
		lcd->createChar(OPENBOX, openBox);
		lcd->createChar(OPENRIGHT, openRight);
		lcd->createChar(OPENWRONG, openWrong);
		lcd->createChar(BRACKETL, bracketL);
		lcd->createChar(BRACKETR, bracketR);
		for EACH_BOX(i) {
			int col = boxes.pos[i].c / 6;
			lcd->setCursor(col, 1);
			lcd->print(BOX);
		}
		choose(boxes, 0);
		ready("Choose your box:");
	}

	void gameOpen(Boxes& boxes, int select) {
		
	}

	void rightOpen(Boxes& boxes, int select) {

	}

	void wrongOpen(Boxes& boxes, int select) {
		
	}
}
