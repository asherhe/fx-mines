#ifndef MINES_H
#define MINES_H

#include "config.h"

struct MINES_Tile
{
  unsigned int neighbors : 4; // number of mined neighbors
  unsigned int isMine : 1;
  unsigned int isCovered : 1;
  unsigned int isFlagged : 1;
  unsigned int : 1;
};

struct MINES_Game
{
  unsigned int width : 8;
  unsigned int height : 8;

  unsigned int mines : 16;   // number of mines
  unsigned int cleared : 16; // number of cleared tiles
  unsigned int flags : 16;   // number of flags placed

  unsigned int cursorX : 8;
  unsigned int cursorY : 8;

  unsigned int over : 1; // whether the game is over
  unsigned int win : 1;
  unsigned int : 6;

  struct MINES_Tile field[MINES_GRID_WIDTH][MINES_GRID_HEIGHT];
};

// describes all user input options
enum MINES_Input
{
  NONE,
  CURSOR_UP,
  CURSOR_DOWN,
  CURSOR_LEFT,
  CURSOR_RIGHT,
  CLEAR_CELL,
  TOGGLE_FLAG
};

#define MINES_GAME_OVER 1

// initializes a new minesweeper instance
void MINES_InitGame(struct MINES_Game *game);

// updates the game based on user input
void MINES_InputGame(struct MINES_Game *game, enum MINES_Input input);

#endif // MINES_H