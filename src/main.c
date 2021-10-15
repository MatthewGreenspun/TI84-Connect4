#include <tice.h>
#include <graphx.h>
#include <keypadc.h>
#include "connect4.h"

int main(void){
	board_t board;
	bool isRedsTurn = true;

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

		switch (key){
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

		kb_Scan();
		if(kb_Data[6] == kb_Enter){
			bool moved = addPiece(&board, board.selectedCol, isRedsTurn? RED_PIECE : YELLOW_PIECE);
			drawBoardBackground();
			drawSelectedCol(&board);
			drawPieces(&board);
			if(moved && isRedsTurn)
				isRedsTurn = false;
			else if(moved)
				isRedsTurn = true;
			delay(500);
		}
    } while (kb_Data[1] != kb_2nd);

	while(!os_GetCSC());

	gfx_End();

	return 0;
}
