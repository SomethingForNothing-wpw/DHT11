#include "usart.h"

// 加入以下代码, 支持printf函数, 而不需要选择use MicroLIB
// 这是一个标准写法，几乎所有的 STM32 工程都会用到
#if 1
#pragma import(__use_no_semihosting)             
// 标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
}; 

FILE __stdout;       
// 定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
// 重定义 fputc 函数 
// 作用：当你在代码里调用 printf 时，内容会被这个函数截获，并通过串口发出去
int fputc(int ch, FILE *f)
{      
	while((USART1->SR & 0X40) == 0); // 等待上一次发送完毕 (SR寄存器的TC位)
	USART1->DR = (uint8_t) ch;            // 将字符写入数据寄存器，发送出去      
	return ch;
}
#endif 

UART_HandleTypeDef huart1;

// 串口1初始化函数
// bound: 波特率 (通常用 115200)
void uart_init(uint32_t bound)
{
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    GPIO_InitStruct.Pin = GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    huart1.Instance = USART1;
    huart1.Init.BaudRate = bound;
    huart1.Init.WordLength = UART_WORDLENGTH_8B;
    huart1.Init.StopBits = UART_STOPBITS_1;
    huart1.Init.Parity = UART_PARITY_NONE;
    huart1.Init.Mode = UART_MODE_TX_RX;
    huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart1.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&huart1);
}

// CubeMX 样式的初始化函数（包装 uart_init）
void MX_USART1_UART_Init(void)
{
    uart_init(115200);  // 默认波特率 115200
}
