#include "oled.h"
#include "ssd1306.h"
#include "ssd1306_fonts.h"
#include <stdio.h>
#include "snake.h"

SSD1306_VERTEX snake_border[5] =
					  {
							  {0,0},
							  {127,0},
							  {127,63},
							  {0,63},
							  {0,0}
					  };





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




void oled_draw_color_menu(const ui_color_state_t *ui)
{
    char buf[16];

    /* --- R --- */
    ssd1306_SetCursor(0, 24);
    ssd1306_WriteString("R", Font_6x8, White);

    ssd1306_SetCursor(100, 24);
    snprintf(buf, sizeof(buf), "%3u%%", ui->r);
    ssd1306_WriteString(buf, Font_6x8, White);

    /* --- G --- */
    ssd1306_SetCursor(0, 32);
    ssd1306_WriteString("G", Font_6x8, White);

    ssd1306_SetCursor(100, 32);
    snprintf(buf, sizeof(buf), "%3u%%", ui->g);
    ssd1306_WriteString(buf, Font_6x8, White);

    /* --- B --- */
    ssd1306_SetCursor(0, 40);
    ssd1306_WriteString("B", Font_6x8, White);

    ssd1306_SetCursor(100, 40);
    snprintf(buf, sizeof(buf), "%3u%%", ui->b);
    ssd1306_WriteString(buf, Font_6x8, White);

    /* --- Aktywny kolor --- */
    switch (ui->selected)
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
            break;
    }
}

void oled_draw_welcome_menu(void)
{
    ssd1306_SetCursor(0, 0);
    ssd1306_WriteString("WELCOME", Font_6x8, White);
}

void oled_draw_snake_menu(void)
{
	ssd1306_Polyline(snake_border, 5, White);
    ssd1306_SetCursor(8, 8);
   // ssd1306_WriteString("SNAKE", Font_6x8, White);



}


void oled_draw_snake_head(snake_head_position_t head)
{

    int start_x = head.x - 2;
    int start_y = head.y - 2;

    for (int y = 0; y < 5; y++)
    {
        for (int x = 0; x < 5; x++)
        {
            ssd1306_DrawPixel(start_x + x, start_y + y, White);
        }
    }

   // ssd1306_UpdateScreen();
}
































