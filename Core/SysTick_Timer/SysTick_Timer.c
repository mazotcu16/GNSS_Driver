/*
 * SysTick_Timer.c
 *
 *  Created on: Sep 5, 2024
 *      Author: PC_6285_Yİ
 */

#include "SysTick_Timer.h"
#include "stm32h7xx.h"

static uint32_t ms;

 uint32_t SystickGetMs()
 {
   return ms;
 }


 uint8_t SystickCheckMs(uint32_t reference,uint32_t time_passed)
 {
   if((ms-reference)>=time_passed)
	   return 1;
   else
	  return 0;
 }


 void SysTick_Handler(void)
 {
   /* USER CODE BEGIN SysTick_IRQn 0 */
    ms++;
   /* USER CODE END SysTick_IRQn 0 */


   /* USER CODE BEGIN SysTick_IRQn 1 */

   /* USER CODE END SysTick_IRQn 1 */
 }
