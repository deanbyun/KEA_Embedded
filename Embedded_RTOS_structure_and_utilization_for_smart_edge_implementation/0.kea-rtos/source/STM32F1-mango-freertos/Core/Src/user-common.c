/*
 * user-common.c
 *
 *  Created on: Apr 24, 2024
 *  Author: Byun JungHoon
 */

#include "user-tasks.h"

void tick_output(char *name)
{
	uint32_t tick;
	char buf[80];
	tick = osKernelSysTick();
	sprintf((char*)buf, "[Thread] %s: tick = %lu", name, tick);
	user_uart_send_msg(&huart1, buf);
}
