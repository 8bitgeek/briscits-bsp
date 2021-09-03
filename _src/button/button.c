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
#include <button.h>
#include <hw_gpio.h>

#define DOUBLE_CLICK_TIME   500
#define HOLD_PRESS_TIME     4000

static void button_emit(button_t* button,button_event_t button_event);

extern void button_setup(button_t* button, hw_gpio_t* gpio, bool inverted, button_callback_t callback)
{
    memset(button,0,sizeof(button_t));
    button->gpio = gpio;
    button->inverted = inverted;
    button->callback = callback;
}

extern void button_service(button_t* button)
{
    switch(button->state)
    {
        case button_idle:
            if ( button_pressed(button) )
            {
                if ( briscits_timer_ticks() - button->down_start < DOUBLE_CLICK_TIME )
                {
                    button_emit(button,button_double_click);
                    button->down_start = briscits_timer_ticks();
                }
                button->state = button_press;
            }
            break;
        case button_press:
            button->down_start = briscits_timer_ticks();
            button_emit(button,button_down);
            button->state = button_press_wait;
            break;
        case button_press_wait:
            if ( !button_pressed(button) )
               button->state = button_release;
            if ( briscits_timer_ticks() - button->down_start > HOLD_PRESS_TIME )
            {
                button_emit(button,button_held);
                button->down_start = briscits_timer_ticks();
            }
            break;
        case button_release:
            button->up_start = briscits_timer_ticks();
            button_emit(button,button_up);
            button->state = button_idle;
            break;
    }
}

extern bool button_pressed(button_t* button)
{
    return button->inverted ? !hw_gpio_state(button->gpio) : hw_gpio_state(button->gpio);
}

static void button_emit(button_t* button,button_event_t button_event)
{
    if ( button->callback != NULL )
    {
        button->callback(button_event);
    }
}
