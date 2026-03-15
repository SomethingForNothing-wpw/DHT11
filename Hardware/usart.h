#ifndef __USART_H
#define __USART_H

#include "stm32f1xx.h" // 或者是 "stm32f4xx.h"，根据你的芯片改
#include "stdio.h"     // 用于 printf

// 函数声明
void uart_init(uint32_t bound); // 初始化函数，参数是波特率
void MX_USART1_UART_Init(void);  // CubeMX 样式的初始化函数
void send_string(const char *str); // 发送字符串函数

#endif
