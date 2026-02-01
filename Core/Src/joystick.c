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

void joystick_read(joystick_t *joy)
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
