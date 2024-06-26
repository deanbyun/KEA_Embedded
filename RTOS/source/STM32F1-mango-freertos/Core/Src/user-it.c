/*
 * user-it.c
 *
 *  Created on: Aug 3, 2023
 *      Author: Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 */

#include <stm32f1xx_hal.h>
#include "user-gpio.h"
#include "user-uart.h"
#include "cmsis_os.h"

int sw_count_flag = 0;

//user-task04.c
extern osSemaphoreId osSemaphoreISR;


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if (huart->Instance == USART1) {
		user_uart_send_msg(huart, "UART1 Rx interrupt occurred.");
	}
}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if (huart->Instance == USART1) {
		user_uart_send_msg(huart, "UART1 Event interrupt occurred.");
		//HAL_UART_Receive_IT(huart, UartRxData, Size);
		//HAL_UART_Transmit(huart, UartRxData, Size, 10);
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if (sw_count_flag < 10)		//100ms x 10 == 1000ms
	//if (sw_count_flag < 50)			//DEAN 50ms x 10 == 500ms
		return;

	if (GPIO_Pin == GPIO_PIN_0) {
		HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_1Y);
		//user_gpio_fnd_on_1();
		user_uart_send_msg(&huart1, "[GPIO0 Interrupt] PB5 LED1 Yellow.");
	}

	if (GPIO_Pin == GPIO_PIN_1) {
		HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_2R);
		//user_gpio_fnd_on_2();
		user_uart_send_msg(&huart1, "[GPIO1 Interrupt] PB9 LED2 Red.");

		//user-task04.c
		osSemaphoreRelease(osSemaphoreISR);
	}

	sw_count_flag = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    static uint32_t cnt=0;

    //SYSCLK == HCLK == 8Mhz
    //Prescaler == 8000, Period == HCLK / Prescaler == 1KHz(1ms)
    //Counter == 1000, Interval Time == Period * Counter == 1ms x 1000 == 1s
    if (htim->Instance == TIM1) {
    	user_gpio_fnd_digit(cnt++);
    	user_uart_send_msg(&huart1, "[Timer1 Interrupt] Running...");
    	cnt %= 10;
    }

    if (htim->Instance == TIM2) {	//10ms	//DEAN -> 100ms
		HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_2R);	//Red	//DEAN
    	//user_uart_send_msg(&huart1, "[Timer2 Interrupt] Running...");
		sw_count_flag++;
	}

    if (htim->Instance == TIM3) {		//DEAN -> 3000ms
		HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_3B);	//Blue	//DEAN
		user_uart_send_msg(&huart1, "[Timer3 Interrupt] Running...");
	}
}
