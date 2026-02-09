/*
 * ui.c
 *
 *  Created on: 8 lut 2026
 *      Author: padli
 */
#include <stdint.h>
#include <ui.h>



void ui_process_joystick(
    ui_color_state_t *ui,
    joy_event evt,
    uint32_t now)
{
    static joy_event last_evt = JOY_EVT_NONE;
    static uint32_t last_repeat = 0;

    if (evt != last_evt)
    {
        last_evt = evt;
        last_repeat = now;

        if (evt != JOY_EVT_NONE)
        {
        	ui_handle_navigation(ui, evt, now);
            ui_handle_value(ui, evt);
        }
    }
    else if (evt != JOY_EVT_NONE &&
             (now - last_repeat) >= 300)
    {
        last_repeat = now;
        ui_handle_navigation(ui, evt, now);
        ui_handle_value(ui, evt);
    }
}


void ui_actual_color_state(
    ui_color_state_t *ui,
    joy_event evt)
{
    switch (evt)
    {
        case JOY_EVT_RIGHT:
            if (ui->selected == UI_RED && ui->r < 100) ui->r++;
            if (ui->selected == UI_GREEN && ui->g < 100) ui->g++;
            if (ui->selected == UI_BLUE && ui->b < 100) ui->b++;
            break;

        case JOY_EVT_LEFT:
            if (ui->selected == UI_RED && ui->r > 0) ui->r--;
            if (ui->selected == UI_GREEN && ui->g > 0) ui->g--;
            if (ui->selected == UI_BLUE && ui->b > 0) ui->b--;
            break;

        default:
            break;
    }
}


/* UP / DOWN – zmiana zaznaczenia */
void ui_handle_navigation(
    ui_color_state_t *ui,
    joy_event evt,
    uint32_t now)
{
    static uint32_t last_nav = 0;        // rate-limit (300 ms)
    static uint32_t last_activity = 0;   // idle timer (3 s)

    /* --- brak ruchu: sprawdź idle --- */
    if (evt != JOY_EVT_UP && evt != JOY_EVT_DOWN && evt == JOY_EVT_NONE)
    {
        if (last_activity != 0 && (now - last_activity) >= 3000)
        {
            ui->selected = UI_NONE;      // albo 0, jeśli UI_NONE == 0
            last_activity = 0;           // zapobiega ciągłemu resetowi
        }
        return;
    }

    /* --- ruch: reset idle --- */
    last_activity = now;

    /* --- ograniczenie szybkości --- */
    if (now - last_nav < 300)
        return;

    last_nav = now;

    switch (evt)
    {
        case JOY_EVT_DOWN:
            ui->selected = (ui->selected + 1) % UI_STATE_MAX;
            break;

        case JOY_EVT_UP:
            ui->selected = (ui->selected == 0)
                            ? UI_STATE_MAX - 1
                            : ui->selected - 1;
            break;

        default:
            break;
    }
}

/* LEFT / RIGHT – zmiana wartości procentowej */
void ui_handle_value(ui_color_state_t *ui, joy_event evt)
{
    switch (evt)
    {
        case JOY_EVT_RIGHT:
            if (ui->selected == UI_RED   && ui->r < 100) ui->r++;
            if (ui->selected == UI_GREEN && ui->g < 100) ui->g++;
            if (ui->selected == UI_BLUE  && ui->b < 100) ui->b++;
            break;

        case JOY_EVT_LEFT:
            if (ui->selected == UI_RED   && ui->r > 0) ui->r--;
            if (ui->selected == UI_GREEN && ui->g > 0) ui->g--;
            if (ui->selected == UI_BLUE  && ui->b > 0) ui->b--;
            break;

        default:
            break;
    }
}















