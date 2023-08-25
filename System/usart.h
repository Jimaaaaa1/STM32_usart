#ifndef USART_H
#define USART_H

#include "stm32f10x_conf.h"
#include <stdio.h>

#define BOUND 115200
#define DEFAULT_USART USART1

void Serial_SendByte(USART_TypeDef* pUSARTx, uint8_t Byte);
void Serial_SendHalfWord(USART_TypeDef* pUSARTx, uint16_t Data);
void Serial_SendArray(USART_TypeDef* pUSARTx, uint8_t *Array, uint16_t Length);
void Serial_SendString(USART_TypeDef* pUSARTx, char *String);
int fputc(int ch, FILE *f);
void Serial_Printf(USART_TypeDef* pUSARTx, char *format, ...);
#endif

