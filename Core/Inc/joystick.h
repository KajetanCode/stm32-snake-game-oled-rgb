/*
 * joystick.h
 *
 *  Created on: 1 lut 2026
 *      Author: padli
 */

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

#include <stdint.h>

typedef struct
{
	uint16_t x;
	uint16_t y;
} joystick_t ;

void joystick_read(joystick_t *joy);

#endif /* INC_JOYSTICK_H_ */
