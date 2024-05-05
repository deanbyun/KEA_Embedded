/*
 * user-task07.c
 *
 *  Created on: Aug 30, 2023
 *      Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 *      STM32Cube Package/Projects/Board/Applications/FreeRTOS/
 *      Message Queue examples(manual page 22)
 */

#include "user-tasks.h"

static char StringBuf[UART_BUF_SIZE];

#define QUEUE_SIZE        (uint32_t) 2

osMessageQId osQueue;
uint32_t ProducerValue = 0, ConsumerValue = osWaitForever;

static void MessageQueueProducer (const void *argument);
static void MessageQueueConsumer (const void *argument);

/**
  * @brief  Message Queue Producer Thread.
  * @param  argument: Not used
  * @retval None
  */
static void MessageQueueProducer (const void *argument)
{
    HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_1Y);
    sprintf((char *)StringBuf, "[Message Queue Producer][%lu] %s", ProducerValue, "Send.");
    user_uart_send_msg(&huart1, StringBuf);

  for(;;)
  {
    if(osMessagePut (osQueue, ProducerValue, 100) != osOK)
    {
    	/* Toggle LED3 to indicate error */
    	user_gpio_led_on_blue();
    	sprintf((char *)StringBuf, "[Message Queue Producer][%lu] %s", ProducerValue, "Error.");
    	user_uart_send_msg(&huart1, StringBuf);

    } else {
      ++ProducerValue;

      HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_1Y);
      sprintf((char *)StringBuf, "[Message Queue Producer][%lu] %s", ProducerValue, "Send.");
      user_uart_send_msg(&huart1, StringBuf);

      osDelay(800);
    }
  }
}

/**
  * @brief  Message Queue Consumer Thread.
  * @param  argument: Not used
  * @retval None
  */
static void MessageQueueConsumer (const void *argument)
{
  osEvent event;

  for(;;)
  {
    /* Get the message from the queue */
    event = osMessageGet(osQueue, 100);

    if(event.status == osEventMessage)
    {
      if(event.value.v != ConsumerValue)
      {
        /* Catch-up. */
        ConsumerValue = event.value.v;

        /* Toggle LED3 to indicate error */
        HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_2R);
        sprintf((char *)StringBuf, "[Message Queue Consumer][%lu] %s", ConsumerValue, "Received.");
        user_uart_send_msg(&huart1, StringBuf);

      } else {
        /* Increment the value we expect to remove from the queue next time round. */
        ++ConsumerValue;
      }
    }
  }
}

void task07_thread_create(void)
{
	osMessageQDef(osqueue, QUEUE_SIZE, uint16_t);
	osQueue = osMessageCreate (osMessageQ(osqueue), NULL);

	/* Note the producer has a lower priority than the consumer when the tasks are spawned. */
	//osThreadDef(QCons, MessageQueueConsumer, osPriorityBelowNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadDef(QCons, MessageQueueConsumer, osPriorityNormal, 0, configMINIMAL_STACK_SIZE*2);
	osThreadCreate(osThread(QCons), NULL);

	osThreadDef(QProd, MessageQueueProducer, osPriorityBelowNormal, 0, configMINIMAL_STACK_SIZE);
	osThreadCreate(osThread(QProd), NULL);
}
