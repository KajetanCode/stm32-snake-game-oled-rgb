#ifndef INC_OLED_H_
#define INC_OLED_H_

#include <stdint.h>
#include "joystick.h"
#include "ui.h"
#include "ssd1306.h"

void oled_init(void);
void oled_clear(void);
void oled_draw_raw(uint16_t x, uint16_t y);
void oled_draw_axis(uint8_t x, uint8_t y);
void oled_draw_event(joy_event evt);


extern SSD1306_VERTEX snake_border[5];



#endif /* INC_OLED_H_ */
