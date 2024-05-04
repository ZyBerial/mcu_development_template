#ifndef __DRIVER_IIC_H
#define __DRIVER_IIC_H

#include "stm32f1xx_hal.h"

extern void iic_gpio_reinit(void);
extern void iic_start(void);
extern void iic_stop(void);
extern uint8_t iic_wait_ack(void);
extern void iic_ack(void);
extern void iic_nack(void);
extern void iic_write_byte(uint8_t data);
extern uint8_t iic_read_byte(uint8_t ack);

#endif