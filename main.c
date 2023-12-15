#include "cyhal.h"
#include "cybsp.h"
#include "cy_gpio.h"
#define MY_LED_PIN P6_3
//IR RECEIVER UART DEFINES
#define BAUD_RATE       9600
#define RX_BUF_SIZE     8
#define UART_DELAY      10u

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
    //IR RECEIVER UART INIT
//    uint8_t      rx_buf[RX_BUF_SIZE];
//    size_t rx_length = RX_BUF_SIZE;
//    uint32_t     actualbaud;
//
//    cyhal_uart_t ir_uart_data;
//    cyhal_uart_init(&ir_uart_data, NC, CYBSP_DEBUG_UART_RX, NC, NC, NULL, NULL);
//    cyhal_uart_set_baud(&ir_uart_data, BAUD_RATE, &actualbaud);
    // Configure LED pin
       cyhal_pwm_t MY_PWM;
       cyhal_pwm_init_adv(&MY_PWM, MY_LED_PIN, NC, CYHAL_PWM_LEFT_ALIGN, true, 0, false, NULL);
    for (;;)
    {
    	cyhal_pwm_stop(&en_left_car_pwm);
    	cyhal_pwm_stop(&en_right_car_pwm);
    	CyDelay(5000);
        cyhal_pwm_start(&en_right_car_pwm);
        cyhal_pwm_start(&en_left_car_pwm);
    	Forward();
    	cyhal_pwm_stop(&en_left_car_pwm);
    	Turn_Left();
    	CyDelay(1000);
    	cyhal_pwm_start(&en_left_car_pwm);
    	Backward();
    	cyhal_pwm_stop(&en_right_car_pwm);
    	Turn_Right();
    	CyDelay(1000);
        cyhal_pwm_start(&en_right_car_pwm);


    }
}
