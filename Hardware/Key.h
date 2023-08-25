#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x_conf.h"

//#define KEY0_GPIO_PIN 				GPIO_Pin_3
//#define KEY0_GPIO_PORT 				GPIOB
//#define KEY0_GPIO_CLK 				RCC_APB2Periph_GPIOB

//#define KEY1_GPIO_PIN 				GPIO_Pin_5
//#define KEY1_GPIO_PORT 				GPIOB
//#define KEY1_GPIO_CLK 				RCC_APB2Periph_GPIOB

#define KEY0 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_3)
#define KEY1 GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)

uint8_t Key_GetNum(void);

#endif
