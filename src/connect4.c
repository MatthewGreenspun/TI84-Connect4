#include <graphx.h>
#include "connect4.h"

void boardInit(board_t* b){
	b->selectedCol = 3;

	int i;
	for(i = 0; i < 7; i++)
		b->colHeights[i] = 0;

	uint8_t row;
	for(row = 0; row < 6; ++row){
		uint8_t col;
		for(col = 0; col < 7; ++col){
			b->boardState[row][col] = EMPTY;
		}
	}
}

void drawBoardBackground(void){
	gfx_SetColor(BOARD_BG_CLR);
	gfx_FillRectangle_NoClip(BOARD_OFFSET, 0, BOARD_WIDTH, BOARD_HEIGHT);
}

void drawPieces(board_t* b){
	uint8_t row;
	for(row = 0; row < 6; ++row){
		uint8_t col;
		for(col = 0; col < 7; ++col){
			gfx_SetColor(b->boardState[row][col]);
			uint16_t x = (BOARD_WIDTH/7)*col + BOARD_WIDTH/14 + BOARD_OFFSET;
			uint16_t y = (BOARD_HEIGHT/6)*row + BOARD_WIDTH/14;
			gfx_FillCircle_NoClip(x, y, 10);
		}
	}
}

void drawSelectedCol(board_t* b){
	gfx_SetColor(SELECTED_COL_CLR);
	gfx_FillRectangle_NoClip(b->selectedCol*(BOARD_WIDTH/7) + 5 + BOARD_OFFSET, 0, BOARD_HEIGHT/7, 210);
}

bool addPiece(board_t* b, uint8_t col, circleState_t color){
	if(b->colHeights[col] == 6) 
		return false;

	uint8_t row = 5 - b->colHeights[col];
	b->boardState[row][col] = color;
	b->colHeights[col]++;
	return true;
}