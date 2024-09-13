/*
 * user-i2c.c
 *
 *  Created on: Aug 3, 2023
 *      Author: jungjaejoon <rgbi3307@naver.com> on the www.kernel.bz
 */

#include <string.h>

#include "user-i2c.h"
#include "user-uart.h"

//main.c
extern UART_HandleTypeDef huart1;
extern I2C_HandleTypeDef hi2c1;

//user-uart.c
extern char UartBuf[UART_BUF_SIZE];

uint8_t I2cBuf[3];

static inline uint16_t _i2c_data_conv(uint8_t *data)
{
	uint16_t value;
	value = (data[0] << 8) + data[1];

	sprintf(UartBuf, "I2C Sensor Output Value: %u\n", value);
	user_uart_send_msg(&huart1, UartBuf);

	return value;
}

static inline void _i2c_error_handler(void)
{
    user_uart_send_msg(&huart1, "Error on the I2C.");
}

static int32_t _i2c_master_send(uint16_t dev_addr, uint8_t *data, uint32_t len)
{
    while(HAL_I2C_Master_Transmit_IT(&hi2c1, dev_addr, data, len) != HAL_OK)
    //while (HAL_I2C_Master_Transmit(&hi2c1, dev_addr, data, len, 1000) != HAL_OK)
    {
    	sprintf(UartBuf, "I2C SEND: while(): <%02X> [%02X] [%02X]", dev_addr, data[0], data[1]);
    	user_uart_send_msg(&huart1, UartBuf);

        if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF) {
            _i2c_error_handler();
            return 0;
        }
    }

    //while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) {}

    sprintf(UartBuf, "I2C SEND: END: <%02X> [%02X] [%02X]", dev_addr, data[0], data[1]);
    user_uart_send_msg(&huart1, UartBuf);

    return 1;
}

static int32_t _i2c_master_recv(uint16_t dev_addr, uint8_t *data, uint32_t len)
{
    while (HAL_I2C_Master_Receive_IT(&hi2c1, dev_addr, data, len) != HAL_OK)
	//while (HAL_I2C_Master_Receive(&hi2c1, dev_addr, data, len, 1000) != HAL_OK)
    {
		sprintf(UartBuf, "I2C RECV: while(): <%02X> [%02X] [%02X]", dev_addr, data[0], data[1]);
		user_uart_send_msg(&huart1, UartBuf);

        if (HAL_I2C_GetError(&hi2c1) != HAL_I2C_ERROR_AF) {
            _i2c_error_handler();
            return 0;
        }
    }

    //while (HAL_I2C_GetState(&hi2c1) != HAL_I2C_STATE_READY) {}

	sprintf(UartBuf, "I2C RECV: END: <%02X> [%02X] [%02X]", dev_addr, data[0], data[1]);
	user_uart_send_msg(&huart1, UartBuf);

	_i2c_data_conv(data);

    return 1;
}

void user_i2c_bh17_test(uint32_t loop_cnt)
{
	uint16_t i2c_dev_addr = I2C_ADDR_BH17 << 1;		// 7bit
	HAL_StatusTypeDef hal_ret;

	memset(I2cBuf, 0, SIZEOF(I2cBuf));

	I2cBuf[0] = 0x10;
	hal_ret = HAL_I2C_Master_Transmit_IT(&hi2c1, i2c_dev_addr, I2cBuf, 1);
	//hal_ret = HAL_I2C_Master_Transmit(&hi2c1, i2c_dev_addr, I2cBuf, 1, 1000);	//1000ms, 1s

	sprintf(UartBuf, "I2C SEND: RET:%d: <%02X> [%02X] [%02X]",
					hal_ret, i2c_dev_addr, I2cBuf[0], I2cBuf[1]);
	user_uart_send_msg(&huart1, UartBuf);

	HAL_Delay(200);

	for (int i = 0; i < loop_cnt; i++) {
		hal_ret = HAL_I2C_Master_Receive_IT(&hi2c1, i2c_dev_addr, I2cBuf, 2);
		//hal_ret = HAL_I2C_Master_Receive(&hi2c1, i2c_dev_addr, I2cBuf, 2, 2000);	//2s

		sprintf(UartBuf, "I2C RECV[%d]: RET:%d: <%02X> [%02X] [%02X]",
					i, hal_ret, i2c_dev_addr, I2cBuf[0], I2cBuf[1]);
		user_uart_send_msg(&huart1, UartBuf);

		_i2c_data_conv(I2cBuf);		// convert to 16 bit

		HAL_Delay(200);
	}
}

int32_t user_i2c_bh17_device_set(void)
{
	uint16_t i2c_dev_addr = I2C_ADDR_BH17 << 1;
	int32_t ret;

	memset(I2cBuf, 0, SIZEOF(I2cBuf));
	I2cBuf[0] = 0x10;
	ret = _i2c_master_send(i2c_dev_addr, I2cBuf, 1);
	return ret;
}

int32_t user_i2c_bh17_data_get(void)
{
	uint16_t i2c_dev_addr = I2C_ADDR_BH17 << 1;
	int32_t ret;

	ret = _i2c_master_recv(i2c_dev_addr, I2cBuf, 2);
	return ret;
}
