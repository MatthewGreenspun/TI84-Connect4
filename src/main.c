#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include "connect4.h"
#include <debug.h>

int main(void){
	board_t board;
	bool isRedsTurn = true;
	winner_t winner = NONE;

	const char* redsTurnStr = "Red's turn";
	const char* yellowsTurnStr = "Yellow's turn";
	const char* redWinsStr = "Red wins! Play again?";
	const char* yellowWinsStr = "Yellow wins! Play again?";
	const char* drawStr = "Draw. Play again?";

	boardInit(&board);

	gfx_Begin();
	gfx_SetColor(BLACK);
	gfx_FillRectangle_NoClip(BOARD_OFFSET, BOARD_HEIGHT, BOARD_WIDTH, 20);
	gfx_SetTextBGColor(BLACK);
	gfx_SetTextFGColor(RED);		
	gfx_PrintStringXY(redsTurnStr, BOARD_OFFSET, BOARD_HEIGHT + 5);

	drawBoardBackground(); 
	drawSelectedCol(&board);
	drawPieces(&board);

	delay(400);
	do {
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
			bool validMove = addPiece(&board, board.selectedCol, isRedsTurn? RED_PIECE : YELLOW_PIECE);
			if(validMove){
				drawBoardBackground();
				drawSelectedCol(&board);
				drawPieces(&board);
				gfx_SetColor(BLACK);
				gfx_FillRectangle_NoClip(BOARD_OFFSET, BOARD_HEIGHT, BOARD_WIDTH, 20);
				winner = findWinner(&board);
				if(winner == NONE) {
					if(isDraw(&board)){
						dbg_sprintf(dbgout, drawStr);
						gfx_SetTextFGColor(LIGHT_GRAY);		
						gfx_PrintStringXY(drawStr, BOARD_OFFSET + 1, BOARD_HEIGHT + 5);
						if(continueGame()){
							resetGame(&board);
						} else {
							gfx_End();
							return 0;
						}
					}
					if(isRedsTurn){
						isRedsTurn = false;
						gfx_SetTextFGColor(YELLOW);		
						gfx_PrintStringXY(yellowsTurnStr, BOARD_OFFSET, BOARD_HEIGHT + 5);
					} else {
						isRedsTurn = true;
						gfx_SetTextFGColor(RED);		
						gfx_PrintStringXY(redsTurnStr, BOARD_OFFSET, BOARD_HEIGHT + 5);
					}
				} else {
					if(winner == RED_PLAYER) {
						gfx_SetTextFGColor(RED);
						gfx_PrintStringXY(redWinsStr, BOARD_OFFSET, BOARD_HEIGHT + 5);
					}
					else {
						gfx_SetTextFGColor(YELLOW);
						gfx_PrintStringXY(yellowWinsStr, BOARD_OFFSET, BOARD_HEIGHT + 5);
					}

					if(continueGame()) {
						resetGame(&board);
					} else {
						gfx_End();
						return 0;
					}
				}
			}
			delay(500);
		}
  } while (kb_Data[1] != kb_2nd);

	gfx_End();
	return 0;
}
