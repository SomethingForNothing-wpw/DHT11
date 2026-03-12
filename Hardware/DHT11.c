#include "DHT11.h"
#include "Delay.h"
// 数据（4 字节：湿度高、湿度低、温度高、温度低）
uint8_t rec_data[4];
uint8_t dht11_error_flag = 0; // 错误标志，volatile 防止优化
//输入模式
void DHT_GPIO_INPUT()
{
  GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
}
//输出模式
void DHT_GPIO_OUTPUT()
{
  GPIO_InitTypeDef GPIO_InitStruct;
  __HAL_RCC_GPIOB_CLK_ENABLE();
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(GPIOB,&GPIO_InitStruct);
}
//主机发送信号
void DHT11_Start()
{
  DHT_GPIO_OUTPUT();
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15, GPIO_PIN_SET);
  Delay_us(30);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15, GPIO_PIN_RESET);
  Delay_ms(20);
  HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15, GPIO_PIN_SET);
  Delay_us(30);
  DHT_GPIO_INPUT();
}
//获取一个字节（带超时保护）
uint8_t DHT11rec_Byte()
{
  unsigned int i = 0;
  uint8_t data = 0;
  unsigned int timeout;
  
  for(i=0;i<8;i++)
  {
    // 等待位开始（高电平）
    timeout = 0;
    while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_RESET)
    {
      Delay_us(1);
      if(++timeout > 100) return 0; // 超时返回 0
    }
    // 高电平维持时间决定是 0 还是 1，延时后读取
    Delay_us(30);
    data <<= 1;
    if(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_SET)
    {
      data |= 1;
    }
    // 等待本位结束（回到低电平）
    timeout = 0;
    while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_SET)
    {
      Delay_us(1);
      if(++timeout > 100) break;
    }
  }
  return data;
}
//获取数据
void DHT11_RECdata()
{
    uint8_t R_H, R_L, T_H, T_L, CHECK;
    unsigned int timeout = 0;
    DHT11_Start();

    // 等待传感器响应：先等待低电平（约 80us）
    timeout = 0;
    while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_RESET)
    {
      Delay_us(1);
      if(++timeout > 500) // 超时约 500us
      {
        dht11_error_flag = 0;
        rec_data[0]=rec_data[1]=rec_data[2]=rec_data[3]=0;
        return;
      }
    }
    // 等待传感器拉高（约 80us）
    timeout = 0;
    while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_SET)
    {
      Delay_us(1);
      if(++timeout > 500)
      {
        dht11_error_flag = 0;
        rec_data[0]=rec_data[1]=rec_data[2]=rec_data[3]=0;
        return;
      }
    }
    // 等待传感器回到低电平（数据开始）
    timeout = 0;
    while(HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_15) == GPIO_PIN_RESET)
    {
      Delay_us(1);
      if(++timeout > 500)
      {
        dht11_error_flag = 0;
        rec_data[0]=rec_data[1]=rec_data[2]=rec_data[3]=0;
        return;
      }
    }

    R_H = DHT11rec_Byte();
    R_L = DHT11rec_Byte();
    T_H = DHT11rec_Byte();
    T_L = DHT11rec_Byte();
    CHECK = DHT11rec_Byte();

    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15, GPIO_PIN_RESET);
    Delay_us(55);
    HAL_GPIO_WritePin(GPIOB,GPIO_PIN_15, GPIO_PIN_SET);

    // 验证校验码
    if((uint8_t)(R_H + R_L + T_H + T_L) == CHECK)
    {
      rec_data[0] = R_H;
      rec_data[1] = R_L;
      rec_data[2] = T_H;
      rec_data[3] = T_L;
      dht11_error_flag = 1; // 采集成功
    }
    else
    {
      // 校验失败但存储数据用于调试
      rec_data[0] = 0;
      rec_data[1] = 0;
      rec_data[2] = 0;
      rec_data[3] = 0;
      dht11_error_flag = 0; // 采集失败
    }
}
