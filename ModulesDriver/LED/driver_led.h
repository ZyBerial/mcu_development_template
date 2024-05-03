#ifndef __DRIVER_LED_H
#define __DRIVER_LED_H

#include "main.h"

#define LED_DEV_NUM     1

#ifndef LED_Pin
#define LED_Pin GPIO_PIN_13
#define LED_GPIO_Port GPIOC
#endif

extern uint8_t led_on(uint8_t led_idf);
extern uint8_t led_off(uint8_t led_idf);

#endif
