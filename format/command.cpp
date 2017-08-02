//----------------------------------------------------------------
//  Module name:
//      command.cpp
//  Languange:
//      C++
//  Description:
//      The module implements commands for XBee transfer
//  Author:
//      Man Sun, Mingxiao An
//----------------------------------------------------------------

#include "Arduino.h"
#include "../headers/game.h"
#include "../headers/command.h"
#include "../headers/display.h"
#include "../headers/move.h"

#define TERMINATOR '\t'

namespace command {
    int speed;
    Boxes boxes;

    enum Command {
        PLOT_ANIMA = 1,
        CHOOSE,
        GAME_START,
        GAME_END,
        GAME_OPEN = 5,
        RIGHT_OPEN,
        WRONG_OPEN,
        READY,
        SETTING_START,
        SETTING_MENU = 10,
        MOVE_BEGIN,
        MOVE_SWAP,
        MOVE_END,
        TUTORIAL_START,
        TUTORIAL_DOWN = 15,
        TUTORIAL_UP,
        TUTORIAL_END
    };

    inline void transferString(char const* str) {
        Serial.print(str);
        Serial.print(TERMINATOR);
    }

    inline void transferNum(int num) {
        Serial.print(num);
        Serial.print(' ');
    }

    inline void transferFinish() {
        Serial.print('\n');
    }

    inline void keepMoving(Boxes& boxes) {
        do {
            display::plotAnima(boxes);
            delay(20);
        } while(move::nextFrame(boxes));
    }

    inline int _step() {
        return random((speed + 1) / 2, (speed + 4) / 2);
    }

}

void command::plotAnima() {
    transferNum(Command::PLOT_ANIMA);
    transferFinish();
}

void command::choose(int boxNo) {
    transferNum(Command::CHOOSE);
    transferNum(boxNo);
    transferFinish();
}

void command::gameStart() {
    transferNum(Command::GAME_START);
    transferFinish();
}

void command::gameEnd() {
    transferNum(Command::GAME_END);
    transferFinish();
}

void command::gameOpen(int choice) {
    transferNum(Command::GAME_OPEN);
    transferNum(choice);
    transferFinish();
}

void command::rightOpen(int choice) {
    transferNum(Command::RIGHT_OPEN);
    transferNum(choice);
    transferFinish();
}

void command::wrongOpen(int choice) {
    transferNum(Command::WRONG_OPEN);
    transferNum(choice);
    transferFinish();
}

void command::ready(char const* info) {
    transferNum(Command::READY);
    transferString(info);
    transferFinish();
}

void command::settingStart() {
    transferNum(Command::SETTING_START);
    transferFinish();
}

void command::settingMenu
(int itemNo, int value, int line) {
    transferNum(Command::SETTING_MENU);
    transferNum(itemNo);
    transferNum(value);
    transferNum(line);
    transferFinish();
}

void command::moveBegin(int num, int speed) {
    transferNum(Command::MOVE_BEGIN);
    transferNum(num);
    transferNum(speed);
    transferFinish();
}

void command::moveSwap(int boxA, int boxB) {
    transferNum(Command::MOVE_SWAP);
    transferNum(boxA);
    transferNum(boxB);
    transferFinish();
}

void command::moveEnd() {
    transferNum(Command::MOVE_END);
    transferFinish();
}

void command::tutorialStart() {
    transferNum(Command::TUTORIAL_START);
    transferFinish();
}

bool command::tutorialUp() {
    transferNum(Command::TUTORIAL_UP);
    transferFinish();
    return true;
}

bool command::tutorialDown() {
    transferNum(Command::TUTORIAL_DOWN);
    transferFinish();
    return true;
}

bool command::tutorialEnd() {
    transferNum(Command::TUTORIAL_END);
    transferFinish();
    return false;
}

void command::receiveEvent() {
    int recVal0,recVal1,recVal2,recVal3;
    // char const* recStr;
    String recStr;
    bool clkws;
    Command cmd = (Command) Serial.parseInt();
    switch(cmd) {
        case Command::PLOT_ANIMA:
            Serial.println("plotAnima");
            display::plotAnima(boxes);
            break;
        case Command::CHOOSE:
            Serial.println("choose");
            recVal0 = Serial.parseInt();
            Serial.println(recVal0);
            display::choose(boxes,recVal0);
            break;
        case Command::GAME_START:
            Serial.println("gameStart");
            display::gameStart(boxes);
            break;
        case Command::GAME_END:
            move::begin(boxes);
            Serial.println("gameEnd");
            display::gameEnd(boxes);
            break;
        case Command::GAME_OPEN:
            recVal0 = Serial.parseInt();
            Serial.println("gameOpen");
            display::gameOpen(boxes,recVal0);
            break;
        case Command::RIGHT_OPEN:
            recVal0 = Serial.parseInt();
            Serial.println("rightOpen");
            display::rightOpen(boxes,recVal0);
            break;
        case Command::WRONG_OPEN:
            recVal0 = Serial.parseInt();
            Serial.println("wrongOpen");
            display::wrongOpen(boxes,recVal0);
            break;
        case Command::READY:
            // recStr = (Serial.readStringUntil(TERMINATOR)).c_str();
            recStr = Serial.readStringUntil(TERMINATOR);
            Serial.println("ready");
            Serial.println(recStr);
            display::ready(recStr);
            break;
        case Command::SETTING_START:
            display::settingStart();
            Serial.println("settingStart");
            break;
        case Command::SETTING_MENU:
            recVal0 = Serial.parseInt();
            recVal1 = Serial.parseInt();
            recVal2 = Serial.parseInt();
            Serial.println("settingMenu");
            display::settingMenu(
                script[recVal0],
                recVal1,
                _min[recVal0],
                _max[recVal0], 
                recVal2
            );
            break;
        case Command::MOVE_BEGIN:
            recVal0 = Serial.parseInt();
            boxes.num = recVal0;
            speed = Serial.parseInt();
            Serial.println("moveBegin");
            move::begin(boxes);
            keepMoving(boxes);
            break;
        case Command::MOVE_SWAP:
            recVal0 = Serial.parseInt();
            recVal1 = Serial.parseInt();
            Serial.println("moveSwap");
            clkws = random(0, 2);
            move::swap(boxes,recVal0,recVal1,clkws,_step());
            keepMoving(boxes);
            break;
        case Command::MOVE_END:
            Serial.println("moveEnd");
            move::end();
            keepMoving(boxes);
            move::begin(boxes);
            break;
        case Command::TUTORIAL_START:
            Serial.println("tutorialStart");
            display::tutorialStart();
            break;
        case Command::TUTORIAL_END:
            Serial.println("tutorialEnd");
            // display::tutorialEnd();
            break;
        case Command::TUTORIAL_UP:
            Serial.println("tutorialUp");
            display::tutorialUp();
            break;
        case Command::TUTORIAL_DOWN:
            Serial.println("tutorialDown");
            display::tutorialDown();
            break;
    }
}
