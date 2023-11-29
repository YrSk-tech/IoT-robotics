#include "cyhal.h"
#include "cybsp.h"
#include "cy_gpio.h"

// Car Definitions
#define M1_EN_PIN P10_3
#define M1_PWM_PIN P10_4
#define M2_PWM_PIN P10_5
#define M2_EN_PIN P10_6

int main(void)
{
    __enable_irq();

    cyhal_gpio_init(M1_EN_PIN, CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG ,1);
    cyhal_gpio_init(M2_EN_PIN, CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG ,0);

    cyhal_pwm_t en_1_car_pwm;
    cyhal_pwm_t en_2_car_pwm;

    cyhal_pwm_init(&en_1_car_pwm,M1_PWM_PIN, NULL);
    cyhal_pwm_set_duty_cycle(&en_1_car_pwm, 100.0, 5000);
    cyhal_pwm_start(&en_1_car_pwm);
    cyhal_pwm_init(&en_2_car_pwm,M2_PWM_PIN, NULL);
    cyhal_pwm_set_duty_cycle(&en_2_car_pwm, 100.0, 5000);
    cyhal_pwm_start(&en_2_car_pwm);
    for (;;)
    {
    	cyhal_gpio_read(M1_EN_PIN)? cyhal_gpio_toggle(M1_EN_PIN):PASS;
    	CyDelay(1000);
    	cyhal_gpio_read(M2_EN_PIN)?cyhal_gpio_toggle(M2_EN_PIN):PASS;
    	CyDelay(1000);

    }
}
