/*
 * user-task04.c
 *
 *  Created on: Aug 30, 2023
 *      Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 *      STM32Cube Package/Projects/Board/Applications/FreeRTOS/
 *      Semaphores ISR examples(manual page 20)
 */

#include "user-tasks.h"

osSemaphoreId osSemaphoreISR;

/**
  * @brief  Semaphore Test.
  * @param  argument: Not used
  * @retval None
  */
static void SemaphoreTestThread (void const *argument)
{
	for(;;)
	{
		if (osSemaphoreISR != NULL)
		{
			/* Try to obtain the semaphore. */
			if(osSemaphoreWait(osSemaphoreISR, 0) == osOK)
			{
				/* Toggle LED3 */
				HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_3B);
				user_uart_send_msg(&huart1, "[SEM Thread1] LED3 Toggle.");
			}
		}
	}
}

void task04_thread_create(void)
{
	/* Define used semaphore */
	osSemaphoreDef(SEM);

	/* Create the semaphore  */
	osSemaphoreISR = osSemaphoreCreate(osSemaphore(SEM) , 1);

	/* Create the Thread that toggle LED1 */
	osThreadDef(SEM_Thread, SemaphoreTestThread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(SEM_Thread), (void *) osSemaphoreISR);
}
