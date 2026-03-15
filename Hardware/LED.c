#include "stm32f103xb.h"
#include "stm32f1xx.h"                  // Device header
#include "stm32f1xx_hal_gpio.h"

/**
  * 函    数：LED初始化
  * 参    数：无
  * 返 回 值：无
  */
void LED_Init(void)
{
	/*开启时钟*/
	__HAL_RCC_GPIOA_CLK_ENABLE();		//开启GPIOA的时钟
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pin = GPIO_PIN_1 | GPIO_PIN_2;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);						//将PA1和PA2引脚初始化为推挽输出
	
	/*设置GPIO初始化后的默认电平*/
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);				//设置PA1引脚为高电平			//设置PA2引脚为高电平
}

/**
  * 函    数：LED1开启
  * 参    数：无
  * 返 回 值：无
  */
void LED1_ON(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);		//设置PA1引脚为低电平
}

/**
  * 函    数：LED1关闭
  * 参    数：无
  * 返 回 值：无
  */
void LED1_OFF(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);		//设置PA1引脚为高电平
}

/**
  * 函    数：LED1状态翻转
  * 参    数：无
  * 返 回 值：无
  */
void LED1_Turn(void)
{
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13) == GPIO_PIN_RESET)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);					//则设置PA1引脚为高电平
	}
	else													//否则，即当前引脚输出高电平
	{
		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);					//则设置PA1引脚为低电平
	}
}

/**
  * 函    数：LED2开启
  * 参    数：无
  * 返 回 值：无
  */
void LED2_ON(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);		//设置PA2引脚为低电平
}

/**
  * 函    数：LED2关闭
  * 参    数：无
  * 返 回 值：无
  */
void LED2_OFF(void)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);		//设置PA2引脚为高电平
}

/**
  * 函    数：LED2状态翻转
  * 参    数：无
  * 返 回 值：无
  */
void LED2_Turn(void)
{
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_2) == GPIO_PIN_RESET)		//获取输出寄存器的状态，如果当前引脚输出低电平
	{                                                  
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET);               		//则设置PA2引脚为高电平
	}                                                  
	else                                               		//否则，即当前引脚输出高电平
	{                                                  
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET);             		//则设置PA2引脚为低电平
	}
}
