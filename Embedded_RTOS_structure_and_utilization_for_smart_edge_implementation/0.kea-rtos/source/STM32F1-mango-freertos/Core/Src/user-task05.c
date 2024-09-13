/*
 * user-task05.c
 *
 *  Created on: Aug 30, 2023
 *      Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 *      STM32Cube Package/Projects/Board/Applications/FreeRTOS/
 *      Mutexes examples(manual page 21)
 */

#include "user-tasks.h"

/* Variables used to detect and latch errors. */
static __IO uint32_t HighPriorityThreadCycles = 0, MediumPriorityThreadCycles = 0, LowPriorityThreadCycles = 0;

/* Handles of the two higher priority tasks, required so they can be resumed (unsuspended). */
static osThreadId osHighPriorityThreadHandle, osMediumPriorityThreadHandle;

/* Private function prototypes */
static void MutexHighPriorityThread(void const *argument);
static void MutexMeduimPriorityThread(void const *argument);
static void MutexLowPriorityThread(void const *argument);

/*	//DEAN move user-common.c
static void tick_output(char *name)
{
	uint32_t tick;
	char buf[80];
	tick = osKernelSysTick();
	sprintf((char*)buf, "Thread %s: tick = %lu", name, tick);
	user_uart_send_msg(&huart1, buf);
}
*/

/**
  * @brief  Mutex High Priority Thread.
  * @param  argument: Not used
  * @retval None
  */
static void MutexHighPriorityThread(void const *argument)
{
  /* Just to remove compiler warning. */
  (void) argument;
  char buf[80];

  for(;;)
  {
    /* Keep count of the number of cycles this thread has performed */
	tick_output("High Start");
    HighPriorityThreadCycles++;
    HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_1Y);
    user_uart_send_msg(&huart1, "[Mutex Thread1 High] Running...");
	sprintf((char*)buf, "[Mutex Thread1 High] High Priority Count: %ld", HighPriorityThreadCycles);
	user_uart_send_msg(&huart1, buf);

    osDelay(800);
    tick_output("High End");
  }
}

/**
  * @brief  Mutex Medium Priority Thread.
  * @param  argument: Not used
  * @retval None
  */
static void MutexMeduimPriorityThread(void const *argument)
{
  /* Just to remove compiler warning */
  (void) argument;
  char buf[80];

  for(;;)
  {
	tick_output("Medium Start");
    /* The High and Medium priority threads should be in lock step. */
    if(HighPriorityThreadCycles != (MediumPriorityThreadCycles + 1))
    {
    	/* Toggle LED 3 to indicate error */
    	user_gpio_led_on_blue();
    	user_uart_send_msg(&huart1, "[Mutex Thread2 Medium] Error: MediumPriorityThreadCycles.");
    }

    /* Keep count of the number of cycles this task has performed so a stall can be detected. */
    MediumPriorityThreadCycles++;
    HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_2R);
    user_uart_send_msg(&huart1, "[Mutex Thread2 Medium] Running...");
	sprintf((char*)buf, "[Mutex Thread2 Medium] Medium Priority Count: %ld", MediumPriorityThreadCycles);
	user_uart_send_msg(&huart1, buf);

    osDelay(800);
    tick_output("Medium End");
  }
}

/**
  * @brief  Mutex Low Priority Thread.
  * @param  argument: Not used
  * @retval None
  */
static void MutexLowPriorityThread(void const *argument)
{
  /* Just to remove compiler warning. */
  (void) argument;
  char buf[80];

  for(;;)
  {
	tick_output("Low Start");
	/* The High and Medium priority threads should be in lock step. */
	if(MediumPriorityThreadCycles != (LowPriorityThreadCycles + 1))
	{
		/* Toggle LED 3 to indicate error */
		user_gpio_led_on_blue();
		user_uart_send_msg(&huart1, "[Mutex Thread3 Low] Error: LowPriorityThreadCycles.");
	}

	LowPriorityThreadCycles++;
	user_uart_send_msg(&huart1, "[Mutex Thread3 Low] Running...");
	sprintf((char*)buf, "[Mutex Thread3 Low] Low Priority Count: %ld", LowPriorityThreadCycles);
	user_uart_send_msg(&huart1, buf);

	osDelay(800);
	tick_output("Low End");
  }
}

void task05_thread_create(void)
{
	user_gpio_led_off_blue();

	/* Define and create the low priority thread */
	osThreadDef(MutLow, MutexLowPriorityThread, osPriorityIdle, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(MutLow), NULL);

	/* Define and create the medium priority thread */
	osThreadDef(MutMedium, MutexMeduimPriorityThread, osPriorityLow, 0, configMINIMAL_STACK_SIZE);
	osMediumPriorityThreadHandle = osThreadCreate(osThread(MutMedium), NULL);

	/* Define and create the high priority thread */
	osThreadDef(MutHigh, MutexHighPriorityThread, osPriorityBelowNormal, 0, configMINIMAL_STACK_SIZE);
	osHighPriorityThreadHandle = osThreadCreate(osThread(MutHigh), NULL);
}
