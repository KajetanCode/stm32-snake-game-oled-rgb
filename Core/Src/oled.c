#include "oled.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include <stdio.h>

void oled_init(void)
{
    ssd1306_Init();
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();
}

void oled_clear(void)
{
    ssd1306_Fill(Black);
}

void oled_draw_raw(uint16_t x, uint16_t y)
{
    char buf[32];

    ssd1306_SetCursor(0, 0);
    snprintf(buf, sizeof(buf),
             "RAW X:%4u Y:%4u",
             x, y);
    ssd1306_WriteString(buf, Font_6x8, White);
}

void oled_draw_axis(uint8_t x, uint8_t y)
{
    char buf[32];

    ssd1306_SetCursor(0, 8);
    snprintf(buf, sizeof(buf),
             "AXIS X:%u Y:%u",
             x, y);
    ssd1306_WriteString(buf, Font_6x8, White);
}

void oled_draw_event(joy_event evt)
{
    ssd1306_SetCursor(0, 16);
    ssd1306_WriteString(
        joy_event_to_str(evt),
        Font_6x8,
        White);

    ssd1306_UpdateScreen();
}
