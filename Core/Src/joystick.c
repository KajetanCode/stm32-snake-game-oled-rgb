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

    HAL_Delay(100);

    adc_select_channel(ADC_CHANNEL_2);   // Y
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 10);
    joy->y = HAL_ADC_GetValue(&hadc1);
    HAL_ADC_Stop(&hadc1);
}

void joystick_apply_deadzone(uint16_t val, uint16_t center)
{
    if (val > center - JOY_DEADZONE &&
        val < center + JOY_DEADZONE)
        return center;

    return val;
}

static int16_t normalize_axis(uint16_t val,
                              const joystick_axis_cal_t *cal)
{
    if (val >= cal->center)
        return (int16_t)((val - cal->center) * 100 /
                         (cal->max - cal->center));
    else
        return (int16_t)((val - cal->center) * 100 /
                         (cal->center - cal->min));
}

void joystick_get_normalized(joystick_norm_t *out,
                             const joystick_raw_t *raw,
                             const joystick_axis_cal_t *x_cal,
                             const joystick_axis_cal_t *y_cal)
{
    out->x = normalize_axis(raw->x, x_cal);
    out->y = normalize_axis(raw->y, y_cal);
}
