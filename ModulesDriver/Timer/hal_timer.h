#ifndef __HAL_TIMER_H
#define __HAL_TIMER_H

#include "stm32f1xx_hal.h"

typedef struct
{
    uint32_t tickstart;
    uint32_t tickcurrent;
    uint32_t wait;
}timer_t;

extern void timer_init(timer_t *timer, uint32_t time_out_ms);
extern uint8_t is_timer_expires(timer_t *timer);

#endif