#include "../headers/game.h"

#define BLOCKWIDTH 6
#define BLOCKHEIGHT 8
#define LCDWIDTH 16
#define LCDHEIGHT 2
#define BEGINFRAMES 4
#define BEGINHEIGHT 13
#define ENDFRAMES 4
#define MOVEVERSTEPS 6
#define TOPROW 2
#define BOTTOMROW 14
#define LEFTCOL 2
#define RIGHTROL 92

namespace move {
	enum phase {BEGIN, SWITCH_OUT, SWITCH_HOR, SWITCH_BAK, END} crtPhase;
	int stepsRemain;
	int switchBoxL, switchBoxR;
	bool switchClockwise;
	int blocksBetweenBox;

	// change the number(start from 1) of the block to the column of its central bit(start from 0)
	int block2col(int blockCol) {
		return (BLOCKWIDTH * blockCol - BLOCKWIDTH/2 - 1);
	}

	// get the column of the central bit of the certain box
	int getCol(Boxes &boxes, int boxNo) {
		return (boxes.pos[boxNo].c);
	}

	// get the row of the central bit of the certain box
	int getRow(Boxes &boxes, int boxNo) {
		return (boxes.pos[boxNo].r);
	}

	// set the column of the central bit of the certain box
	void setCol(Boxes &boxes, int boxNo, int col) {
		if(col < LEFTCOL || col > RIGHTROL) return;
		boxes.pos[boxNo].c = col;
	}

	// set the row of the central bit of the certain box
	void setRow(Boxes &boxes, int boxNo, int row) {
		if(row < TOPROW || row > BOTTOMROW) return;
		boxes.pos[boxNo].r = row;
	}

	// move the certain box down by step bit(s)
	void moveDown(Boxes &boxes, int boxNo, int step = 1) {
		if(getRow(boxes,boxNo) == BOTTOMROW) return;
		boxes.pos[boxNo].r += step;
	}

	// move the certain box up by step bit(s)
	void moveUp(Boxes &boxes, int boxNo, int step = 1) {
		if(getRow(boxes,boxNo) == TOPROW) return;
		boxes.pos[boxNo].r -= step;
	}

	// move the certain box left by step bit(s)
	void moveLeft(Boxes &boxes, int boxNo, int step = 1) {
		if(getCol(boxes,boxNo) == LEFTCOL) return;
		boxes.pos[boxNo].c -= step;
	}

	// move the certain box right by step bit(s)
	void moveRight(Boxes &boxes, int boxNo, int step = 1) {
		if(getCol(boxes,boxNo) == RIGHTROL) return;
		boxes.pos[boxNo].c += step;
	}

	// set all the box in boxes to the central from left to right
	void initPos(Boxes &boxes)
	{
		for(int i = 0;i<boxes.num;i++)
		{	
			int crtCol = block2col((i + 1) * (blocksBetweenBox + 1));
			setCol(boxes,i,crtCol);
			setRow(boxes,i,BLOCKHEIGHT);
		}
	}

	// move all the boxes up for 1 bit
	void beginMove(Boxes &boxes) {
		for(int i = 0;i<boxes.num;i++) {
			moveUp(boxes,i);
		}
	}

	// move the two swapped boxes out of the queue by 1 bit according to the direction
	void switchOut(Boxes &boxes) {
		if(switchClockwise) {
			moveUp(boxes,switchBoxL);
			moveDown(boxes,switchBoxR);
		} else {
			moveUp(boxes,switchBoxR);
			moveDown(boxes,switchBoxL);
		}

		if(getRow(boxes,switchBoxL) == (switchClockwise ? TOPROW : BOTTOMROW)) {
			stepsRemain = (switchBoxR - switchBoxL) * (blocksBetweenBox + 1) * BLOCKWIDTH;
			crtPhase = SWITCH_HOR;
		}
	}

	// move the two swapped boxes horizontally by 1 bit according to the direction
	void switchHorizontal(Boxes &boxes) {
		if(switchClockwise) {
			moveRight(boxes,switchBoxL);
			moveLeft(boxes,switchBoxR);
		} else {
			moveRight(boxes,switchBoxL);
			moveLeft(boxes,switchBoxR);
		}

		if(stepsRemain == 0) {
			stepsRemain = MOVEVERSTEPS;
			crtPhase = SWITCH_BAK;
		}
	}

	// move the two swapped boxes back to the queue by 1 bit according to the direction
	void switchBack(Boxes &boxes) {
		if(switchClockwise) {
			moveDown(boxes,switchBoxL);
			moveUp(boxes,switchBoxR);
		} else {
			moveDown(boxes,switchBoxR);
			moveUp(boxes,switchBoxL);
		}
	}

	// move all the boxes down by 1 bit
	void endMove(Boxes &boxes) {
		for(int i = 0;i<boxes.num;i++) {
			moveDown(boxes,i);
		}
	}

	// set all the boxes to their beginning positions
	void begin(Boxes &boxes) {
		crtPhase = BEGIN;
		stepsRemain = BEGINFRAMES;
		blocksBetweenBox = LCDWIDTH / boxes.num - 1;
		int margin = (LCDWIDTH - boxes.num - blocksBetweenBox * (boxes.num - 1)) / 2;
		for(int i = 0;i<boxes.num;i++)
		{	
			int crtCol = block2col(margin + i * (blocksBetweenBox + 1) + 1);
			setCol(boxes,i,crtCol);
			setRow(boxes,i,BEGINHEIGHT);
		}
	}

	// record the number of the two swapped boxes and the direction
	void swap(Boxes &boxes, int boxA, int boxB, bool clockwise) {
		crtPhase = SWITCH_OUT;
		initPos(boxes);
		if (boxA < boxB) {
			switchBoxL = boxA;
			switchBoxR = boxB;
		} else {
			switchBoxL = boxB;
			switchBoxR = boxA;
		}
		switchClockwise = clockwise;

		stepsRemain = MOVEVERSTEPS;
	}

	// set all the boxes to their ending positions
	void end() {
		crtPhase = END;
		stepsRemain = ENDFRAMES;
	}

	// modify the current positions according to the phases and remaining steps
	// return true if there are still remaining steps, false if not
	bool nextFrame(Boxes &boxes) {
		if(stepsRemain == 0) return false;
		else stepsRemain -= 1;
		switch(crtPhase) {
			case BEGIN:
				beginMove(boxes);
				break;
			case SWITCH_OUT:
				switchOut(boxes);
				break;
			case SWITCH_HOR:
				switchHorizontal(boxes);
				break;
			case SWITCH_BAK:
				switchBack(boxes);
				break;
			case END:
				endMove(boxes);
				break;
		}
		return true;
	}
}