#include <gint/display.h>
#include <gint/keyboard.h>
#include <gint/drivers/keydev.h>
#include <stdlib.h>
#include <time.h>
#include "mines.h"
#include "display.h"

int main(void)
{
	extern bopti_image_t img_title, img_title_logo;
	extern font_t font_3x5;

	srand(clock());
	dfont(&font_3x5);

	struct MINES_Game game;

	dimage(47, 5, &img_title_logo);
	dimage(25, 38, &img_title);
	dupdate();
	getkey();

	while (true)
	{
		MINES_InitGame(&game);
		render(&game);

		while (!game.over)
		{
			int key = getkey().key;
			enum MINES_Input input = NONE;
			switch (key)
			{
			case KEY_UP:
				input = CURSOR_UP;
				break;
			case KEY_DOWN:
				input = CURSOR_DOWN;
				break;
			case KEY_LEFT:
				input = CURSOR_LEFT;
				break;
			case KEY_RIGHT:
				input = CURSOR_RIGHT;
				break;
			case KEY_EXE:
				input = CLEAR_CELL;
				break;
			case KEY_1:
				input = TOGGLE_FLAG;
				break;
			default:
				break;
			}
			if (input != NONE)
			{
				MINES_InputGame(&game, input);
				render(&game);
			}
		}
		getkey();
	}

	return 1;
}
