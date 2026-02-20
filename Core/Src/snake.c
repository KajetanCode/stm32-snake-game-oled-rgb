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
        // fallback (awaryjnie)
        number = HAL_GetTick();
    }

    return number;
}



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

			oled_draw_snake_wait_start();

			break;

		case GAME_INPROGRESS:


			snake_game_head(head_position, evt, game_state);
			snake_game_eat(head_position, snack);
			snake_game_snacks(&snack);
			snake_game_tail(head_position, snake_body, last_evt);
			spawn_snack=0;

			break;

		case GAME_WIN:
			head_position -> x = 10;
			head_position -> y = 10;
			snake_size = 0;
			oled_draw_snake_win();

			break;

		case GAME_LOSE:
			head_position -> x = 10;
			head_position -> y = 10;

			oled_draw_snake_lose();

			break;
		}

	}

	else
		return;
}


void snake_game_head (snake_head_position_t *head_position, joy_event evt, uint8_t *game_state, uint8_t snake_size)
{


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

    snack->x = r % (127 - (3 - 1)); // oled border - snack size - 1
    snack->y = r % (63 - (3 - 1)); // oled border - snack size - 1

    spawn_snack=0;

    oled_draw_snake_snack(*snack);
	}
	else
		oled_draw_snake_snack(*snack);

}



void snake_game_tail(snake_head_position_t *head_position,         // kolejny krok do uzaleznic punkty ogona od iventu
                     snake_tail_position_t *snake_body,
                     joy_event last_evt)
{
    if (snake_grow && snake_size == 0)
    {
        uint8_t last_head_position_x = head_position->x;
        uint8_t last_head_position_y = head_position->y;

            snake_body[snake_size].x = last_head_position_x +3;
            snake_body[snake_size].y = last_head_position_y +3;
            snake_size+=1;

            switch (last_evt)
            {
                case JOY_EVT_LEFT:
                    for (int i = 0; i < 2; i++)
                    {
                        snake_body[snake_size + i].x = snake_body[snake_size].x + 3;
                    }
                    snake_size += 2;
                    break;

                case JOY_EVT_RIGHT:
                    for (int i = 0; i < 2; i++)
                    {
                        snake_body[snake_size + i].x = snake_body[snake_size].x - 3;
                    }
                    snake_size += 2;
                    break;

                case JOY_EVT_UP:
                    for (int i = 0; i < 2; i++)
                    {
                        snake_body[snake_size + i].y = snake_body[snake_size].y - 3;
                    }
                    snake_size += 2;
                    break;

                case JOY_EVT_DOWN:
                    for (int i = 0; i < 2; i++)
                    {
                        snake_body[snake_size + i].y = snake_body[snake_size].y + 3;
                    }
                    snake_size += 2;
                    break;
            }


    }

    else if (snake_grow && snake_size != 0)
    {
        switch (last_evt)
        {
            case JOY_EVT_LEFT:
                for (int i = 0; i < 2; i++)
                {
                	snake_body[snake_size + i].x = snake_body[snake_size].x + 3;
                	//snake_body[snake_size + i].y = snake_body[snake_size].y + 3;
                }

                snake_size+=3;

            case JOY_EVT_RIGHT:
                for (int i = 0; i < 2; i++)
                {
                	snake_body[snake_size + i].x = snake_body[snake_size].x - 3;
                	//snake_body[snake_size + i].y = snake_body[snake_size].y + 3;
                }

                snake_size+=3;

            case JOY_EVT_UP:
                for (int i = 0; i < 2; i++)
                {
                	//snake_body[snake_size + i].x = snake_body[snake_size].x - 3;
                	snake_body[snake_size + i].y = snake_body[snake_size].y - 3;
                }

                snake_size+=3;

            case JOY_EVT_DOWN:
                for (int i = 0; i < 2; i++)
                {
                	//snake_body[snake_size + i].x = snake_body[snake_size].x - 3;
                	snake_body[snake_size + i].y = snake_body[snake_size].y + 3;
                }

                snake_size+=3;

        }
    }
    oled_draw_snake_tail(snake_body, snake_size);
    snake_grow = 0;
}


void snake_game_eat (snake_head_position_t *head_position, snake_snack_t snack)
{


		for (int yi = 0; yi < 5; yi++)
		{
			for (int xi = 0; xi < 5; xi++)
			{
				for (int qi = 0; qi < 3; qi++)
				{
					if(
						head_position -> x + xi == snack.x + qi &&
						head_position -> y + yi == snack.y + qi
						)
						{
						spawn_snack=1;
						snake_grow = 1;
						}
				}
			}


		}
}


























