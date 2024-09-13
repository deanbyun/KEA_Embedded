/*
 * user-i2c.h
 *
 *  Created on: Aug 3, 2023
 *      Author: jungjaejoon <rgbi3307@naver.com> on the www.kernel.bz
 */

#ifndef INC_USER_I2C_H_
#define INC_USER_I2C_H_

#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_i2c.h>

#define I2C_ADDR_BH17	0x23	//0010_0011
//#define I2C_ADDR_BH17	(0x23 << 1)
//#define I2C_ADDR_BH17	0x46	//0100_0110

void user_i2c_bh17_test(uint32_t loop_cnt);
int32_t user_i2c_bh17_device_set(void);
int32_t user_i2c_bh17_data_get(void);

#endif /* INC_USER_I2C_H_ */
