/*
 * user-tasks.h
 *
 *  Created on: Aug 29, 2023
 *      Author: Jung-JaeJoon <rgbi3307@naver.com> on the www.kernel.bz
 */

#ifndef INC_USER_TASKS_H_
#define INC_USER_TASKS_H_

#include "cmsis_os.h"
#include "user-uart.h"
#include "user-gpio.h"

void tick_output(char *name);

void task01_thread_create(void);
void task02_thread_create(void);
void task03_thread_create(void);
void task04_thread_create(void);
void task05_thread_create(void);
void task06_thread_create(void);
void task07_thread_create(void);
void task08_thread_create(void);

#endif /* INC_USER_TASKS_H_ */
