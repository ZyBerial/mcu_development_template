//
// Created by YuZheng on 2024/5/4.
//
#ifndef __HAL_CONFIG_H
#define __HAL_CONFIG_H

#include "stm32f1xx_hal.h"

/*********************************LED***************************************/
#define LED_ENABLE              1

#if     LED_ENABLE
//LED_NUM
#define LED_DEV_NUM             1
//LED_GPIO
#ifndef LED_Pin
#define LED_Pin                 GPIO_PIN_13
#define LED_GPIO_Port           GPIOC
#endif
//LED_RCC
#define LED_GPIO_RCC_ENABLE()   do { \
                                __HAL_RCC_GPIOD_CLK_ENABLE();   \
                                __HAL_RCC_GPIOC_CLK_ENABLE();   \
                                } while(0u)
#endif
/*********************************LED***************************************/

/*********************************IIC***************************************/
#define IIC                     1
//使能 IIC 1
#define IIC1_ENABLE             1

#ifdef IIC

//IIC1 config
#if     IIC1_ENABLE

#ifndef SCL1_Pin
#define SCL1_Pin                GPIO_PIN_6
#define SCL1_GPIO_Port          GPIOB
#endif

#ifndef SDA1_Pin
#define SDA1_Pin                GPIO_PIN_7
#define SDA1_GPIO_Port          GPIOB
#endif

#endif

#endif
/*********************************IIC***************************************/

#endif