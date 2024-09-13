/*
 * user-gpio.c
 *
 *  Created on: Aug 1, 2023
 *      Author: Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 */

#include "user-gpio.h"


void user_gpio_led_off_all(void)
{
	/* GPIO pins : PB5(GPIO_PIN_5), PB8(GPIO_PIN_8), PB9(GPIO_PIN_9) */
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_1Y, USER_GPIO_LED_OFF);		//Yellow, Off
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_2R, USER_GPIO_LED_OFF);		//Red, Off
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_3B, USER_GPIO_LED_OFF); 		//Blue, Off
}

void user_gpio_led_on_all(void)
{
	/* GPIO pins : PB5(GPIO_PIN_5), PB8(GPIO_PIN_8), PB9(GPIO_PIN_9) */
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_1Y, USER_GPIO_LED_ON);		//Yellow, On
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_2R, USER_GPIO_LED_ON);		//Red, On
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_3B, USER_GPIO_LED_ON); 		//Blue, On
}

void user_gpio_led_on_yellow(void)
{
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_1Y, USER_GPIO_LED_ON);
}

void user_gpio_led_off_yellow(void)
{
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_1Y, USER_GPIO_LED_OFF);
}

void user_gpio_led_on_red(void)
{
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_2R, USER_GPIO_LED_ON);
}

void user_gpio_led_off_red(void)
{
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_2R, USER_GPIO_LED_OFF);
}

void user_gpio_led_on_blue(void)
{
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_3B, USER_GPIO_LED_ON);
}

void user_gpio_led_off_blue(void)
{
	HAL_GPIO_WritePin(GPIOB, USER_GPIO_PIN_LED_3B, USER_GPIO_LED_OFF);
}

void user_gpio_led_toggle_delay(uint32_t ms)
{
	user_gpio_led_on_yellow();
	HAL_Delay(ms);
	user_gpio_led_off_yellow();

	user_gpio_led_on_red();
	HAL_Delay(ms);
	user_gpio_led_off_red();

	HAL_GPIO_TogglePin(GPIOB, USER_GPIO_PIN_LED_3B);	//Blue
}

void user_gpio_fnd_off_all(void)
{
	//FND Anode
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, USER_GPIO_LED_OFF);		//FND_A_DP
}

void user_gpio_fnd_clear(void)
{
	//FND Anode
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, USER_GPIO_LED_ON);

	/* GPIO pins : PC0 ~ PC8 */
	//GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
	//GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_ALL, USER_GPIO_LED_OFF);
}

void user_gpio_fnd_on_all(void)
{
	//FND Anode
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, USER_GPIO_LED_ON);

	//GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
	//GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_ALL, USER_GPIO_LED_ON);
}

void user_gpio_fnd_test(void)
{
	user_gpio_fnd_off_all();
	HAL_Delay(1000);
	user_gpio_fnd_on_all();
	HAL_Delay(1000);
	user_gpio_fnd_clear();

	//FND Anode
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, USER_GPIO_LED_ON);

	//GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
	//GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7
	uint32_t pin = 1;
	for (uint32_t i = 0; i < 8; i++ ) {
		pin = 1 << i;
		HAL_GPIO_WritePin(GPIOC, pin, USER_GPIO_LED_ON);
		HAL_Delay(1000);
	}

	user_gpio_fnd_on_1();
	HAL_Delay(1000);
	user_gpio_fnd_on_2();
	HAL_Delay(1000);
	user_gpio_fnd_on_3();
	HAL_Delay(1000);
	user_gpio_fnd_on_4();
	HAL_Delay(1000);
	user_gpio_fnd_on_5();
	HAL_Delay(1000);
	user_gpio_fnd_on_6();
	HAL_Delay(1000);
	user_gpio_fnd_on_7();
	HAL_Delay(1000);
	user_gpio_fnd_on_8();
	HAL_Delay(1000);
	user_gpio_fnd_on_9();
	HAL_Delay(1000);
	user_gpio_fnd_on_0();
}

void user_gpio_fnd_digit(int digit)
{
	uint16_t fnd_digit[] = { USER_GPIO_PIN_FND_0, USER_GPIO_PIN_FND_1, USER_GPIO_PIN_FND_2, USER_GPIO_PIN_FND_3
			, USER_GPIO_PIN_FND_4, USER_GPIO_PIN_FND_5, USER_GPIO_PIN_FND_6, USER_GPIO_PIN_FND_7
			, USER_GPIO_PIN_FND_8, USER_GPIO_PIN_FND_9, USER_GPIO_PIN_FND_ALL };

	user_gpio_fnd_clear();
	HAL_GPIO_WritePin(GPIOC, fnd_digit[digit], USER_GPIO_LED_ON);
}

void user_gpio_fnd_on_1(void)
{
	user_gpio_fnd_clear();
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_1, USER_GPIO_LED_ON);
}

void user_gpio_fnd_on_2(void)
{
	user_gpio_fnd_clear();
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_2, USER_GPIO_LED_ON);
}

void user_gpio_fnd_on_3(void)
{
	user_gpio_fnd_clear();
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_3, USER_GPIO_LED_ON);
}

void user_gpio_fnd_on_4(void)
{
	user_gpio_fnd_clear();
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_4, USER_GPIO_LED_ON);
}

void user_gpio_fnd_on_5(void)
{
	user_gpio_fnd_clear();
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_5, USER_GPIO_LED_ON);
}

void user_gpio_fnd_on_6(void)
{
	user_gpio_fnd_clear();
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_6, USER_GPIO_LED_ON);
}

void user_gpio_fnd_on_7(void)
{
	user_gpio_fnd_clear();
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_7, USER_GPIO_LED_ON);
}

void user_gpio_fnd_on_8(void)
{
	user_gpio_fnd_clear();
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_8, USER_GPIO_LED_ON);
}

void user_gpio_fnd_on_9(void)
{
	user_gpio_fnd_clear();
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_9, USER_GPIO_LED_ON);
}

void user_gpio_fnd_on_0(void)
{
	user_gpio_fnd_clear();
	HAL_GPIO_WritePin(GPIOC, USER_GPIO_PIN_FND_0, USER_GPIO_LED_ON);
}
