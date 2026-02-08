#ifndef INC_DIODA_RGB_H_
#define INC_DIODA_RGB_H_

#include <stdint.h>

typedef enum
{
    RGB_OFF = 0,
    RGB_RED,
    RGB_GREEN,
    RGB_BLUE,
    RGB_YELLOW,
    RGB_CYAN,
    RGB_MAGENTA,
    RGB_WHITE
} rgb_color_t;

void rgb_init(void);
void rgb_set_color(rgb_color_t color);
void rgb_set_raw(uint8_t r, uint8_t g, uint8_t b);

#endif /* INC_DIODA_RGB_H_ */
