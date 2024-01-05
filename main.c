#include "cyhal.h"
#include "cybsp.h"
#include "cy_gpio.h"

// CHEROKEY MOBILE ROBOT DEFINES
#define M1_RIGHT_EN_PIN P10_3
#define M1_PWM_PIN P10_4
#define M2_PWM_PIN P10_5
#define M2_LEFT_EN_PIN P10_6


void Forward(){
	cyhal_gpio_write(M1_RIGHT_EN_PIN, 1);
	cyhal_gpio_write(M2_LEFT_EN_PIN, 0);
	CyDelay(1000);
}
void Backward(){
	cyhal_gpio_write(M1_RIGHT_EN_PIN, 0);
	cyhal_gpio_write(M2_LEFT_EN_PIN, 1);
	CyDelay(1000);
}
void Turn_Right(){
	cyhal_gpio_write(M2_LEFT_EN_PIN, 0);
	CyDelay(1000);
}
void Turn_Left(){
	cyhal_gpio_write(M1_RIGHT_EN_PIN, 1);
	CyDelay(1000);
}
int main(void)
{
    __enable_irq();
    //CHEROKEY MOBILE ROBOT INIT
    cyhal_gpio_init(M1_RIGHT_EN_PIN, CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG   ,0);
    cyhal_gpio_init(M2_LEFT_EN_PIN, CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_STRONG   ,0);

    cyhal_pwm_t en_right_car_pwm;
    cyhal_pwm_t en_left_car_pwm;

    cyhal_pwm_init(&en_right_car_pwm,M1_PWM_PIN, NULL);
    cyhal_pwm_set_duty_cycle(&en_right_car_pwm, 100.0, 5000);
    cyhal_pwm_init(&en_left_car_pwm,M2_PWM_PIN, NULL);
    cyhal_pwm_set_duty_cycle(&en_left_car_pwm, 100.0, 5000);
    cyhal_pwm_start(&en_right_car_pwm);
    cyhal_pwm_start(&en_left_car_pwm);
    for (;;)
    {
    	CyDelay(5000);
        cyhal_pwm_start(&en_right_car_pwm);
        cyhal_pwm_start(&en_left_car_pwm);
    	Forward();
    	CyDelay(1000);
    	Backward();
    	cyhal_pwm_stop(&en_right_car_pwm);
    	Turn_Right();
    	CyDelay(1000);
        cyhal_pwm_start(&en_right_car_pwm);
        cyhal_pwm_stop(&en_left_car_pwm);
        Turn_Left();
        CyDelay(1000);
        cyhal_pwm_stop(&en_right_car_pwm);


    }
}
