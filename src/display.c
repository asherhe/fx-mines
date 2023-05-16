#include "display.h"

#include <gint/display.h>
#include "config.h"
#include "mines.h"

void render(struct MINES_Game *game)
{
  extern bopti_image_t img_icons, img_tiles;

  dclear(C_WHITE);

  drect(1, 1, 126, 62, C_BLACK);
  drect(3, 3, 92, 60, C_WHITE);   // playfield
  drect(95, 3, 124, 60, C_WHITE); // sidebar

  // cursor
  dsubimage(5 + game->cursorX * MINES_TILE_WIDTH, 5 + game->cursorY * MINES_TILE_HEIGHT,
            &img_tiles,
            0, 0,
            MINES_TILE_WIDTH, MINES_TILE_HEIGHT, DIMAGE_NONE);

  // draw tiles
  for (int i = 0; i < MINES_GRID_WIDTH; ++i)
    for (int j = 0; j < MINES_GRID_HEIGHT; ++j)
    {
      struct MINES_Tile *tile = &game->field[i][j];
      unsigned int x = 5 + i * MINES_TILE_WIDTH, y = 5 + j * MINES_TILE_HEIGHT;
      if (game->over && tile->isMine)
        dsubimage(x, y,
                  &img_tiles,
                  game->win ? 4 * MINES_TILE_WIDTH : 3 * MINES_TILE_WIDTH, 0,
                  MINES_TILE_WIDTH, MINES_TILE_HEIGHT, DIMAGE_NONE);
      else if (tile->isFlagged)
        dsubimage(x, y,
                  &img_tiles,
                  2 * MINES_TILE_WIDTH, 0,
                  MINES_TILE_WIDTH, MINES_TILE_HEIGHT, DIMAGE_NONE);
      else if (tile->isCovered)
        dsubimage(x, y,
                  &img_tiles,
                  MINES_TILE_WIDTH, 0,
                  MINES_TILE_WIDTH, MINES_TILE_HEIGHT, DIMAGE_NONE);
      else if (tile->neighbors)
        dsubimage(x, y,
                  &img_tiles,
                  (tile->neighbors - 1) * MINES_TILE_WIDTH, MINES_TILE_HEIGHT,
                  MINES_TILE_WIDTH, MINES_TILE_HEIGHT, DIMAGE_NONE);
    }

  // write info
  dsubimage(97, 5, &img_icons, 1, 1, 5, 5, DIMAGE_NONE);
  dtext(103, 5, C_BLACK, "MINES");

  dsubimage(97, 23, &img_icons, 1, 1, 5, 5, DIMAGE_NONE);
  dprint(105, 23, C_BLACK, "%d", game->mines);
  dsubimage(97, 33, &img_icons, 8, 1, 5, 5, DIMAGE_NONE);
  dprint(105, 33, C_BLACK, "%d", game->flags);

  dupdate();
}
