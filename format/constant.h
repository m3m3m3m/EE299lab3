//----------------------------------------------------------------
//  Module name:
//      constant.h
//  Languange:
//      C++
//  Description:
//      The module defines global constants
//  Author:
//      Mingxiao An
//----------------------------------------------------------------

#ifndef CONSTANT_H
#define CONSTANT_H

#define MASTER 1
#define SLAVE 2
#define TEST 3

#define LCD_PORT 2, 3, 4, 5, 6, 7, 8
#define LCD_WIDTH 16
#define LCD_HEIGHT 2
#define LCD_SIZE LCD_WIDTH, LCD_HEIGHT
#define BAUD_RATE 9600

#define MAX_BOXES 8
#define MAX_CHARS 8

#define UP_PIN 2
#define RIGHT_PIN 3
#define DOWN_PIN 4
#define LEFT_PIN 5

#define SETTING_PIN UP_PIN
#define CONFIRM_PIN RIGHT_PIN
#define TUTORIAL_PIN DOWN_PIN
#define RESTART_PIN LEFT_PIN

#define X_PIN 8
#define Y_PIN 9
#define X_LEFT(x) ((x) < 256)
#define X_RIGHT(x) ((x) >= 768)
#define Y_UP(y) ((y) >= 768)
#define Y_DOWN(y) ((y) < 256)

#define NUM 0
#define SPEED 1
#define DIFFI 2

const int _min[] = {3, 1, 1};
const int _max[] = {7, 7, 7};
const char script[][11] = {
    "Box Number",
    "Move Speed",
    "Difficulty"
};

#endif  // CONSTANT_H
