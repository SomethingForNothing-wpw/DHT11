#include "stm32f1xx.h"

/*
 * Reworked delay routines.
 * The original implementation used SysTick directly, which reconfigured and
 * disabled the timer on each call.  That conflicts with the HAL tick
 * (uwTick) and caused HAL_Delay to hang.  Here we use the DWT cycle counter
 * for microsecond waits and defer to HAL_Delay for millisecond/longer waits.
 */

static void Delay_Init(void)
{
    /* enable DWT cycle counter if not already enabled */
    if (!(CoreDebug->DEMCR & CoreDebug_DEMCR_TRCENA_Msk))
    {
        CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    }
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

void Delay_us(uint32_t xus)
{
    static uint8_t init = 0;
    if (!init)
    {
        Delay_Init();
        init = 1;
    }

    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = xus * (SystemCoreClock / 1000000U);
    while ((DWT->CYCCNT - start) < ticks)
    {
        /* busy loop */
    }
}

void Delay_ms(uint32_t xms)
{
    /* use HAL_Delay which relies on the HAL tick maintained by SysTick */
    HAL_Delay(xms);
}

void Delay_s(uint32_t xs)
{
    while (xs--)
    {
        Delay_ms(1000);
    }
} 
