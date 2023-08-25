#include "stm32f10x_conf.h"
#include "usart.h"
#include "Init.h"
#include "stdio.h"
#include "Delay.h"
#include "Key.h"
#include "LED.h"
#include "TIME.h"
#include <stdlib.h>
typedef unsigned long long u64;

char cmd = 0;
uint8_t KeyNum;

void KEY_EXTI_Config(void)
{
		GPIO_InitTypeDef GPIOB_struct;	
    EXTI_InitTypeDef EXTI_InitStruct;
    NVIC_InitTypeDef NVIC_InitStruct;
		

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE); 
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
		GPIOB_struct.GPIO_Mode = GPIO_Mode_IPU;
		GPIOB_struct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_5;
		GPIOB_struct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIOB_struct);
 
    EXTI_InitStruct.EXTI_Line       =   EXTI_Line1;    
    EXTI_InitStruct.EXTI_LineCmd    =   ENABLE;        
    EXTI_InitStruct.EXTI_Mode       =   EXTI_Mode_Interrupt;    
    EXTI_InitStruct.EXTI_Trigger    =   EXTI_Trigger_Falling;   
    EXTI_Init(&EXTI_InitStruct);  
	
    EXTI_InitStruct.EXTI_Line       =   EXTI_Line5;    
    EXTI_InitStruct.EXTI_LineCmd    =   ENABLE;        
    EXTI_InitStruct.EXTI_Mode       =   EXTI_Mode_Interrupt;    
    EXTI_InitStruct.EXTI_Trigger    =   EXTI_Trigger_Falling;   
    EXTI_Init(&EXTI_InitStruct); 	
 
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);  
	
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource5);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   
    
    NVIC_InitStruct.NVIC_IRQChannel     =   EXTI1_IRQn;         
    NVIC_InitStruct.NVIC_IRQChannelCmd  =   ENABLE;             
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority   =   1; 
    NVIC_InitStruct.NVIC_IRQChannelSubPriority          =   0;
    NVIC_Init(&NVIC_InitStruct);        

		NVIC_InitStruct.NVIC_IRQChannel     =   EXTI9_5_IRQn;         
    NVIC_InitStruct.NVIC_IRQChannelCmd  =   ENABLE;             
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority   =   1; 
    NVIC_InitStruct.NVIC_IRQChannelSubPriority          =   0;
    NVIC_Init(&NVIC_InitStruct); 
}


void EXTI1_IRQHandler(void)
{	
	
	if (EXTI_GetITStatus(EXTI_Line1) != RESET)
	{
		Serial_SendString(USART1, "$START@");
	}	
	for(int i=0;i<1000000;i++){}
	EXTI_ClearITPendingBit(EXTI_Line1);
	while(EXTI_GetITStatus(EXTI_Line1) != RESET);
}

void EXTI9_5_IRQHandler(void)
{	
	if (EXTI_GetITStatus(EXTI_Line5) != RESET)
	{
		Serial_SendString(USART1, "$STOP@");
	}	
	for(int i=0;i<1000000;i++){}
	EXTI_ClearITPendingBit(EXTI_Line5);
	while(EXTI_GetITStatus(EXTI_Line5) != RESET);
}


int main()
{
	Init();	
	KEY_EXTI_Config();
	TIM2_Getsample_Int(4999,719);		//500ms
	while(1)
	{
	}
}

