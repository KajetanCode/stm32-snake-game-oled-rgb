/*
 * snake.h
 *
 *  Created on: 15 lut 2026
 *      Author: padli
 */

#ifndef INC_SNAKE_H_
#define INC_SNAKE_H_

#include <stdint.h>


typedef struct
{
	uint8_t x;
	uint8_t y;
}snake_head_position_t;

typedef struct
{
	uint8_t x;
	uint8_t y;
}snake_tail_position_t;


typedef struct
{
	uint8_t x;
	uint8_t y;
}snake_snack_t;

extern snake_tail_position_t snake_tail[10];

typedef enum
{
	GAME_WAIT_START = 0,
	GAME_INPROGRESS,
	GAME_WIN,
	GAME_LOSE,
} snake_game_state_t;


#endif /* INC_SNAKE_H_ */
