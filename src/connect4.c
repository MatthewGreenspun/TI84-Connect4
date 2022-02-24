#include "connect4.h"
#include <graphx.h>
#include <debug.h>
#include <keypadc.h>
#include <tice.h>


void boardInit(board_t *b) {
  b->selectedCol = 3;

  uint8_t i;
  for (i = 0; i < 7; i++)
    b->colHeights[i] = 0;

  uint8_t row;
  for (row = 0; row < 6; ++row) {
    uint8_t col;
    for (col = 0; col < 7; ++col) {
      b->boardState[row][col] = EMPTY;
    }
  }
}

void copyBoard(board_t *b, board_t* bCopy) {
  bCopy->selectedCol = b->selectedCol;

  uint8_t i;
  for (i = 0; i < 7; i++)
    bCopy->colHeights[i] = b->colHeights[i];

  uint8_t row;
  for (row = 0; row < 6; ++row) {
    uint8_t col;
    for (col = 0; col < 7; ++col) {
      bCopy->boardState[row][col] = b->boardState[row][col];
    }
  }
}

void drawBoardBackground(void) {
  gfx_SetColor(BOARD_BG_CLR);
  gfx_FillRectangle_NoClip(BOARD_OFFSET, 0, BOARD_WIDTH, BOARD_HEIGHT);
}

void drawPieces(board_t *b) {
  uint8_t row;
  for (row = 0; row < 6; ++row) {
    uint8_t col;
    for (col = 0; col < 7; ++col) {
      gfx_SetColor(b->boardState[row][col]);
      uint16_t x = (BOARD_WIDTH / 7) * col + BOARD_WIDTH / 14 + BOARD_OFFSET;
      uint16_t y = (BOARD_HEIGHT / 6) * row + BOARD_WIDTH / 14;
      gfx_FillCircle_NoClip(x, y, 10);
    }
  }
}

void drawSelectedCol(board_t *b) {
  gfx_SetColor(SELECTED_COL_CLR);
  gfx_FillRectangle_NoClip(b->selectedCol * (BOARD_WIDTH / 7) + 5 +
                               BOARD_OFFSET,
                           0, BOARD_HEIGHT / 7, 210);
}

bool addPiece(board_t *b, uint8_t col, circleState_t color) {
  if(b->colHeights[col] == 6)
    return false;

  uint8_t row = 5 - b->colHeights[col];
  b->boardState[row][col] = color;
  b->colHeights[col]++;
  return true;
}

circleState_t oppColor(circleState_t color){
	if(color == RED_PIECE) return YELLOW_PIECE;
	return RED_PIECE;
}

bool fourEq(circleState_t v1, circleState_t v2, circleState_t v3, circleState_t v4){
  // dbg_sprintf(dbgout, "\nv1: %d, v2: %d, v3: %d, v4: %d, \nout: %d", v1, v2, v3, v4, (v1 == v2 && v2 == v3 && v3 == v4));
  return (v1 == v2 && v2 == v3 && v3 == v4);
}

winner_t findWinner(board_t *b){
  uint8_t row;
  uint8_t start;
  //check horizontal wins
  for (row = 0; row < 6; row++) {
    for (start = 0; start < 4; start++) {
      if(fourEq(b->boardState[row][start], b->boardState[row][start + 1], b->boardState[row][start + 2], b->boardState[row][start + 3])){
        circleState_t winningColor = b->boardState[row][start];
        if(winningColor != WHITE)
        dbg_sprintf(dbgout, "\n[row winner] by row %d, col %d:  %s", row, start, winningColor == WHITE? "white": winningColor==RED_PIECE?"red":"yellow");
        if(winningColor == RED_PIECE) return RED_PLAYER;
        else if(winningColor == YELLOW_PIECE) return YELLOW_PLAYER;
        continue;
      }
    }
  }

  uint8_t col;
  //check vertical wins
  for (col = 0; col < 7; col++) {
    for (start = 0; start < 3; start++) {
      if(fourEq(b->boardState[start][col], b->boardState[start + 1][col], b->boardState[start + 2][col], b->boardState[start + 3][col])){
        circleState_t winningColor = b->boardState[start][col];
        if(winningColor != WHITE)
        dbg_sprintf(dbgout, "\n[col winner] by row %d, col %d:  %d", start, col, winningColor);
        if(winningColor == RED_PIECE) return RED_PLAYER;
        else if(winningColor == YELLOW_PIECE) return YELLOW_PLAYER;
        continue;
      }
    }
  }

  //check diagonal wins with negative slope
  for(col = 0; col < 4; col++){
    for(row = 0; row < 3; row++){
      if(fourEq(b->boardState[row][col], b->boardState[row + 1][col + 1], b->boardState[row + 2][col + 2], b->boardState[row + 3][col + 3])){
        circleState_t winningColor = b->boardState[row][col];
        if(winningColor != WHITE) {
          dbg_sprintf(dbgout, "\n[diag winner] by row %d, col %d:  %d\n", row, col, winningColor);
          dbg_sprintf(dbgout, "\n(%d,%d): %d\t(%d,%d): %d\t(%d,%d): %d\t(%d,%d): %d\n", row, col, b->boardState[row][col],
                                                                                      row + 1, col + 1, b->boardState[row + 1][col + 1],
                                                                                      row + 2, col + 2, b->boardState[row + 2][col + 2],
                                                                                      row + 3, col + 3, b->boardState[row + 3][col + 3]);
        }
        if(winningColor == RED_PIECE) return RED_PLAYER;
        else if(winningColor == YELLOW_PIECE) return YELLOW_PLAYER;
        continue;
      }
    }
  }

  //check diagonal wins with positive slope
  for(col = 3; col < 7; col++){
    for(row = 0; row < 3; row++){
      if(fourEq(b->boardState[row][col], b->boardState[row + 1][col - 1], b->boardState[row + 2][col - 2], b->boardState[row + 3][col - 3])){
        circleState_t winningColor = b->boardState[row][col];
        if(winningColor != WHITE) {
          dbg_sprintf(dbgout, "\n[diag winner] by row %d, col %d:  %d\n", row, col, winningColor);
          dbg_sprintf(dbgout, "\n(%d,%d): %d\t(%d,%d): %d\t(%d,%d): %d\t(%d,%d): %d\n", row, col, b->boardState[row][col],
                                                                                      row + 1, col - 1, b->boardState[row + 1][col - 1],
                                                                                      row + 2, col - 2, b->boardState[row + 2][col - 2],
                                                                                      row + 3, col - 3, b->boardState[row + 3][col - 3]);
        }
        if(winningColor == RED_PIECE) return RED_PLAYER;
        else if(winningColor == YELLOW_PIECE) return YELLOW_PLAYER;
        continue;
      }
    }
  }
  return NONE;
}

void setDialogColors(bool selected){
  if(selected) {
    gfx_SetColor(DIALOG_SELECTED_CLR);
    gfx_SetTextBGColor(DIALOG_SELECTED_CLR);
  } else {
    gfx_SetColor(GRAY);
    gfx_SetTextBGColor(GRAY);
  }
}

bool continueGame(void) {
  bool yesSelected = true;
  delay(200);
  do {
    kb_Scan();
    if(kb_Data[6] == kb_Enter) break;
    if(kb_Data[7] == kb_Right){
     yesSelected = !yesSelected;
     delay(200);
    }
    if(kb_Data[7] == kb_Left) {
      yesSelected = !yesSelected;
      delay(200);
    }
    
    //draw border around buttons
    gfx_SetColor(BLACK);
    gfx_FillRectangle_NoClip(220, BOARD_HEIGHT + 2, 40, 20);
    gfx_FillRectangle_NoClip(265, BOARD_HEIGHT + 2, 40, 20);

    gfx_SetTextFGColor(BLACK);
    setDialogColors(yesSelected);
    gfx_FillRectangle_NoClip(222, BOARD_HEIGHT + 4, 36, 16);
    gfx_PrintStringXY("Y", 240, BOARD_HEIGHT + 10);

    setDialogColors(!yesSelected);
    gfx_FillRectangle_NoClip(267, BOARD_HEIGHT + 4, 36, 16);
    gfx_PrintStringXY("N", 285, BOARD_HEIGHT + 10);
    delay(100);
  } while(kb_Data[1] != kb_2nd);

  return yesSelected;
}

bool isDraw(board_t* b){
  uint8_t row;
  uint8_t col;
  
  for(row = 0; row < 6; row++){
    for(col = 0; col < 7; col++){
      if(b->boardState[row][col] == WHITE) return false;
    }
  }
  return true;
}

void resetGame(board_t* b){
  gfx_SetColor(WHITE);
  gfx_FillRectangle(0, 0, 310, 240);
  boardInit(b);
  gfx_SetColor(BLACK);
  gfx_FillRectangle_NoClip(BOARD_OFFSET, BOARD_HEIGHT, BOARD_WIDTH, 20);
  gfx_SetTextBGColor(BLACK);
  gfx_SetTextFGColor(RED);		
  gfx_PrintStringXY("Red's turn", BOARD_OFFSET, BOARD_HEIGHT + 5);

  drawBoardBackground(); 
  drawSelectedCol(b);
  drawPieces(b);

  delay(400);
}