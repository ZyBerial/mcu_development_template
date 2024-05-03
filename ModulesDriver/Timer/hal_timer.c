//
// Created by YuZheng on 2024/5/3.
//

#include "hal_timer.h"

void timer_init(timer_t *timer, uint32_t time_out_ms)
{
    timer->tickstart = HAL_GetTick();
    timer->wait = time_out_ms;

    if (timer->wait < HAL_MAX_DELAY)
    {
        timer->wait += (uint32_t)(uwTickFreq);
    }
}

uint8_t is_timer_expires(timer_t *timer)
{
    timer->tickcurrent = HAL_GetTick();

    if (timer->tickcurrent - timer->tickstart < timer->wait)
    {
        return 0;
    }

    return 1;
}