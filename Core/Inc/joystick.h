/*
 * joystick.h
 *
 *  Created on: 1 lut 2026
 *      Author: padli
 */

#ifndef INC_JOYSTICK_H_
#define INC_JOYSTICK_H_

#include <stdint.h>

#define JOY_DEADZONE 100

typedef struct
{
    uint16_t x;
    uint16_t y;
} joystick_raw_t;

typedef struct
{
    uint16_t axis_val;
    uint16_t center_position;
} joystick_axis_value;

typedef struct
{
    uint16_t axis_val;
    uint16_t center_position;
} joystick_move;

typedef enum
{
    JOY_EVT_NONE = 0,
    JOY_EVT_LEFT,
    JOY_EVT_RIGHT,
    JOY_EVT_UP,
    JOY_EVT_DOWN,
    JOY_EVT_CENTER
} joy_event;

typedef struct
{
    uint16_t x;
    uint16_t y;
} joystick_center_t;

typedef struct
{
    int16_t x;
    int16_t y;
} joystick_norm_t;

typedef struct
{
    uint16_t min;
    uint16_t center;
    uint16_t max;
} joystick_axis_cal_t;
/*
void joystick_read_raw(joystick_raw_t *joy);

void joystick_read_raw(joystick_raw_t *raw);

void joystick_calibrate(joystick_axis_cal_t *x,
                         joystick_axis_cal_t *y,
                         const joystick_raw_t *raw);

void joystick_get_normalized(joystick_norm_t *out,
                              const joystick_raw_t *raw,
                              const joystick_axis_cal_t *x_cal,
                              const joystick_axis_cal_t *y_cal);
*/
#endif /* INC_JOYSTICK_H_ */
