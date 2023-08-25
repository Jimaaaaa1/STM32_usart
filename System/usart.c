#include "usart.h"
#include "Delay.h"
#include "LED.h"
#include <stdio.h>
#include <stdarg.h>

u8 RxBuffer[10]={0};              /* USART1 Using  */
u8 RxCnt = 0;
//u8 charNum=0;
//int exectime=0;
//u8 led[4] = {0};

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
    RxBuffer[RxCnt++] = USART_ReceiveData(USART1);
		if(RxCnt > 2)
		{
			extern char cmd;
			char flag;
			for(uint8_t i = 0; i<RxCnt; i++)
			{
				if(RxBuffer[i] == '$')  //head
				{
					flag = i;
				}
				if(RxBuffer[i] == '@') //tail
				{
					cmd = RxBuffer[flag + 6];
					if( cmd >='1' && cmd <='9')
						{
							TIM2->CR1 |= 0x01;
							TIM2->ARR=(cmd-'0')*10000;
						}
						else
						{
							TIM2->CR1 &= ~(0x01);
							LED_OFF();
						}
					RxCnt = 0;			
					break;
				}
			}
		}
  }
	USART_ClearITPendingBit(USART1, USART_IT_RXNE);
}

void Serial_SendByte(USART_TypeDef* pUSARTx, uint8_t Byte)
{
	USART_SendData(pUSARTx, Byte);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void Serial_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t Data)
{
	uint8_t temp_h,temp_l;
	temp_h = (Data&0xff00) >> 8;
	temp_l = (Data&0x00ff);
	
	USART_SendData(pUSARTx, temp_h);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	USART_SendData(pUSARTx, temp_l);
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(USART_TypeDef* pUSARTx, uint8_t *Array, uint16_t Length)
{
	uint16_t i;
	for (i = 0; i < Length; i ++)
	{
		Serial_SendByte(pUSARTx, Array[i]);
	}
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

void Serial_SendString(USART_TypeDef* pUSARTx, char *String)
{
	uint8_t i;
	for (i = 0; String[i] != '\0'; i ++)
	{
		Serial_SendByte(pUSARTx,String[i]);
	}
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

int fputc(int ch, FILE *f)
{
	Serial_SendByte(DEFAULT_USART,ch);
	while (USART_GetFlagStatus(DEFAULT_USART, USART_FLAG_TXE) == RESET);
	return ch;
}

void Serial_Printf(USART_TypeDef* pUSARTx, char *format, ...)
{
	char String[100];
	va_list arg;
	va_start(arg, format);
	vsprintf(String, format, arg);
	va_end(arg);
	Serial_SendString(pUSARTx, String);
}

