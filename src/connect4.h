#ifndef CONNECT4_H
#define CONNECT4_H
#include <stdbool.h>
#include <stdint.h>

#define BOARD_WIDTH 300
#define BOARD_HEIGHT 210
#define BOARD_OFFSET 10

// colors from https://ce-programming.github.io/toolchain/libraries/graphx.html
#define WHITE 255
#define BLACK 0
#define RED 224
#define YELLOW 231
#define DIALOG_SELECTED_CLR 247
#define GRAY 116
#define LIGHT_GRAY 223
#define BLUE 26
#define LIGHT_BLUE 27
#define BOARD_BG_CLR 26
#define SELECTED_COL_CLR 27

typedef enum circleState_t {EMPTY = WHITE, RED_PIECE = RED, YELLOW_PIECE = YELLOW, VISITED} circleState_t;
typedef enum winner_t {NONE, RED_PLAYER, YELLOW_PLAYER} winner_t;
typedef enum direction_t {RIGHT, DOWN, DIAGONAL} direction_t;

typedef struct board_t {
	circleState_t boardState[6][7];
	uint8_t selectedCol;
	uint8_t colHeights[7];
} board_t;

void boardInit(board_t* b);
void copyBoard(board_t* b, board_t* bCopy);
void drawBoardBackground(void);
void drawPieces(board_t* b);
void drawSelectedCol(board_t* b);
bool addPiece(board_t* b, uint8_t col, circleState_t color);
circleState_t oppColor(circleState_t color);
winner_t findWinner(board_t* b);
bool fourEq(circleState_t v1, circleState_t v2, circleState_t v3, circleState_t v4);
bool continueGame(void);
bool isDraw(board_t* b);
void resetGame(board_t* b);

#endif