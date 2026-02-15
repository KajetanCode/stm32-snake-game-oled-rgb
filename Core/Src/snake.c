/*
 * snake.c
 *
 *  Created on: 15 lut 2026
 *      Author: padli
 */

#include "snake.h"
#include "main.h"
#include "ui.h"
#include "joystick.h"






void snake_head (snake_head_position_t *head_position, joy_event evt, ui_menu_page page, uint8_t *game_state)
{
	if (page == UI_SNAKE )
	{

		switch (*game_state)
		{
		case GAME_WAIT_START:

			head_position -> x = 10;
			head_position -> y = 10;

			if (evt == JOY_EVT_RIGHT)
			{
				*game_state=GAME_INPROGRESS;
			}

			break;

		case GAME_INPROGRESS:

			static joy_event last_evt;

			if (evt != JOY_EVT_NONE)
			{
			    last_evt = evt;
			}
						switch (last_evt)
						{
						case JOY_EVT_LEFT:
						    if (head_position->x <= 4) // 0 + 4 (sneak head 5x5 + oled error)
						    {
						        *game_state = GAME_LOSE;
						    }
						    else
						    {
						        head_position->x--;
						    }
						    break;

						case JOY_EVT_RIGHT:
						    if (head_position->x >= 123) // 127 - 4 (sneak head 5x5 + oled error)
						    {
						        *game_state = GAME_LOSE;
						    }
						    else
						    {
						        head_position->x++;
						    }
						    break;

						case JOY_EVT_UP:
						    if (head_position->y <= 4) // 0 + 4 (sneak head 5x5 + oled error)
						    {
						        *game_state = GAME_LOSE;
						    }
						    else
						    {
						        head_position->y--;
						    }
						    break;

						case JOY_EVT_DOWN:
						    if (head_position->y >= 59) // 63 - 4 (sneak head 5x5 + oled error)
						    {
						        *game_state = GAME_LOSE;
						    }
						    else
						    {
						        head_position->y++;
						    }
						    break;

						default:
							break;
						}

			oled_draw_snake_head (*head_position);

			break;

		case GAME_WIN:
			head_position -> x = 10;
			head_position -> y = 10;
			break;

		case GAME_LOSE:
			head_position -> x = 10;
			head_position -> y = 10;
			break;
		}

	}

	else
		return;
}



