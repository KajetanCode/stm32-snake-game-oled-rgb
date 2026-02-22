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
#include "rng.h"

#define SNAKE_MAX_LENGTH 30

bool spawn_snack;
bool snake_grow;

static snake_tail_position_t snake_body[SNAKE_MAX_LENGTH];
snake_snack_t snack;
static uint8_t snake_size;

static joy_event last_evt;

uint32_t Random_Get(void)
{
    uint32_t number;

    if (HAL_RNG_GenerateRandomNumber(&hrng, &number) != HAL_OK)
    {
        // fallback
        number = HAL_GetTick();
    }

    return number;
}



void snake_game_state (snake_head_position_t *head_position, joy_event evt, ui_menu_page page, uint8_t *game_state)
{
	if(snake_size == SNAKE_MAX_LENGTH)
	{
		*game_state=GAME_WIN;
	}

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

			oled_draw_snake_wait_start();

			break;

		case GAME_INPROGRESS:


			snake_game_head(head_position, evt, game_state);
			snake_game_eat(head_position, snack);
			snake_game_snacks(&snack);
			if (snake_check_tail_collision(head_position, snake_body, snake_size))
			{
			    *game_state = GAME_LOSE;
			}
			snake_game_tail(head_position, snake_body, last_evt);
			spawn_snack=0;

			break;

		case GAME_WIN:

			snake_game_init(head_position);
			oled_draw_snake_win();

			break;

		case GAME_LOSE:

			snake_game_init(head_position);
			oled_draw_snake_lose();

			break;
		}

	}

	else
		snake_size = 0;
		return;
}


void snake_game_head (snake_head_position_t *head_position, joy_event evt, uint8_t *game_state, uint8_t snake_size)
{

	if (evt != JOY_EVT_NONE)
	{
	    uint8_t opposite =
	        (last_evt == JOY_EVT_LEFT  && evt == JOY_EVT_RIGHT) ||
	        (last_evt == JOY_EVT_RIGHT && evt == JOY_EVT_LEFT)  ||
	        (last_evt == JOY_EVT_UP    && evt == JOY_EVT_DOWN)  ||
	        (last_evt == JOY_EVT_DOWN  && evt == JOY_EVT_UP);

	    if (!opposite)
	    {
	        last_evt = evt;
	    }
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

if (snake_size + 2 >= SNAKE_MAX_LENGTH)
{
	*game_state = GAME_WIN;
}

oled_draw_snake_head (*head_position);
}


void snake_game_snacks(snake_snack_t *snack)
{
	if (spawn_snack)
	{

	    uint32_t r;
	    HAL_RNG_GenerateRandomNumber(&hrng, &r);

    snack->x = r % (127 - (8 + 3)); // oled border - snack size - 3
    snack->y = r % (63 - (8 + 3)); // oled border - snack size - 3

    spawn_snack=0;

    oled_draw_snake_snack(*snack);
	}
	else
		oled_draw_snake_snack(*snack);

}



void snake_game_tail(snake_head_position_t *head_position,
                     snake_tail_position_t *snake_body,
                     joy_event last_evt)
{
    static uint8_t prev_head_x = 10;
    static uint8_t prev_head_y = 10;


    for (int i = snake_size; i > 0; i--)
    {
        snake_body[i] = snake_body[i - 1];
    }


    if (snake_size > 0)
    {
        snake_body[0].x = prev_head_x;
        snake_body[0].y = prev_head_y;
    }


    prev_head_x = head_position->x;
    prev_head_y = head_position->y;


    if (snake_grow)
    {
        if (snake_size < SNAKE_MAX_LENGTH - 1)
        {
            snake_size+=3;
        }
        snake_grow = 0;
    }

    oled_draw_snake_tail(snake_body, snake_size);
}


void snake_game_eat (snake_head_position_t *head_position, snake_snack_t snack)
{

	    for (int yi = 0; yi < 5; yi++)
	    {
	        for (int xi = 0; xi < 5; xi++)
	        {
	            for (int qy = 0; qy < 3; qy++)
	            {
	                for (int qx = 0; qx < 3; qx++)
	                {
	                    if (
	                        head_position->x + xi == snack.x + qx &&
	                        head_position->y + yi == snack.y + qy
	                       )
	                    {
	                        spawn_snack = 1;
	                        snake_grow = 1;
	                        return;
	                    }
	                }
	            }
	        }
	    }
	}



uint8_t snake_check_tail_collision(snake_head_position_t *head_position,
                                   snake_tail_position_t *snake_body,
                                   uint8_t snake_size)
{
    for (uint8_t i = 0; i < snake_size; i++)
    {
        if (head_position->x == snake_body[i].x &&
            head_position->y == snake_body[i].y)
        {
            return 1; // collision
        }
    }

    return 0; // no collision
}



void snake_game_init(snake_head_position_t *head_position)
{
    snake_size = 0;
    snake_grow = 0;
    spawn_snack = 1;

    head_position -> x = 10;
    head_position -> y = 10;

    last_evt = JOY_EVT_RIGHT;
}



















