#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include "connect4.h"

void boardInit(board_t* b){
	b->selectedCol = 3;
	uint8_t row;
	for(row = 0; row < 6; ++row){
		uint8_t col;
		for(col = 0; col < 7; ++col){
			b->gameState[row][col] = EMPTY;
		}
	}
}

void drawBoardBackground(void){
	gfx_SetColor(BOARD_BG_CLR);
	gfx_FillRectangle_NoClip(0, 0, BOARD_WIDTH, BOARD_HEIGHT);
}

void drawPieces(board_t* b){
	uint8_t row;
	for(row = 0; row < 6; ++row){
		uint8_t col;
		for(col = 0; col < 7; ++col){
			gfx_SetColor(b->gameState[row][col]);
			uint16_t x = (BOARD_WIDTH/7)*col + BOARD_WIDTH/14;
			uint16_t y = (BOARD_HEIGHT/6)*row + BOARD_WIDTH/14;
			gfx_FillCircle_NoClip(x, y, 10);
		}
	}
}

void drawSelectedCol(board_t* b){
	gfx_SetColor(SELECTED_COL_CLR);
	gfx_FillRectangle_NoClip(b->selectedCol*(BOARD_WIDTH/7) + 5, 0, BOARD_HEIGHT/7, 210);
}

int main(void){
	board_t board;
	boardInit(&board);

	//screen is 320 wide x 240 high

	gfx_Begin();

	drawBoardBackground(); 
	drawSelectedCol(&board);
	drawPieces(&board);

	do {
		kb_key_t key;
		kb_Scan();

		// Load group 7 registers
		key = kb_Data[7];

		switch (key)
		{
				case kb_Right:     
						board.selectedCol = (board.selectedCol + 1) % 7;
						drawBoardBackground();
						drawSelectedCol(&board);
						drawPieces(&board);
						delay(200);
						break;
				case kb_Left:           /* Change screen color to a different red */
						board.selectedCol = board.selectedCol == 0? 6 : (board.selectedCol - 1) % 7;
						drawBoardBackground();
						drawSelectedCol(&board);
						drawPieces(&board);
						delay(200);
						break;
				default:
						break;
		}
    } while (kb_Data[1] != kb_2nd);


	while(!os_GetCSC());
	gfx_End();

	return 0;
}
