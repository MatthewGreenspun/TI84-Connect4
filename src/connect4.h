#ifndef CONNECT4_H
#define CONNECT4_H

#define BOARD_WIDTH 300
#define BOARD_HEIGHT 210
#define BOARD_OFFSET 10
#define WHITE 255
#define RED 224
#define YELLOW 231
#define BLUE 26
#define LIGHT_BLUE 27
#define BOARD_BG_CLR 26
#define SELECTED_COL_CLR 27

typedef enum circleState_t {EMPTY = WHITE, RED_PIECE = RED, YELLOW_PIECE = YELLOW, VISITED} circleState_t;

typedef struct board_t {
	circleState_t boardState[6][7];
	uint8_t selectedCol;
	uint8_t colHeights[7];
} board_t;

void boardInit(board_t* b);
void drawBoardBackground(void);
void drawPieces(board_t* b);
void drawSelectedCol(board_t* b);
bool addPiece(board_t* b, uint8_t col, circleState_t color);

#endif
