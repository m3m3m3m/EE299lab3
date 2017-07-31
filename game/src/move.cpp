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

	int block2col(int blockCol) {
		return (BLOCKWIDTH * blockCol - BLOCKWIDTH/2 - 1);
	}

	int getCol(Boxes &boxes, int boxNo) {
		return (boxes.pos[boxNo].c);
	}

	int getRow(Boxes &boxes, int boxNo) {
		return (boxes.pos[boxNo].r);
	}

	void setCol(Boxes &boxes, int boxNo, int col) {
		if(col < LEFTCOL || col > RIGHTROL) return;
		boxes.pos[boxNo].c = col;
	}

	void setRow(Boxes &boxes, int boxNo, int row) {
		if(row < TOPROW || row > BOTTOMROW) return;
		boxes.pos[boxNo].r = row;
	}

	void moveDown(Boxes &boxes, int boxNo, int step = 1) {
		if(getRow(boxes,boxNo) == BOTTOMROW) return;
		boxes.pos[boxNo].r += step;
	}

	void moveUp(Boxes &boxes, int boxNo, int step = 1) {
		if(getRow(boxes,boxNo) == TOPROW) return;
		boxes.pos[boxNo].r -= step;
	}

	void moveLeft(Boxes &boxes, int boxNo, int step = 1) {
		if(getCol(boxes,boxNo) == LEFTCOL) return;
		boxes.pos[boxNo].c -= step;
	}

	void moveRight(Boxes &boxes, int boxNo, int step = 1) {
		if(getCol(boxes,boxNo) == RIGHTROL) return;
		boxes.pos[boxNo].c += step;
	}

	void initPos(Boxes &boxes)
	{
		for(int i = 0;i<boxes.num;i++)
		{	
			int crtCol = block2col((i + 1) * (blocksBetweenBox + 1));
			setCol(boxes,i,crtCol);
			setRow(boxes,i,BLOCKHEIGHT);
		}
	}

	void beginMove(Boxes &boxes) {
		for(int i = 0;i<boxes.num;i++) {
			moveUp(boxes,i);
		}
	}

	void switchOut(Boxes &boxes) {
		if(switchClockwise) {
			moveUp(boxes,switchBoxL);
			moveDown(boxes,switchBoxR);
		} else {
			moveUp(boxes,switchBoxR);
			moveDown(boxes,switchBoxL);
		}

		if(getRow(boxes,switchBoxL) == (switchClockwise ? TOPROW : BOTTOMROW)) {
			stepsRemain = (switchBoxR - switchBoxL) * (blocksBetweenBox + 1);
			crtPhase = SWITCH_HOR;
		}
	}

	void switchHorizontal(Boxes &boxes) {
		if(switchClockwise) {
			moveRight(boxes,switchBoxL);
			moveLeft(boxes,switchBoxR);
		} else {
			moveRight(boxes,switchBoxR);
			moveLeft(boxes,switchBoxL);
		}

		if(stepsRemain == 0) {
			stepsRemain = MOVEVERSTEPS;
			crtPhase = SWITCH_BAK;
		}
	}

	void switchBack(Boxes &boxes) {
		if(switchHorizontal) {
			moveDown(boxes,switchBoxL);
			moveUp(boxes,switchBoxR);
		} else {
			moveDown(boxes,switchBoxR);
			moveUp(boxes,switchBoxL);
		}
	}

	void endMove(Boxes &boxes) {
		for(int i = 0;i<boxes.num;i++) {
			moveDown(boxes,i);
		}
	}
	void begin(Boxes &boxes) {
		crtPhase = BEGIN;
		stepsRemain = BEGINFRAMES;
		blocksBetweenBox = LCDWIDTH / (boxes.num + 1) - 1;
		for(int i = 0;i<boxes.num;i++)
		{	
			int crtCol = block2col((i + 1) * (blocksBetweenBox + 1));
			setCol(boxes,i,crtCol);
			setRow(boxes,i,BEGINHEIGHT);
		}
	}

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

	void end() {
		crtPhase = END;
		stepsRemain = ENDFRAMES;
	}

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