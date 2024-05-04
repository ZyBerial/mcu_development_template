#include "driver_iic.h"
#include "hal_config.h"

#define SDA_L()         HAL_GPIO_WritePin(SDA1_GPIO_Port, SDA1_Pin, GPIO_PIN_RESET)
#define SDA_H()         HAL_GPIO_WritePin(SDA1_GPIO_Port, SDA1_Pin, GPIO_PIN_SET)
#define SCL_L()         HAL_GPIO_WritePin(SCL1_GPIO_Port, SCL1_Pin, GPIO_PIN_RESET)
#define SCL_H()         HAL_GPIO_WritePin(SCL1_GPIO_Port, SCL1_Pin, GPIO_PIN_SET)

#define IIC_SDA_IN()    HAL_GPIO_ReadPin(SDA1_GPIO_Port, SDA1_Pin)

static void iic_delay_us(uint32_t nus)
{
    uint32_t Delay = nus * 168/4;
    do
    {
        __NOP();
    }
    while (Delay --);
}

static void I2C_Delay(uint32_t t)
{
    volatile uint32_t tmp = t;
    while(tmp--);
}

void iic_gpio_reinit(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    HAL_GPIO_DeInit(SCL1_GPIO_Port, SCL1_Pin);
    HAL_GPIO_DeInit(SDA1_GPIO_Port, SDA1_Pin);

    GPIO_InitStruct.Pin = SCL1_Pin|SDA1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    HAL_GPIO_WritePin(GPIOB, SCL1_Pin|SDA1_Pin, GPIO_PIN_SET);
}

void iic_start(void)
{
    SDA_H();
    SCL_H();
    I2C_Delay(100);
    SDA_L();
    I2C_Delay(100);
    SCL_L();
}

void iic_stop(void)
{
    SDA_L();
    SCL_H();
    I2C_Delay(100);
    SDA_H();
    I2C_Delay(100);
}

uint8_t iic_wait_ack(void)
{
    uint8_t ucErrTime = 0;

    SCL_L();
    SDA_H();
    I2C_Delay(100);

    SCL_H();
    while(IIC_SDA_IN())
    {
        if (++ucErrTime >= 100)
        {
            SCL_L();
            return 0;
        }
        I2C_Delay(10);
    }

    SCL_L();
    return 1;
}

void iic_ack(void)
{
    SCL_L();
    SDA_L();
    I2C_Delay(100);
    SCL_H();
    I2C_Delay(100);
}

void iic_nack(void)
{
    SCL_L();
    SDA_H();
    I2C_Delay(100);
    SCL_H();
    I2C_Delay(100);
}

void iic_write_byte(uint8_t data)
{
    uint8_t i;

    for (i=0; i<8; i++)
    {
        SCL_L();
        I2C_Delay(100);
        if ((data<<i) & 0x80)
        {
            SDA_H();
        }
        else
        {
            SDA_L();
        }
        SDA_H();
        I2C_Delay(100);
    }

    if (!iic_wait_ack())
    {
        iic_stop();
    }
}

uint8_t iic_read_byte(uint8_t ack)
{
    uint8_t data = 0;
    uint8_t i = 0;

    SDA_H();

    for (i=0; i<8; i++)
    {
        SCL_L();
        I2C_Delay(100);
        SCL_H();
        I2C_Delay(100);
        data |= (IIC_SDA_IN()) ? (1<<i) : (0);
    }

    (!ack) ? (iic_ack()) : (iic_nack());
    
    return data;
}