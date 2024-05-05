/*
 * user-gpio.h
 *
 *  Created on: Aug 1, 2023
 *      Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 */

#ifndef INC_USER_GPIO_H_
#define INC_USER_GPIO_H_

#include <stm32f1xx_hal.h>
#include <stm32f1xx_hal_gpio.h>

#define USER_GPIO_LED_ON		GPIO_PIN_RESET
#define USER_GPIO_LED_OFF		GPIO_PIN_SET

//GPIOB
#define USER_GPIO_PIN_LED_1Y	GPIO_PIN_5		//Yellow
#define USER_GPIO_PIN_LED_2R	GPIO_PIN_9		//Red
#define USER_GPIO_PIN_LED_3B	GPIO_PIN_8		//Blue

//GPIOC
#define USER_GPIO_PIN_FND_ALL	0xFF
#define USER_GPIO_PIN_FND_1		GPIO_PIN_1 | GPIO_PIN_2
#define USER_GPIO_PIN_FND_2		GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_3 | GPIO_PIN_4
#define USER_GPIO_PIN_FND_3		GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_7 | GPIO_PIN_2 | GPIO_PIN_3
#define USER_GPIO_PIN_FND_4		GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_7 | GPIO_PIN_5
#define USER_GPIO_PIN_FND_5		GPIO_PIN_0 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_5 | GPIO_PIN_7
#define USER_GPIO_PIN_FND_6		GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7
#define USER_GPIO_PIN_FND_7		GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2
#define USER_GPIO_PIN_FND_8		GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7
#define USER_GPIO_PIN_FND_9		GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_5 | GPIO_PIN_7
#define USER_GPIO_PIN_FND_0		GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5


void user_gpio_led_off_all(void);
void user_gpio_led_on_all(void);
void user_gpio_led_toggle_delay(uint32_t ms);

void user_gpio_led_on_yellow(void);
void user_gpio_led_off_yellow(void);
void user_gpio_led_on_red(void);
void user_gpio_led_off_red(void);
void user_gpio_led_on_blue(void);
void user_gpio_led_off_blue(void);


void user_gpio_fnd_off_all(void);
void user_gpio_fnd_clear(void);
void user_gpio_fnd_on_all(void);
void user_gpio_fnd_test(void);
void user_gpio_fnd_digit(int digit);

void user_gpio_fnd_on_1(void);
void user_gpio_fnd_on_2(void);
void user_gpio_fnd_on_3(void);
void user_gpio_fnd_on_4(void);
void user_gpio_fnd_on_5(void);
void user_gpio_fnd_on_6(void);
void user_gpio_fnd_on_7(void);
void user_gpio_fnd_on_8(void);
void user_gpio_fnd_on_9(void);
void user_gpio_fnd_on_0(void);

#endif /* INC_USER_GPIO_H_ */
