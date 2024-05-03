#include "driver_led.h"

#define TRUE                1
#define FALSE               0

#define INVALID_LED_NUM     0xFF

typedef struct
{
    uint8_t led_identifier;
    uint16_t led_gpio_pin;
    GPIO_TypeDef *led_port;
}led_t;

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