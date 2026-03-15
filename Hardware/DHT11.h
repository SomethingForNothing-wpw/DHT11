#ifndef __DHT11_H
#define __DHT11_H
#include "stm32f1xx.h"

// 全局数据: 以字节为单位存放 DHT11 返回的 4 字节数据
extern uint8_t rec_data[4];
extern uint8_t dht11_error_flag;


void DHT_GPIO_INPUT(void);
void DHT_GPIO_OUTPUT(void);
void DHT11_Start(void);
uint8_t DHT11rec_Byte(void);
void DHT11_RECdata(void);


#endif
