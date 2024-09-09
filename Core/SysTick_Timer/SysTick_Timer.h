/*
 * SysTick_Timer.h
 *
 *  Created on: Sep 5, 2024
 *      Author: PC_6285_Yİ
 */

#ifndef SYSTICK_TIMER_SYSTICK_TIMER_H_
#define SYSTICK_TIMER_SYSTICK_TIMER_H_

#include "stdint.h"
 uint32_t SystickGetMs();


uint8_t SystickCheckMs(uint32_t reference,uint32_t time_passed);

#endif /* SYSTICK_TIMER_SYSTICK_TIMER_H_ */
