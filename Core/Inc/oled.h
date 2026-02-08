#ifndef INC_OLED_H_
#define INC_OLED_H_

#include <stdint.h>
#include "joystick.h"

typedef enum
{
    UI_NONE = 0,
    UI_RED,
    UI_GREEN,
    UI_BLUE,
    UI_STATE_MAX
} ui_state_t;



void oled_init(void);
void oled_clear(void);
void oled_draw_raw(uint16_t x, uint16_t y);
void oled_draw_axis(uint8_t x, uint8_t y);
void oled_draw_event(joy_event evt);

#endif /* INC_OLED_H_ */
