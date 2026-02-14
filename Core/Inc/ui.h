/*
 * ui.h
 *
 *  Created on: 8 lut 2026
 *      Author: padli
 */

#ifndef INC_UI_H_
#define INC_UI_H_

#include <stdint.h>
#include "joystick.h"
#include "oled.h"

typedef enum
{
    UI_NONE = 0,
    UI_RED,
    UI_GREEN,
    UI_BLUE,
    UI_STATE_MAX
} ui_state_t;

typedef enum
{
	UI_WELCOME = 0,
	UI_RGB,
	UI_SNAKE,
	UI_MAX_PAGE
}ui_menu_page;


typedef struct
{
    ui_state_t selected;   // UI_RED / UI_GREEN / UI_BLUE
    uint8_t r;             // 0–100
    uint8_t g;             // 0–100
    uint8_t b;             // 0–100
} ui_color_state_t;

void ui_handle_navigation(
    ui_color_state_t *ui,
    joy_event evt,
    uint32_t now);
void ui_handle_value(ui_color_state_t *ui, joy_event evt);

#endif /* INC_UI_H_ */
