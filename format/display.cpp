//----------------------------------------------------------------
//  Module name:
//      display.cpp
//  Languange:
//      C++
//  Description:
//      The module inplements display methods
//  Author:
//      Mingxiao An, Man Sun
//----------------------------------------------------------------

#include "Arduino.h"
#include <LiquidCrystal.h>
#include "../headers/display.h"
#include "../headers/game.h"
#include "../headers/graph.h"
#include "../headers/sound.h"

#define EACH_COL(i) (int i = 0; i < LCD_WIDTH; i ++)
#define EACH_ROW(i) (int i = 0; i < LCD_HEIGHT; i ++)
#define EACH_BOX(i) (int i = 0; i < boxes.num; i ++)

#define LEFTARROW (char)0
#define RIGHTARROW (char)1
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
    int tutorialLine;

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
}

void display::clear() {
    lcd->clear();
}

void display::begin() {
    lcd = new LiquidCrystal(LCD_PORT);
    lcd->begin(LCD_SIZE);
    _initDisplay();
    _refreshDisplay();
}

void display::plotAnima(Boxes& boxes) {
    charListIndex = 0;
    charList[charListIndex++] = bitmaps[VERTICAL][1];
    charList[charListIndex++] = bitmaps[VERTICAL][10];

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

            if (col_relative == -1 && row_relative == -1) { // neither same row or col
                display[i][j].map = NULL;
                display[i][j].smap = ' ';
            } else {
                if (col_relative == -1) {                   // same col without same row
                    display[i][j].map = bitmaps[VERTICAL][row_relative];
                } else {
                    if (row_relative == -1) {               // same row without same col
                        display[i][j].map = bitmaps[
                            j == 0 ? HORIZONTAL_LINE1 : HORIZONTAL_LINE2
                        ][col_relative];
                    } else {                                // both same row and col
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

void display::choose(Boxes& boxes, int select) {
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

void display::ready(char const *s) {
    lcd->setCursor(0, 0);
    lcd->print("                ");
    lcd->setCursor(0, 0);
    lcd->print(s);
}

void display::ready(String& s) {
    lcd->setCursor(0, 0);
    lcd->print("                ");
    lcd->setCursor(0, 0);
    lcd->print(s);
}

void display::gameStart(Boxes& boxes) {
    lcd->clear();
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

void display::gameEnd(Boxes& boxes) {
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

void display::gameOpen(Boxes& boxes, int select) {
    int col = boxes.pos[select].c / 6;
    lcd->setCursor(col, 1);
    lcd->print(OPENBOX);
}

void display::rightOpen(Boxes& boxes, int select) {
    int col = boxes.pos[select].c / 6;
    lcd->setCursor(col, 0);
    lcd->print(OPENRIGHT);
    lcd->setCursor(col-1,1);
    lcd->print(' ');
    lcd->setCursor(col+1,1);
    lcd->print(' ');
    soundSuccess();
}

void display::wrongOpen(Boxes& boxes, int select) {
    int col = boxes.pos[select].c / 6;
    lcd->setCursor(col, 0);
    lcd->print(OPENWRONG);
    lcd->setCursor(col-1,1);
    lcd->print(' ');
    lcd->setCursor(col+1,1);
    lcd->print(' ');
    soundWA();
}

void display::settingStart() {
    lcd->clear();
    lcd->createChar(LEFTARROW,leftArrow);
    lcd->createChar(RIGHTARROW,rightArrow);
}

void display::settingMenu
(char const* item, int value, int min, int max, int line) {
    lcd->setCursor(0,line);
    lcd->print(item);
    lcd->print("   ");
    if(min < value) lcd->print(LEFTARROW);
    else lcd->print(" ");
    lcd->print(value);
    if(max > value) lcd->print(RIGHTARROW);
    else lcd->print(" ");

    if (line == 1) line = 0;
    else line = 1;
    lcd->setCursor(13, line);
    lcd->print(" ");
    lcd->setCursor(15, line);
    lcd->print(" ");
}

void display::tutorialStart() {
    lcd->clear();
    tutorialLine = 0;
    lcd->print(tutorialLine1);
    lcd->setCursor(0, 1);
    lcd->print(tutorialLine2);
}

void display::tutorialUp() {
    switch (tutorialLine) {
        case 1:
            lcd->setCursor(0, 0);
            lcd->print(tutorialLine1);
            lcd->setCursor(0, 1);
            lcd->print(tutorialLine2);
            tutorialLine -= 1;
            break;
        case 2:
            lcd->setCursor(0, 0);
            lcd->print(tutorialLine2);
            lcd->setCursor(0, 1);
            lcd->print(tutorialLine3);
            tutorialLine -= 1;
            break;      
    }
}

void display::tutorialDown() {
    switch (tutorialLine) {
        case 0:
            lcd->setCursor(0, 0);
            lcd->print(tutorialLine2);
            lcd->setCursor(0, 1);
            lcd->print(tutorialLine3);
            tutorialLine += 1;
            break;
        case 1:
            lcd->setCursor(0, 0);
            lcd->print(tutorialLine3);
            lcd->setCursor(0, 1);
            lcd->print(tutorialLine4);
            tutorialLine += 1;
            break;
    }
}
