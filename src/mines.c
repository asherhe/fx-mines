#include "mines.h"

#include <stdlib.h>
#include "config.h"

void MINES_InitGame(struct MINES_Game *game)
{
  game->width = MINES_GRID_WIDTH;
  game->height = MINES_GRID_HEIGHT;
  game->mines = MINES_NUM_MINES;
  game->cleared = 0;
  game->flags = 0;
  game->cursorX = 0;
  game->cursorY = 0;
  game->over = 0;
  game->win = 0;

  for (int i = 0; i < game->width; ++i)
    for (int j = 0; j < game->height; ++j)
    {
      struct MINES_Tile *tile = &game->field[i][j];
      tile->neighbors = 0;
      tile->isMine = 0;
      tile->isCovered = 1;
      tile->isFlagged = 0;
    }

  for (int i = 0; i < game->mines; ++i)
  {
    int x, y;
    do
    {
      x = rand() % MINES_GRID_WIDTH;
      y = rand() % MINES_GRID_HEIGHT;
    } while (game->field[x][y].isMine);
    game->field[x][y].isMine = 1;

    if (x > 0)
    {
      ++game->field[x - 1][y].neighbors;
      if (y > 0)
        ++game->field[x - 1][y - 1].neighbors;
      if (y < MINES_GRID_HEIGHT - 1)
        ++game->field[x - 1][y + 1].neighbors;
    }
    if (y > 0)
      ++game->field[x][y - 1].neighbors;
    if (y < MINES_GRID_HEIGHT - 1)
      ++game->field[x][y + 1].neighbors;
    if (x < MINES_GRID_WIDTH - 1)
    {
      ++game->field[x + 1][y].neighbors;
      if (y > 0)
        ++game->field[x + 1][y - 1].neighbors;
      if (y < MINES_GRID_HEIGHT - 1)
        ++game->field[x + 1][y + 1].neighbors;
    }
  }
}

void MINES_InputGame(struct MINES_Game *game, enum MINES_Input input)
{
  if (input == NONE)
    return;

  struct MINES_Tile *tile = &game->field[game->cursorX][game->cursorY];
  switch (input)
  {
  case CURSOR_UP:
    if (game->cursorY > 0)
      --game->cursorY;
    break;
  case CURSOR_DOWN:
    if (game->cursorY < MINES_GRID_HEIGHT - 1)
      ++game->cursorY;
    break;
  case CURSOR_LEFT:
    if (game->cursorX > 0)
      --game->cursorX;
    break;
  case CURSOR_RIGHT:
    if (game->cursorX < MINES_GRID_WIDTH - 1)
      ++game->cursorX;
    break;
  case CLEAR_CELL:
    if (tile->isCovered && !tile->isFlagged)
    {
      tile->isCovered = 0;
      ++game->cleared;
      if (tile->isMine)
      {
        game->over = 1;
      }
      else if (game->cleared + game->mines == MINES_GRID_WIDTH * MINES_GRID_HEIGHT)
      {
        game->over = 1;
        game->win = 1;
      }
    }
    break;
  case TOGGLE_FLAG:
    if (tile->isCovered)
    {
      tile->isFlagged = ~tile->isFlagged;
      if (tile->isFlagged)
        ++game->flags;
      else
        --game->flags;
    }
    break;
  default:
    break;
  }
  return;
}