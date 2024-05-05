/*
 * user-task08.c
 *
 *  Created on: Aug 30, 2023
 *      Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 *      STM32Cube Package/Projects/Board/Applications/FreeRTOS/
 *      Timer examples(manual page 23)
 */

#include "user-tasks.h"

int Lock;

/**
  * @brief  Timer Clbk that toggle LED1
  * @param  argument not used
  * @retval None
  */
static void osTimerCallback (void const *argument)
{
	(void) argument;

	Lock = 1;
	/* Toggle LED2 each 200ms */
	HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_2R);
	user_uart_send_msg(&huart1, "[osTimerCallback] Toggle LED2 each 200ms.");
	Lock = 0;
}

/**
  * @brief  Toggle LED3 thread
  * @param  argument not used
  * @retval None
  */
static void ToggleLEDsThread(void const *argument)
{
	(void) argument;

	for(;;)
	{
		if (Lock == 1)
			osDelay(10);

		/* Toggle LED1 each 400ms*/
		HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_1Y);
		user_uart_send_msg(&huart1, "[ToggleLEDsThread] Toggle LED1 each 400ms.");

		osDelay(400);
	}
}

void task08_thread_create(void)
{
	/* Create Timer */
	osTimerDef(LEDTimer, osTimerCallback);
	osTimerId osTimer = osTimerCreate (osTimer(LEDTimer), osTimerPeriodic, NULL);

	/* Start Timer */
	osTimerStart(osTimer, 200);	//period 200ms

	/* Create LED Thread */
	osThreadDef(LEDThread, ToggleLEDsThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate (osThread(LEDThread), NULL);
}
