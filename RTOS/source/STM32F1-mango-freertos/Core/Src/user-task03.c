/*
 * user-task03.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 *      STM32Cube Package/Projects/Board/Applications/FreeRTOS/
 *      Semaphores examples(manual page 19)
 */

#include "user-tasks.h"

//static char StringBuf[UART_BUF_SIZE];
#define semtstSTACK_SIZE  configMINIMAL_STACK_SIZE

osThreadId SemThread1Handle, SemThread2Handle;
osSemaphoreId osSemaphore;

/**
  * @brief  Semaphore Thread 1 function
  * @param  argument: shared semaphore
  * @retval None
  */
static void SemaphoreThread1 (void const *argument)
{
  uint32_t count = 0;
  osSemaphoreId semaphore = (osSemaphoreId) argument;

  for(;;)
  {
    if (semaphore != NULL)
    {
      /* Try to obtain the semaphore. */
      if(osSemaphoreWait(semaphore , 100) == osOK)
      {
        count = osKernelSysTick() + 5000;
        user_uart_send_msg(&huart1, "[SEM Thread1] obtain the semaphore.");

        while (count >= osKernelSysTick())
        {
        	/* Toggle LED1 */
        	HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_1Y);
        	user_uart_send_msg(&huart1, "[SEM Thread1] LED1 Toggle each 200ms.");

        	/* Delay 200 ms */
        	osDelay(200);
        }

        /* Turn off LED1 */
        user_gpio_led_off_yellow();

        /* Release the semaphore */
        osSemaphoreRelease(semaphore);
    	user_uart_send_msg(&huart1, "[SEM Thread1] Release the semaphore.");

        /* Suspend ourseleves to execute thread 2 (lower priority)  */
        osThreadSuspend(NULL);
    	user_uart_send_msg(&huart1, "[SEM Thread1] Suspend the semaphore to execute thread 2.");
      }
    } //if
  } //for
}

/**
  * @brief  Semaphore Thread 2 function
  * @param  argument: shared semaphore
  * @retval None
  */
static void SemaphoreThread2 (void const *argument)
{
  uint32_t count = 0;
  osSemaphoreId semaphore = (osSemaphoreId) argument;

  for(;;)
  {
    if (semaphore != NULL)
    {
      /* Try to obtain the semaphore. */
      if(osSemaphoreWait(semaphore , 0) == osOK)
      {
        /* Resume Thread 1 (higher priority)*/
        osThreadResume(SemThread1Handle);
        user_uart_send_msg(&huart1, "[SEM Thread2] obtain the semaphore.");

        count = osKernelSysTick() + 5000;

        /* Toggle LED2 every 200 ms for 5 seconds*/
        while (count >= osKernelSysTick())
        {
        	HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_2R);
        	user_uart_send_msg(&huart1, "[SEM Thread2] LED2 Red Toggle each 200ms.");

        	osDelay(200);
        }

        /* Turn off LED2 */
        user_gpio_led_off_red();

        /* Release the semaphore to unblock Thread 1 (higher priority)  */
        osSemaphoreRelease(semaphore);
    	user_uart_send_msg(&huart1, "[SEM Thread2] Release the semaphore to unblock Thread 1.");
      }
    } //if
  } //for
}


void task03_thread_create(void)
{
	/* Define used semaphore */
	osSemaphoreDef(SEM);	//osSemaphoreDef_t

	/* Create the semaphore used by the two threads */
	osSemaphore = osSemaphoreCreate(osSemaphore(SEM) , 1);

	/* Create the first Thread */
	osThreadDef(SEM_Thread1, SemaphoreThread1, osPriorityLow, 0, semtstSTACK_SIZE);
	SemThread1Handle = osThreadCreate(osThread(SEM_Thread1), (void *) osSemaphore);

	/* Create the second Thread */
	osThreadDef(SEM_Thread2, SemaphoreThread2, osPriorityIdle, 0, semtstSTACK_SIZE);
	SemThread2Handle = osThreadCreate(osThread(SEM_Thread2), (void *) osSemaphore);
}

