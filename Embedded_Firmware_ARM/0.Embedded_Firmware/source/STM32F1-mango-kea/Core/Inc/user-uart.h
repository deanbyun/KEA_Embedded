/*
 * user-uart.h
 *
 *  Created on: Aug 3, 2023
 *      Author: jungjaejoon <rgbi3307@naver.com> on the www.kernel.bz
 */

#ifndef INC_USER_UART_H_
#define INC_USER_UART_H_

#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_uart.h>

#include <stdio.h>
#include <string.h>

#define UART_BUF_SIZE           160
#define UART_BUF_MAX            255
#define UART_TIMEOUT            3000

#define UART_OK_MSG             "OK"
#define UART_CONNECT_MSG        "\r\n[CONNECT] "
#define UART_SEND_OK_MSG        "SEND OK"
#define UART_ER_MSG             "ERROR"
#define UART_ENTER              "\n"
#define UART_NEWLINE            "\r\n"
#define UART_NL_OK              "\r\nOK\r"
#define UART_NL_ER              "\r\nERROR\r"
#define UART_NL_UNKNOWN         "\r\nUNKNOWN\r"

#define SIZEOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))

void user_uart_send_char(UART_HandleTypeDef *huart, const uint8_t *buf);
void user_uart_send_msg(UART_HandleTypeDef *huart, const char *msg);


#endif /* INC_USER_UART_H_ */
