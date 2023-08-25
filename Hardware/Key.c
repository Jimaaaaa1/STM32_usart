#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "usart.h"
#include "Key.h"

uint8_t Key_GetNum(void)
{
	uint8_t KeyNum = 0;
	if (KEY0 == 0)
	{
		Delay_ms(20);
		while (KEY0 == 0);
		Delay_ms(20);
		KeyNum = 1;
	}
	else if (KEY1 == 0)
	{
		Delay_ms(20);
		while (KEY1 == 0);
		Delay_ms(20);
		KeyNum = 2;
	}
	else
	{
		KeyNum = 0;
	}
	return KeyNum;
}
