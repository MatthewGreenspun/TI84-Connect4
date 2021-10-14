#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include "connect4.h"

board_t board;
void boardInit(void){
	board.selectedCol = 4;
	uint8_t row;
	for(row = 0; row < 6; ++row){
		uint8_t col;
		for(col = 0; col < 7; ++col){
			board.gameState[row][col] = EMPTY;
		}
	}
}

void drawBoard(void){
	gfx_SetColor(BOARD_BG_CLR);
	gfx_FillRectangle_NoClip(0, 0, 300, 210);
}

void drawPieces(void){
	uint8_t row;
	for(row = 0; row < 6; ++row){
		uint8_t col;
		for(col = 0; col < 7; ++col){
			gfx_SetColor(board.gameState[row][col]);
			uint16_t x = (BOARD_WIDTH/7)*col + BOARD_WIDTH/14;
			uint16_t y = (BOARD_HEIGHT/6)*row + BOARD_WIDTH/14;
			gfx_FillCircle_NoClip(x, y, 10);
		}
	}
}

void drawSelectedCol(void){
	gfx_SetColor(SELECTED_COL_CLR);
	gfx_FillRectangle_NoClip(board.selectedCol*(BOARD_WIDTH/7) + 5, 0, BOARD_HEIGHT/7, 210);
}

int main(void){
	boardInit();

	//screen is 320 wide x 240 high

	gfx_Begin();

	drawBoard(); 
	drawSelectedCol();
	drawPieces();

	do {
		kb_key_t key;
		kb_Scan();

		// Load group 7 registers
		key = kb_Data[7];

		switch (key)
		{
				case kb_Right:     
						board.selectedCol = (board.selectedCol + 1) % 7;
						drawBoard();
						drawSelectedCol();
						drawPieces();
						delay(200);
						break;
				case kb_Left:           /* Change screen color to a different red */
						board.selectedCol = board.selectedCol == 0? 6 : (board.selectedCol - 1) % 7;
						drawBoard();
						drawSelectedCol();
						drawPieces();
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
