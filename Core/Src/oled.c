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

   // ssd1306_UpdateScreen();
}

ui_state_t ui_handle_event(ui_state_t state, joy_event evt)
{
    switch (evt)
    {
        case JOY_EVT_DOWN:
            state = (state + 1) % UI_STATE_MAX;
            break;

        case JOY_EVT_UP:
            state = (state == 0) ? UI_STATE_MAX - 1 : state - 1;
            break;

        default:
            break;
    }

    return state;
}


void oled_draw_color_menu(ui_state_t state)
{
    /* Stała lista */
    ssd1306_SetCursor(0, 24);
    ssd1306_WriteString("R", Font_6x8, White);

    ssd1306_SetCursor(0, 32);
    ssd1306_WriteString("G", Font_6x8, White);

    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString("B", Font_6x8, White);



    switch (state)
    {
        case UI_RED:
        	ssd1306_SetCursor(48, 24);
            ssd1306_WriteString("RED", Font_6x8, White);
            break;

        case UI_GREEN:
        	ssd1306_SetCursor(48, 32);
            ssd1306_WriteString("GREEN", Font_6x8, White);
            break;

        case UI_BLUE:
        	ssd1306_SetCursor(48, 40);
            ssd1306_WriteString("BLUE", Font_6x8, White);
            break;

        default:
            ssd1306_WriteString(" ", Font_6x8, White);
            break;
    }

   // ssd1306_UpdateScreen();
}

