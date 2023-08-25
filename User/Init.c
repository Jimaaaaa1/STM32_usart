#include "usart.h"
#include "Delay.h"
#include "LED.h"
#include "Key.h"
#include "Init.h"
#include <stdio.h>
#include <stdarg.h>

void Serial_Init()
{
	GPIO_InitTypeDef GPIOA_struct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	//GPIO: A9 A10
	//A9 AF PP
	GPIOA_struct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIOA_struct.GPIO_Pin = GPIO_Pin_9;
	GPIOA_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIOA_struct );
	//A10 FLOATING
	GPIOA_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIOA_struct.GPIO_Pin = GPIO_Pin_10;
	GPIOA_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init( GPIOA, &GPIOA_struct );
}

void sys_LED_Init()
{
	GPIO_InitTypeDef GPIOB_struct;	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	//LED
	GPIOB_struct.GPIO_Pin =  GPIO_Pin_8; 
	GPIOB_struct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIOB_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOB_struct);
}

void sys_USART_Init()
{
	USART_InitTypeDef US;
	NVIC_InitTypeDef NV;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE );
	
	USART_DeInit( USART1 );
	
	//NVIC
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 ); //group of NVIC
	NV.NVIC_IRQChannel = USART1_IRQn;
	NV.NVIC_IRQChannelPreemptionPriority = 0;
	NV.NVIC_IRQChannelSubPriority = 0;
	NV.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NV );
	
	//USART: no pareity/ stopbit 1/ word 8
	US.USART_BaudRate = BOUND;
	US.USART_Parity = USART_Parity_No;
	US.USART_StopBits = USART_StopBits_1;
	US.USART_WordLength = USART_WordLength_8b;
	US.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	US.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init( USART1, &US );
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); // NVIC of receive USART
	USART_Cmd( USART1, ENABLE );
	
}

void EXIT_Key_Init()
{
	GPIO_InitTypeDef GPIOB_struct;	
	EXTI_InitTypeDef EXTI_struct;
	NVIC_InitTypeDef NVIC_struct;
	
//	//GPIO
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	GPIOB_struct.GPIO_Mode = GPIO_Mode_IPU;
	GPIOB_struct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;
	GPIOB_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIOB_struct);
	
	//EXTI
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE );	
	
	EXTI_struct.EXTI_Line = EXTI_Line3|EXTI_Line5;
	EXTI_struct.EXTI_LineCmd = ENABLE;
	EXTI_struct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_struct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_StructInit(&EXTI_struct);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
	
	//Priority
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_2 ); //group of NVIC
	NVIC_struct.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_struct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_struct.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init( &NVIC_struct );
	
	NVIC_struct.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_struct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_struct.NVIC_IRQChannelSubPriority = 2;
	NVIC_struct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_struct );
}


void Init(){
	
	Serial_Init();
	sys_LED_Init();
	sys_USART_Init();
	//EXIT_Key_Init();

}

