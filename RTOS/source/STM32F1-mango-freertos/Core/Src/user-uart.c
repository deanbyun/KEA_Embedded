/*
 * user-uart.c
 *
 *  Created on: Aug 3, 2023
 *      Author: Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 */

#include <stdio.h>
#include <string.h>
#include "user-uart.h"

char UartBuf[UART_BUF_SIZE];

void user_uart_send_char(UART_HandleTypeDef *huart, const uint8_t *buf)
{
    uint32_t len;

    len = strlen((const char *)buf);
    HAL_UART_Transmit(huart, buf, len, UART_TIMEOUT);

    if (buf[len-1] == '\r')
    	HAL_UART_Transmit(huart, (const uint8_t *)UART_ENTER, 1, UART_TIMEOUT);
}


void user_uart_send_msg(UART_HandleTypeDef *huart, const char *msg)
{
    uint32_t len;

    len = strlen((const char *)msg);
    if (msg[len-1] == '\r') {
        sprintf((char *)UartBuf, "%s%s", msg, UART_ENTER);
        len += 1;
    } else {
        sprintf((char *)UartBuf, "%s%s", msg, UART_NEWLINE);
        len += 2;
    }

    HAL_UART_Transmit(huart, (const uint8_t *)UartBuf, len, UART_TIMEOUT);
}
