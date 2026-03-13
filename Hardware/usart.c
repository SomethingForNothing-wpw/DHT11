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
	// 等待发送数据寄存器空 (TXE)，然后写入数据
	while((USART1->SR & USART_SR_TXE) == 0);
	USART1->DR = (uint8_t) ch;
	// 不等待 TC，因为对于连续字符，TXE 足够
	return ch;
}
#endif 

// 串口1初始化函数
// bound: 波特率 (通常用 9600)
void uart_init(uint32_t bound)
{
    // 开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN | RCC_APB2ENR_IOPAEN;

    // PA9 TX: 复用推挽 (MODE9=11, CNF9=10)
    GPIOA->CRH &= ~(GPIO_CRH_MODE9 | GPIO_CRH_CNF9);
    GPIOA->CRH |= (GPIO_CRH_MODE9_1 | GPIO_CRH_MODE9_0) | GPIO_CRH_CNF9_1;

    // PA10 RX: 浮空输入 (MODE10=00, CNF10=01)
    GPIOA->CRH &= ~(GPIO_CRH_MODE10 | GPIO_CRH_CNF10);
    GPIOA->CRH |= GPIO_CRH_CNF10_0;

    // 计算波特率 (假设 PCLK2 = 8MHz, oversampling16)
    // 公式来自 STM32 参考手册：
    //   USARTDIV = PCLK2 / (16 * baud)
    //   BRR = mantissa[15:4] + fraction[3:0]
    // 这里用整数计算并进行四舍五入
    {
        const uint32_t pclk = 8000000U;
        uint32_t tmp = (pclk * 25U) / (4U * bound); // = USARTDIV * 100
        uint32_t mantissa = tmp / 100U;
        uint32_t fraction = ((tmp - mantissa * 100U) * 16U + 50U) / 100U;
        if (fraction >= 16U) fraction = 15U;
        USART1->BRR = (mantissa << 4) | (fraction & 0xF);
    }

    // 8N1, 16 oversampling
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE;
    USART1->CR2 = 0;
    USART1->CR3 = 0;

    // 使能USART
    USART1->CR1 |= USART_CR1_UE;
}

// CubeMX 样式的初始化函数（包装 uart_init）
void MX_USART1_UART_Init(void)
{
    uart_init(115200);  // HC-05默认波特率115200
}

// 发送字符串函数（直接发送，不用 printf）
void send_string(const char *str)
{
    while (*str)
    {
        while ((USART1->SR & USART_SR_TXE) == 0);
        USART1->DR = (uint8_t)*str++;
        // 不等待 TC，连续发送以减少延迟
    }
}
