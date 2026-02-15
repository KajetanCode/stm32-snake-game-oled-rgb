#include "dioda_RGB.h"
#include "ui.h"
#include "tim.h"

#define PWM_MAX 1000

static uint32_t percent_to_pwm(uint8_t percent)
{
    if (percent > 100)
        percent = 100;

    return (percent * PWM_MAX) / 100;
}

void rgb_apply_ui_color(const ui_color_state_t *ui, ui_menu_page page)
{
	if (page == UI_RGB)
	{
    uint32_t r_pwm = percent_to_pwm(ui->r);
    uint32_t g_pwm = percent_to_pwm(ui->g);
    uint32_t b_pwm = percent_to_pwm(ui->b);

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, r_pwm);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, g_pwm);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, b_pwm);
	}
	else
		return;

}
