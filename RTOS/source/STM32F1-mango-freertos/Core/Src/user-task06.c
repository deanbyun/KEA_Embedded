/*
 * user-task05.c
 *
 *  Created on: Aug 30, 2023
 *      Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 *      STM32Cube Package/Projects/Board/Applications/FreeRTOS/
 *      Mutexes examples(manual page 21)
 */

#include "user-tasks.h"

#define mutexSHORT_DELAY     ((uint32_t) 20)
#define mutexNO_DELAY        ((uint32_t) 0)
#define mutexTWO_TICK_DELAY  ((uint32_t) 2)

static osMutexId osMutex;

/* Variables used to detect and latch errors. */
static __IO uint32_t HighPriorityThreadCycles = 0, MediumPriorityThreadCycles = 0, LowPriorityThreadCycles = 0;

/* Handles of the two higher priority tasks, required so they can be resumed (unsuspended). */
static osThreadId osHighPriorityThreadHandle, osMediumPriorityThreadHandle;

/* Private function prototypes */
static void MutexHighPriorityThread(void const *argument);
static void MutexMeduimPriorityThread(void const *argument);
static void MutexLowPriorityThread(void const *argument);


/**
  * @brief  Mutex High Priority Thread.
  * @param  argument: Not used
  * @retval None
  */
static void MutexHighPriorityThread(void const *argument)
{
  /* Just to remove compiler warning. */
  (void) argument;

  for(;;)
  //int i;
  //for(i=0; i < 10; i++)
  {
	//tick_output("High Thread Start");
	//wait(lock) the mutex
    if(osMutexWait(osMutex, mutexTWO_TICK_DELAY) != osOK)
    {
      /* Toggle LED 3 to indicate error */
      user_gpio_led_on_blue();
      user_uart_send_msg(&huart1, "[Mutex Thread1 High] Error osMutexWait()");
    }

    osDelay(mutexSHORT_DELAY);

    /* Keep count of the number of cycles this thread has performed */
    HighPriorityThreadCycles++;
    HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_1Y);
    user_uart_send_msg(&huart1, "[Mutex Thread1 High] Running...");

    osDelay(1000);

	//release(unlock) the mutex
	if(osMutexRelease(osMutex) != osOK)
	{
	  /* Toggle LED 3 to indicate error */
	  user_gpio_led_on_blue();
	  user_uart_send_msg(&huart1, "[Mutex Thread1 High] Error osMutexRelease()");
	}

	//tick_output("High Thread End");

	/* Suspend ourselves to the medium priority thread can execute */
	osThreadSuspend(NULL);
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

  for(;;)
  //int i;
  //for(i=0; i < 10; i++)
  {
	//wait(lock) the mutex
    if(osMutexWait(osMutex, osWaitForever) == osOK)
    {
      tick_output("Medium Thread Start");
      if(osThreadGetState(osHighPriorityThreadHandle) != osThreadSuspended)
      {
        user_gpio_led_on_blue();
        user_uart_send_msg(&huart1, "[Mutex Thread2 Medium] Error: high priority not suspended.");

      } else {

        /* The High and Medium priority threads should be in lock step. */
		if(HighPriorityThreadCycles != (MediumPriorityThreadCycles + 1))
		{
			/* Toggle LED 3 to indicate error */
			user_gpio_led_on_blue();
			user_uart_send_msg(&huart1, "[Mutex Thread2 Medium] HighPriorityThreadCycles Error.");
		}

		/* Keep count of the number of cycles this task has performed so a stall can be detected. */
		MediumPriorityThreadCycles++;
		HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_2R);
		user_uart_send_msg(&huart1, "[Mutex Thread2 Medium] Running...");

		osDelay(800);

        if(osMutexRelease(osMutex) != osOK) {
		  /* Toggle LED 3 to indicate error */
		  user_gpio_led_on_blue();
		  user_uart_send_msg(&huart1, "[Mutex Thread2 Medium] Error osMutexRelease()");
		}
        tick_output("Medium Thread End");
        osThreadSuspend(NULL);
      }

    } else {
      user_gpio_led_on_blue();
      user_uart_send_msg(&huart1, "[Mutex Thread2 Medium] Error osMutexWait()");
    }
  } //for
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

  for(;;)
  //int i;
  //for(i=0; i < 10; i++)
  {
	//wait(lock) the mutex
    if(osMutexWait(osMutex, mutexNO_DELAY) == osOK)
    {
       tick_output("Low Thread Start");
      /* Is the high and medium-priority threads suspended? */
      if((osThreadGetState(osHighPriorityThreadHandle) != osThreadSuspended)
    		  || (osThreadGetState(osMediumPriorityThreadHandle) != osThreadSuspended))
      {
    	  /* Toggle LED 3 to indicate error */
    	  user_gpio_led_on_blue();
    	  user_uart_send_msg(&huart1, "[Mutex Thread3 Low] Error1: osThreadSuspended.");
      }
      else
      {
        LowPriorityThreadCycles++;
        user_uart_send_msg(&huart1, "[Mutex Thread3 Low] Running...");
        osDelay(600);

        osThreadResume(osMediumPriorityThreadHandle);
        osThreadResume(osHighPriorityThreadHandle);

        if((osThreadGetState(osHighPriorityThreadHandle) == osThreadSuspended)
        		|| (osThreadGetState(osMediumPriorityThreadHandle) == osThreadSuspended))
        {
          /* Toggle LED 3 to indicate error */
          user_gpio_led_on_blue();
          user_uart_send_msg(&huart1, "[Mutex Thread3 Low] Error2: osThreadSuspended.");
        }

        /* Release the mutex, disinheriting the higher priority again. */
        if(osMutexRelease(osMutex) != osOK)
        {
          /* Toggle LED 3 to indicate error */
        	user_gpio_led_on_blue();
        	user_uart_send_msg(&huart1, "[Mutex Thread3 Low] Error: osMutexRelease()");
        }
        tick_output("Low Thread End");
      }
    }

#if configUSE_PREEMPTION == 0
    {
      taskYIELD();
    }
#endif

  } //for
}

void task06_thread_create(void)
{
	/* Creates the mutex */
	osMutexDef(osMutex);
	osMutex = osMutexCreate(osMutex(osMutex));

	user_gpio_led_off_blue();

	if(osMutex != NULL)
	{
		/* Define and create the high priority thread */
		osThreadDef(MutHigh, MutexHighPriorityThread, osPriorityBelowNormal, 0, configMINIMAL_STACK_SIZE);
		osHighPriorityThreadHandle = osThreadCreate(osThread(MutHigh), NULL);

		/* Define and create the medium priority thread */
		osThreadDef(MutMedium, MutexMeduimPriorityThread, osPriorityLow, 0, configMINIMAL_STACK_SIZE);
		osMediumPriorityThreadHandle = osThreadCreate(osThread(MutMedium), NULL);

		/* Define and create the low priority thread */
		osThreadDef(MutLow, MutexLowPriorityThread, osPriorityIdle, 0, configMINIMAL_STACK_SIZE);
		osThreadCreate(osThread(MutLow), NULL);
	}
}
