/******************************************************************************
 ________  ________  ___  ________  ________  ___  _________  ________      
|\   __  \|\   __  \|\  \|\   ____\|\   ____\|\  \|\___   ___\\   ____\     
\ \  \|\ /\ \  \|\  \ \  \ \  \___|\ \  \___|\ \  \|___ \  \_\ \  \___|_    
 \ \   __  \ \   _  _\ \  \ \_____  \ \  \    \ \  \   \ \  \ \ \_____  \   
  \ \  \|\  \ \  \\  \\ \  \|____|\  \ \  \____\ \  \   \ \  \ \|____|\  \  
   \ \_______\ \__\\ _\\ \__\____\_\  \ \_______\ \__\   \ \__\  ____\_\  \ 
    \|_______|\|__|\|__|\|__|\_________\|_______|\|__|    \|__| |\_________\
                            \|_________|                        \|_________|
                            
MIT License

Copyright (c) 2021 Mike Sharkey

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

******************************************************************************/
#include <led.h>

extern void led_setup(led_t* led, gpio_t* gpio, bool inverted)
{
    memset(led,0,sizeof(led_t));
    led->gpio = gpio;
    led->inverted = inverted;
}

extern void led_service(led_t* led)
{
    if ( led->blink_count > 0 )
    {
        if ( b_thread_systick() - led->blink_start > led->blink_rate )
        {
            led_toggle(led);
            if ( led->blink_count != LED_BLINK_FOREVER && !led_state(led) )
                --led->blink_count;
            led->blink_start = b_thread_systick();
        }
    }
}

extern void led_on(led_t* led)
{
    if ( led->inverted )
        b_gpio_reset(led->gpio);
    else
        b_gpio_set(led->gpio);
}

extern void led_off(led_t* led)
{
    if ( led->inverted )
        b_gpio_set(led->gpio);
    else
        b_gpio_reset(led->gpio);
}

extern void led_toggle(led_t* led)
{
    b_gpio_toggle(led->gpio);
}

extern bool led_state(led_t* led)
{
    if ( led->inverted )
        return !b_gpio_state(led->gpio);
    else
        return b_gpio_state(led->gpio);
}

extern void led_set(led_t* led, bool on)
{
    if ( led->inverted )
        b_gpio_write(led->gpio,!on);
    else
        b_gpio_write(led->gpio,on);
}

extern void led_reset(led_t* led)
{
    led->blink_count = 0;
    led->blink_rate = 0;
    led_off(led);
}

extern void led_blink(led_t* led, uint8_t count, uint16_t rate)
{
    if ( !led->blink_count )
    {
        led->blink_count = count;
        led->blink_rate = rate;
        led_on(led);
        led->blink_start = b_thread_systick();
    }
}
