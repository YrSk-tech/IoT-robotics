#include "cyhal.h"
#include "cybsp.h"
#include "cy_gpio.h"
#define MY_LED_PIN P6_3
//IR RECEIVER UART DEFINES
#define BAUD_RATE       9600
#define RX_BUF_SIZE     8
#define UART_DELAY      10u

// CHEROKEY MOBILE ROBOT DEFINES
#define M1_EN_PIN P10_3
#define M1_PWM_PIN P10_4
#define M2_PWM_PIN P10_5
#define M2_EN_PIN P10_6



void Forward(){
	cyhal_gpio_write(M1_EN_PIN, 1);
	cyhal_gpio_write(M2_EN_PIN, 0);
	CyDelay(1000);
}
void Backward(){
	cyhal_gpio_write(M1_EN_PIN, 0);
	cyhal_gpio_write(M2_EN_PIN, 1);
	CyDelay(1000);
}
void Turn_Right(){
	cyhal_gpio_write(M2_EN_PIN, 0);
	cyhal_gpio_write(M2_EN_PIN, 0);
	CyDelay(1000);
}
void Turn_Left(){
	cyhal_gpio_write(M1_EN_PIN, 1);
	cyhal_gpio_write(M2_EN_PIN, NULL);
	CyDelay(1000);
}
int main(void)
{
    __enable_irq();
    //CHEROKEY MOBILE ROBOT INIT
    cyhal_gpio_init(M1_EN_PIN, CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_PULLDOWN   ,0);
    cyhal_gpio_init(M2_EN_PIN, CYHAL_GPIO_DIR_OUTPUT,CYHAL_GPIO_DRIVE_PULLDOWN   ,0);

    cyhal_pwm_t en_1_car_pwm;
    cyhal_pwm_t en_2_car_pwm;

    cyhal_pwm_init(&en_1_car_pwm,M1_PWM_PIN, NULL);
    cyhal_pwm_set_duty_cycle(&en_1_car_pwm, 100.0, 5000);
    cyhal_pwm_init(&en_2_car_pwm,M2_PWM_PIN, NULL);
    cyhal_pwm_set_duty_cycle(&en_2_car_pwm, 100.0, 5000);
//    cyhal_pwm_start(&en_1_car_pwm);
//    cyhal_pwm_start(&en_2_car_pwm);
    //IR RECEIVER UART INIT
    uint8_t      rx_buf[RX_BUF_SIZE];
    size_t rx_length = RX_BUF_SIZE;
    uint32_t     actualbaud;

    cyhal_uart_t ir_uart_data;
    cyhal_uart_init(&ir_uart_data, NC, CYBSP_DEBUG_UART_RX, NC, NC, NULL, NULL);
    cyhal_uart_set_baud(&ir_uart_data, BAUD_RATE, &actualbaud);
    // Configure LED pin
       cyhal_pwm_t MY_PWM;
       cyhal_pwm_init_adv(&MY_PWM, MY_LED_PIN, NC, CYHAL_PWM_LEFT_ALIGN, true, 0, false, NULL);
    for (;;)
    {
    	 // Begin Rx Transfer
    	    cyhal_uart_read(&ir_uart_data,rx_buf, &rx_length);
    	    cyhal_system_delay_ms(UART_DELAY);
    	    if (rx_buf != 0)
    	    {

    	    	for (size_t i = 0; i < rx_length; i++)
    	    	{
    	    		cyhal_pwm_start(&MY_PWM);  // Start PWM output
    	    		cyhal_pwm_set_duty_cycle(&MY_PWM, 50.0, 1);
    	    	    printf("%c ", rx_buf[i]);
    	    	}
    	    }

    }
}
