/*
 * user-task02.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 *      STM32Cube Package/Projects/Board/Applications/FreeRTOS/
 *      Thread examples(manual page 18)
 */

#include "user-tasks.h"

static char StringBuf[UART_BUF_SIZE];

osThreadId LEDThread1Handle, LEDThread2Handle;

static void LED_Thread1(void const *argument)
{
	uint32_t count = 0;
	(void) argument;

	for(;;)
	{
		count = osKernelSysTick() + 5000;
		user_uart_send_msg(&huart1, "[LED Thread1] Starting...");

		/* Toggle LED1 every 200 ms for 5 s */
		while (count >= osKernelSysTick()) {
			uint32_t tick;		//DEAN
			HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_1Y);
			user_uart_send_msg(&huart1, "[LED Thread1] LED1 Toggle each 200ms.");
			osDelay(200);
			//DEAN Add tick
			tick = osKernelSysTick();
			sprintf((char*)StringBuf, "tick = %u", tick);
			user_uart_send_msg(&huart1, StringBuf);
		}

		/* Turn off LED1 */
		user_gpio_led_off_yellow();

		/* Suspend Thread 1 */
		osThreadSuspend(NULL);		//NULL = itself

		count = osKernelSysTick() + 5000;

		/* Toggle LED1 every 400 ms for 5 s */
		while (count >= osKernelSysTick()) {
			HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_1Y);
			user_uart_send_msg(&huart1, "[LED Thread1] LED1 Yellow Toggle each 400ms.");
			osDelay(400);
		}

		/* Resume Thread 2*/
		osThreadResume(LEDThread2Handle);
	}
}

static void LED_Thread2(void const *argument)
{
	uint32_t count;
	(void) argument;

	for(;;)
	{
		count = osKernelSysTick() + 10000;
		user_uart_send_msg(&huart1, "[LED Thread2] Starting...");

		/* Toggle LED2 every 500 ms for 10 s */
		while (count >= osKernelSysTick()) {
			HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_2R);
			user_uart_send_msg(&huart1, "[LED Thread2] LED2 Red Toggle each 500ms.");
			osDelay(500);
		}

		/* Turn off LED2 */
		user_gpio_led_off_red();

		/* Resume Thread 1 */
		osThreadResume(LEDThread1Handle);

		/* Suspend Thread 2 */
		osThreadSuspend(NULL);
	}
}

void task02_thread_create(void)
{
	/* Thread 1 definition */
	osThreadDef(LED1, LED_Thread1, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

	/*  Thread 2 definition */
	osThreadDef(LED2, LED_Thread2, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

	/* Start thread 1 */
	LEDThread1Handle = osThreadCreate (osThread(LED1), NULL);

	/* Start thread 2 */
	LEDThread2Handle = osThreadCreate (osThread(LED2), NULL);
}
