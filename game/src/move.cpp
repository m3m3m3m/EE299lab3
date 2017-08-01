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
#define RIGHTCOL 92

namespace move {
	enum phase {BEGIN, SWITCH_OUT, SWITCH_HOR, SWITCH_BAK, END} crtPhase;
	int stepLen;
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
		if(col < LEFTCOL || col > RIGHTCOL) return;
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
		if(getRow(boxes,boxNo) + step > BOTTOMROW) setRow(boxes,boxNo,BOTTOMROW);
		else boxes.pos[boxNo].r += step;
	}

	// move the certain box up by step bit(s)
	void moveUp(Boxes &boxes, int boxNo, int step = 1) {
		if(getRow(boxes,boxNo) == TOPROW) return;
		if(getRow(boxes,boxNo) - step < TOPROW) setRow(boxes,boxNo,TOPROW);
		else boxes.pos[boxNo].r -= step;
	}

	// move the certain box left by step bit(s)
	void moveLeft(Boxes &boxes, int boxNo, int step = 1) {
		if(getCol(boxes,boxNo) == LEFTCOL) return;
		if(getCol(boxes,boxNo) - step < LEFTCOL) setCol(boxes,boxNo,LEFTCOL);
		else boxes.pos[boxNo].c -= step;
	}

	// move the certain box right by step bit(s)
	void moveRight(Boxes &boxes, int boxNo, int step = 1) {
		if(getCol(boxes,boxNo) == RIGHTCOL) return;
		if(getCol(boxes,boxNo) + step > RIGHTCOL) setCol(boxes,boxNo,RIGHTCOL);
		else boxes.pos[boxNo].c += step;
	}

	// set all the box in boxes to the central from left to right
	void initPos(Boxes &boxes)
	{
		int margin = (LCDWIDTH - boxes.num - blocksBetweenBox * (boxes.num - 1)) / 2;
		for(int i = 0;i<boxes.num;i++)
		{	
			int crtCol = block2col(margin + i * (blocksBetweenBox + 1) + 2);
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
			moveUp(boxes,switchBoxL,stepLen);
			moveDown(boxes,switchBoxR,stepLen);
		} else {
			moveUp(boxes,switchBoxR,stepLen);
			moveDown(boxes,switchBoxL,stepLen);
		}

		if(getRow(boxes,switchBoxL) == (switchClockwise ? TOPROW : BOTTOMROW)) {
			stepsRemain = (switchBoxR - switchBoxL) * (blocksBetweenBox + 1) * BLOCKWIDTH;
			stepsRemain = (stepsRemain + stepLen - 1) / stepLen;
			crtPhase = SWITCH_HOR;
		}
	}

	// move the two swapped boxes horizontally by 1 bit according to the direction
	void switchHorizontal(Boxes &boxes) {
		if(switchClockwise) {
			moveRight(boxes,switchBoxL,stepLen);
			moveLeft(boxes,switchBoxR,stepLen);
		} else {
			moveRight(boxes,switchBoxL,stepLen);
			moveLeft(boxes,switchBoxR,stepLen);
		}

		if(stepsRemain == 0) {
			stepsRemain = MOVEVERSTEPS;
			stepsRemain = (stepsRemain + stepLen - 1) / stepLen;
			crtPhase = SWITCH_BAK;
		}
	}

	// move the two swapped boxes back to the queue by 1 bit according to the direction
	void switchBack(Boxes &boxes) {
		if(switchClockwise) {
			moveDown(boxes,switchBoxL,stepLen);
			moveUp(boxes,switchBoxR,stepLen);
		} else {
			moveDown(boxes,switchBoxR,stepLen);
			moveUp(boxes,switchBoxL,stepLen);
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
			int crtCol = block2col(margin + i * (blocksBetweenBox + 1) + 2);
			setCol(boxes,i,crtCol);
			setRow(boxes,i,BEGINHEIGHT);
		}
	}

	// record the number of the two swapped boxes and the direction
	void swap(Boxes &boxes, int boxA, int boxB, bool clockwise,int step) {
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
		stepLen = step;

		stepsRemain = MOVEVERSTEPS;
		stepsRemain = (stepsRemain + stepLen - 1) / stepLen;
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