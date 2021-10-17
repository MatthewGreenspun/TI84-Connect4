#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include "connect4.h"

int main(void){
	board_t board;
	bool isRedsTurn = true;
	const char* redsTurnStr = "red's turn";
	const char* yellowsTurnStr = "yellow's turn";

	boardInit(&board);

	//screen is 320 wide x 240 high

	gfx_Begin();
	gfx_SetColor(BLACK);
	gfx_FillRectangle_NoClip(BOARD_OFFSET, BOARD_HEIGHT + 5, BOARD_WIDTH, 10);
	gfx_SetTextBGColor(BLACK);
	gfx_SetTextFGColor(RED);		
	gfx_PrintStringXY(redsTurnStr, BOARD_OFFSET, BOARD_HEIGHT + 5);

	drawBoardBackground(); 
	drawSelectedCol(&board);
	drawPieces(&board);

	do {
		delay(1000);
		kb_Scan();

		if(kb_Data[7] == kb_Right){
			board.selectedCol = (board.selectedCol + 1) % 7;
			drawBoardBackground();
			drawSelectedCol(&board);
			drawPieces(&board);
			delay(200);
		} else if(kb_Data[7] == kb_Left){
			board.selectedCol = board.selectedCol == 0? 6 : (board.selectedCol - 1) % 7;
			drawBoardBackground();
			drawSelectedCol(&board);
			drawPieces(&board);
			delay(200);
		}

		if(kb_Data[6] == kb_Enter){
			bool moved = addPiece(&board, board.selectedCol, isRedsTurn? RED_PIECE : YELLOW_PIECE);
			drawBoardBackground();
			drawSelectedCol(&board);
			drawPieces(&board);
			if(moved && isRedsTurn){
				isRedsTurn = false;
				gfx_SetTextFGColor(YELLOW);		
				gfx_PrintStringXY(yellowsTurnStr, BOARD_OFFSET, BOARD_HEIGHT + 5);
			}
			else if(moved){
				isRedsTurn = true;
				gfx_SetColor(BLACK);
				gfx_FillRectangle_NoClip(BOARD_OFFSET, BOARD_HEIGHT + 5, BOARD_WIDTH, 10);
				gfx_SetTextFGColor(RED);		
				gfx_PrintStringXY(redsTurnStr, BOARD_OFFSET, BOARD_HEIGHT + 5);
			}
			delay(500);
		}
  } while (kb_Data[1] != kb_2nd);

	gfx_End();
	return 0;
}
