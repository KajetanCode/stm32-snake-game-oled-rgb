/*
 * joystick.c
 *
 *  Created on: 1 lut 2026
 *      Author: padli
 */


#include "joystick.h"
#include "adc.h"

static void adc_select_channel(uint32_t channel)
{
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = channel;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_92CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}

void joystick_read_raw(joystick_raw_t *joy)
{
    adc_select_channel(ADC_CHANNEL_1);   // X
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 10);
    joy->x = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);

   // HAL_Delay(100);

    adc_select_channel(ADC_CHANNEL_2);   // Y
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 10);
    joy->y = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
}

void joystick_apply_deadzone(
        uint16_t val,
        uint16_t center,
        uint16_t *out,
        uint8_t *in_deadzone)
{
    if (val > center - JOY_DEADZONE &&
        val < center + JOY_DEADZONE)
    {
        *out = 0;            // CENTER
        *in_deadzone = 1;
    }
    else if (val < center - JOY_DEADZONE)
    {
        *out = 1;            // LEFT / UP
        *in_deadzone = 0;
    }
    else // val > center + JOY_DEADZONE
    {
        *out = 2;            // RIGHT / DOWN
        *in_deadzone = 0;
    }
}

joy_event joystick_get_event(
				uint16_t val_x,
				uint16_t center_x,
				uint16_t val_y,
				uint16_t center_y)
{
  //  if (center_x && center_y)
  //      return JOY_EVT_NONE;

    if (val_x == 1 && !center_x && center_y)
        return JOY_EVT_LEFT;

    if (val_x == 2 && (center_x==0) && (center_y==1))
        return JOY_EVT_RIGHT;

    if (val_y == 1 && !center_y)
        return JOY_EVT_UP;

    if (val_y == 2 && !center_y)
        return JOY_EVT_DOWN;

    return JOY_EVT_NONE;
}


const char* joy_event_to_str(joy_event evt)
{
    switch (evt)
    {
        case JOY_EVT_LEFT:  return "LEFT";
        case JOY_EVT_RIGHT: return "RIGHT";
        case JOY_EVT_UP:    return "UP";
        case JOY_EVT_DOWN:  return "DOWN";
        default:            return "NONE";
    }
}

