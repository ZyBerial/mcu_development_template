#include "driver_led.h"
#include "hal_config.h"

#define TRUE                1
#define FALSE               0

#define INVALID_LED_NUM     0xFF

typedef struct
{
    uint8_t led_identifier;
    uint16_t led_gpio_pin;
    GPIO_TypeDef *led_port;
} led_t;

//成员需要将相同GPIO_Port的LED设备写在一起。
static led_t led_device[LED_DEV_NUM] =
{
    {0, LED_Pin, LED_GPIO_Port}
};

static uint8_t retrieve_led_dev(uint8_t led_idf)
{
    uint8_t i;

    for (i=0; i<LED_DEV_NUM; i++)
    {
        if (led_idf == led_device[i].led_identifier)
        {
            return i;
        }
    }

    return INVALID_LED_NUM;
}

void led_reinit(void)
{
    uint8_t i, j;
    GPIO_TypeDef *init_group_idf = NULL;
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    uint32_t pin = 0;

    LED_GPIO_RCC_ENABLE();

    for (i=0; i<LED_DEV_NUM; i++)
    {
        init_group_idf = led_device[i].led_port;
        pin = led_device[i].led_gpio_pin;

        for (j=i+1; j<LED_DEV_NUM; j++)
        {
            if (init_group_idf != led_device[j].led_port)
            {
                i = j-1;
                break;
            }
            pin |= led_device[j].led_gpio_pin;
        }

        GPIO_InitStruct.Pin = pin;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
        GPIO_InitStruct.Pull = GPIO_PULLUP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
        HAL_GPIO_Init(init_group_idf, &GPIO_InitStruct);
        pin = 0;
    }
}

uint8_t led_on(uint8_t led_idf)
{
    uint8_t led_dev;

    led_dev = retrieve_led_dev(led_idf);
    if (INVALID_LED_NUM == led_dev)
    {
        return FALSE;
    }

    HAL_GPIO_WritePin(led_device[led_dev].led_port, led_device[led_dev].led_gpio_pin, GPIO_PIN_RESET);
    return TRUE;
}

uint8_t led_off(uint8_t led_idf)
{
    uint8_t led_dev;

    led_dev = retrieve_led_dev(led_idf);
    if (INVALID_LED_NUM == led_dev)
    {
        return FALSE;
    }

    HAL_GPIO_WritePin(led_device[led_dev].led_port, led_device[led_dev].led_gpio_pin, GPIO_PIN_SET);
    return TRUE;
}