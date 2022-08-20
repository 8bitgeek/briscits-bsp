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
#ifndef BRISC_LED_H_
#define BRISC_LED_H_

#include <board.h>
#include <hw_gpio.h>
#include <jiffies.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define LED_BLINK_FOREVER   0xFF

typedef struct _led_t_
{
    hw_gpio_t*      gpio;
    bool            inverted;
    uint8_t         blink_count;
    uint16_t        blink_rate; 
    #if defined(__BARE_METAL__)
        uint32_t        blink_start;
    #else
        jiffies_t  blink_start;
    #endif
} led_t;


extern void led_setup   (led_t* led, hw_gpio_t* gpio, bool inverted);
extern void led_service (led_t* led);
extern void led_on      (led_t* led);
extern void led_off     (led_t* led);
extern void led_toggle  (led_t* led);
extern bool led_state   (led_t* led);
extern void led_set     (led_t* led, bool on);
extern void led_reset   (led_t* led);

/****************************************************************************
 * @brief Blink the led for a pre determined period and rate.
 * @param led An initialized led structure see: @ref led_setup
 * @param count Number of cycles to blink, or LED_BLINK_FOREVER 
 * @param rate Blink frequency in milliseconds
****************************************************************************/
extern void led_blink   (led_t* led, uint8_t count, uint16_t rate);

#ifdef __cplusplus
}
#endif

#endif
