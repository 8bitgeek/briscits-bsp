#include <rgb_led.h>

extern void rgb_led_r(bool state)
{
    GPIO_WriteBit( GPIOA, GPIO_Pin_0, state );
}

extern void rgb_led_g(bool state)
{
    GPIO_WriteBit( GPIOA, GPIO_Pin_1, state );
}

extern void rgb_led_b(bool state)
{
    GPIO_WriteBit( GPIOA, GPIO_Pin_0, state );
}

