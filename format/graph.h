//----------------------------------------------------------------
//  Module name:
//      graph.h
//  Languange:
//      C++
//  Description:
//      The module defines character bitmaps to show on lcd
//  Author:
//      Man Sun
//----------------------------------------------------------------

#ifndef GRAPH_H
#define GRAPH_H

#include "Arduino.h"

// category: 0 for vertical, line: 1,2
// category: 1 for horizontal with one stay in the bottom, line: 1
// category: 2 for horizontal in the top, line: 1
// category: 3 for horizontal with one stay in the top, line: 2
// category: 4 for horizontal in the bottom, line: 2
#define VERTICAL 0
#define HORIZONTAL_LINE1_WITH 1
#define HORIZONTAL_LINE1 2
#define HORIZONTAL_LINE2_WITH 3
#define HORIZONTAL_LINE2 4

static byte bitmaps[5][12][8] = {
    {
        // line:1,2 ; cat:0
        {
            B01110,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B10001,
            B01110,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B10101,
            B10001,
            B01110,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B10001,
            B10101,
            B10001,
            B01110,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B01110,
            B10001,
            B10101,
            B10001,
            B01110,
            B00000,
            B00000,
            B00000
        }, {
            B00000,
            B01110,
            B10001,
            B10101,
            B10001,
            B01110,
            B00000,
            B00000
        }, {
            B00000,
            B00000,
            B01110,
            B10001,
            B10101,
            B10001,
            B01110,
            B00000
        }, {
            B00000,
            B00000,
            B00000,
            B01110,
            B10001,
            B10101,
            B10001,
            B01110
        }, {
            B00000,
            B00000,
            B00000,
            B00000,
            B01110,
            B10001,
            B10101,
            B10001
        }, {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B01110,
            B10001,
            B10101
        }, {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B01110,
            B10001
        }, {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B01110
        }
    }, {
        // line:1 ; cat:1
        {
            B00000,
            B10000,
            B10000,
            B10000,
            B00000,
            B00000,
            B01110,
            B10001
        }, {
            B10000,
            B01000,
            B01000,
            B01000,
            B10000,
            B00000,
            B01110,
            B10001
        }, {
            B11000,
            B00100,
            B10100,
            B00100,
            B11000,
            B00000,
            B01110,
            B10001
        }, {
            B11100,
            B00010,
            B01010,
            B00010,
            B11100,
            B00000,
            B01110,
            B10001
        }, {
            B01110,
            B10001,
            B10101,
            B10001,
            B01110,
            B00000,
            B01110,
            B10001
        }, {
            B00111,
            B01000,
            B01010,
            B01000,
            B00111,
            B00000,
            B01110,
            B10001
        }, {
            B00011,
            B00100,
            B00101,
            B00100,
            B00011,
            B00000,
            B01110,
            B10001
        }, {
            B00001,
            B00010,
            B00010,
            B00010,
            B00001,
            B00000,
            B01110,
            B10001
        }, {
            B00000,
            B00001,
            B00001,
            B00001,
            B00000,
            B00000,
            B01110,
            B10001
        },  {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B01110,
            B10001
        },  {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B01110,
            B10001
        },  {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B01110,
            B10001
        }
    }, {
        // line:1 ; cat:2
        {
            B00000,
            B10000,
            B10000,
            B10000,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B10000,
            B01000,
            B01000,
            B01000,
            B10000,
            B00000,
            B00000,
            B00000
        }, {
            B11000,
            B00100,
            B10100,
            B00100,
            B11000,
            B00000,
            B00000,
            B00000
        }, {
            B11100,
            B00010,
            B01010,
            B00010,
            B11100,
            B00000,
            B00000,
            B00000
        }, {
            B01110,
            B10001,
            B10101,
            B10001,
            B01110,
            B00000,
            B00000,
            B00000
        }, {
            B00111,
            B01000,
            B01010,
            B01000,
            B00111,
            B00000,
            B00000,
            B00000
        }, {
            B00011,
            B00100,
            B00101,
            B00100,
            B00011,
            B00000,
            B00000,
            B00000
        }, {
            B00001,
            B00010,
            B00010,
            B00010,
            B00001,
            B00000,
            B00000,
            B00000
        }, {
            B00000,
            B00001,
            B00001,
            B00001,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }
    }, {
        // line:2 ; cat:3
        {
            B10001,
            B01110,
            B00000,
            B00000,
            B10000,
            B10000,
            B10000,
            B00000
        }, {
            B10001,
            B01110,
            B00000,
            B10000,
            B01000,
            B01000,
            B01000,
            B10000
        }, {
            B10001,
            B01110,
            B00000,
            B11000,
            B00100,
            B10100,
            B00100,
            B11000
        }, {
            B10001,
            B01110,
            B00000,
            B11100,
            B00010,
            B01010,
            B00010,
            B11100
        }, {
            B10001,
            B01110,
            B00000,
            B01110,
            B10001,
            B10101,
            B10001,
            B01110
        }, {
            B10001,
            B01110,
            B00000,
            B00111,
            B01000,
            B01010,
            B01000,
            B00111
        }, {
            B10001,
            B01110,
            B00000,
            B00011,
            B00100,
            B00101,
            B00100,
            B00011
        }, {
            B10001,
            B01110,
            B00000,
            B00001,
            B00010,
            B00010,
            B00010,
            B00001
        }, {
            B10001,
            B01110,
            B00000,
            B00000,
            B00001,
            B00001,
            B00001,
            B00000
        }, {
            B10001,
            B01110,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B10001,
            B01110,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B10001,
            B01110,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }
    }, {
        // line:2 ; cat:4
        {
            B00000,
            B00000,
            B00000,
            B00000,
            B10000,
            B10000,
            B10000,
            B00000
        }, {
            B00000,
            B00000,
            B00000,
            B10000,
            B01000,
            B01000,
            B01000,
            B10000
        }, {
            B00000,
            B00000,
            B00000,
            B11000,
            B00100,
            B10100,
            B00100,
            B11000
        }, {
            B00000,
            B00000,
            B00000,
            B11100,
            B00010,
            B01010,
            B00010,
            B11100
        }, {
            B00000,
            B00000,
            B00000,
            B01110,
            B10001,
            B10101,
            B10001,
            B01110
        }, {
            B00000,
            B00000,
            B00000,
            B00111,
            B01000,
            B01010,
            B01000,
            B00111
        }, {
            B00000,
            B00000,
            B00000,
            B00011,
            B00100,
            B00101,
            B00100,
            B00011
        }, {
            B00000,
            B00000,
            B00000,
            B00001,
            B00010,
            B00010,
            B00010,
            B00001
        }, {
            B00000,
            B00000,
            B00000,
            B00000,
            B00001,
            B00001,
            B00001,
            B00000
        }, {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }, {
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000,
            B00000
        }
    }
};

static byte box[] =  {
    B00000,
    B01110,
    B10001,
    B10101,
    B10001,
    B01110,
    B00000,
    B00000
};

static byte bracketL[] = {
    B00111,
    B00100,
    B00100,
    B00100,
    B00100,
    B00100,
    B00111,
    B00000
};

static byte bracketR[] = {
    B11100,
    B00100,
    B00100,
    B00100,
    B00100,
    B00100,
    B11100,
    B00000
};

static byte openBox[] = {
    B00000,
    B01110,
    B11111,
    B10101,
    B10001,
    B01110,
    B00000,
    B00000
};

static byte openRight[] = {
    B00000,
    B00000,
    B00000,
    B01010,
    B10101,
    B10001,
    B01010,
    B00100
};

static byte openWrong[] = {
    B00000,
    B00000,
    B00000,
    B10001,
    B01010,
    B00100,
    B01010,
    B10001
};

static byte leftArrow[] = {
    B00000,
    B00001,
    B00011,
    B00111,
    B01111,
    B00111,
    B00011,
    B00001
};

static byte rightArrow[] = {
    B00000,
    B10000,
    B11000,
    B11100,
    B11110,
    B11100,
    B11000,
    B10000
};

static String tutorialLine1 = "BTN_UP - SETTING";
static String tutorialLine2 = "BTN_RT - CONFIRM";
static String tutorialLine3 = "BTN_DN -    HELP";
static String tutorialLine4 = "JOYSTK -  MOVING";

#endif  // GRAPH_H