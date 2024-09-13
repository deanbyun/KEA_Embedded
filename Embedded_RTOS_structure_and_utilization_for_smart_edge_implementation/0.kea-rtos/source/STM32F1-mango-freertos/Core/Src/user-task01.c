/*
 * user-task01.c
 *
 *  Created on: Aug 29, 2023
 *      Author: Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 *       Refer: https://www.keil.com/pack/doc/CMSIS/RTOS/html/group__CMSIS__RTOS__ThreadMgmt.html
 *       Refer: https://arm-software.github.io/CMSIS_5/develop/RTOS2/html/rtos2_tutorial.html#rtos2_tutorial_start
 */

#include "user-tasks.h"

static char StringBuf[UART_BUF_SIZE];

static void task01_thread(void const *arg)
{
	osThreadId id;
	osPriority priority;

	id = osThreadGetId();
	if (id == NULL) {
		user_uart_send_msg(&huart1, "[Task01 FAIL] osThreadGetId().");
		return;
	} else {
		sprintf((char *)StringBuf, "[Task01] id=%p %s", id, "Running...");
		user_uart_send_msg(&huart1, StringBuf);
	}

	while(1) {
		priority = osThreadGetPriority(id);
		sprintf((char *)StringBuf, "[Task01][%d] %s", priority, "Running...");
		user_uart_send_msg(&huart1, StringBuf);

		/*
		osStatus   status;
		status = osThreadSetPriority (id, osPriorityBelowNormal);
		if (status != osOK)
			user_uart_send_msg(&huart1, "[Task01 FAIL] osThreadSetPriority().");
		*/

		osDelay(2000);	//2000ms
	}
}

void task01_thread_create(void)
{
	osThreadId id;

	user_uart_send_msg(&huart1, "[Task01] Starting...");

	osThreadDef(task01, task01_thread, osPriorityNormal, 0, 128);
	id = osThreadCreate(osThread(task01), NULL);
	if (id == NULL) {
		user_uart_send_msg(&huart1, "[Task01 FAIL] osThreadCreate().");
	}
	//osThreadTerminate(id);
}
