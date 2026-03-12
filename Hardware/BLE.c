#include "BLE.h"
#include "stm32f1xx.h"
#include "DHT11.h"
 
/*
*** USART1  配置串口1与HC-05通信 ***
 
*** 波特率：115200，8位数据位，1位停止位，无奇偶校验位 ***
 
*** 接口：PA9->TX   PA10->RX ***
 
*** 作者：陈加油嗯 ***
 
***关注微信公众号学习更多单片机知识：微信搜索"陈加油嗯" ***
 
*/
void USART1_Init()
{
	GPIO_InitTypeDef GPIO_Initstructure;
	NVIC_InitTypeDef NVIC_InitStruct;
	USART_InitTypeDef USART1_InitStructure;
 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
 
	// USART1_TX     PA9
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Initstructure);
 
	// USART1_RX     PA10
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Initstructure);
 
	USART1_InitStructure.USART_BaudRate = 115200;
	USART1_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //无硬件数据流控制
	USART1_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;                 //收发模式
	USART1_InitStructure.USART_Parity = USART_Parity_No;                             //无奇偶校验位
	USART1_InitStructure.USART_StopBits = USART_StopBits_1;                          //一个停止位
	USART1_InitStructure.USART_WordLength = USART_WordLength_8b;                     //字长为8位数据格式
	USART_Init(USART1, &USART1_InitStructure);
	USART_Cmd(USART1, ENABLE); //使能USART1
 
	NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
 
	NVIC_Init(&NVIC_InitStruct);
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
 
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
}
 
void USART1_IRQHandler(void)
{
	if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET)
	{
		// 可以在这里添加接收数据的处理代码
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
	}
}
