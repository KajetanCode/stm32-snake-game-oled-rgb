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
#include <stdbool.h>

#define SNAKE_MAX_LENGTH 30

bool spawn_snack;
static snake_tail_position_t snake_body[SNAKE_MAX_LENGTH];
static uint8_t snake_length = 1;
snake_snack_t snack;



void snake_game_state (snake_head_position_t *head_position, joy_event evt, ui_menu_page page, uint8_t *game_state)
{
	if (page == UI_SNAKE )
	{

		switch (*game_state)
		{
		case GAME_WAIT_START:

			spawn_snack=1;
			head_position -> x = 10;
			head_position -> y = 10;

			if (evt == JOY_EVT_RIGHT)
			{
				*game_state=GAME_INPROGRESS;
			}

			break;

		case GAME_INPROGRESS:

			snake_game_head(head_position, evt, game_state);

			snake_game_snacks(&snack);

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


void snake_game_head (snake_head_position_t *head_position, joy_event evt, uint8_t *game_state)
{
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
}






void snake_game_tail (head_position)
{

}

void snake_game_snacks(snake_snack_t *snack)
{
	if (spawn_snack)
	{
		srand(HAL_GetTick() ^ SysTick->VAL);


    snack->x = rand() % (127 - (3 - 1)); // oled border - snack size - 1
    snack->y = rand() % (63 - (3 - 1)); // oled border - snack size - 1

    spawn_snack=0;

    oled_draw_snake_snack(snack);
	}
	else
		return;
}




























