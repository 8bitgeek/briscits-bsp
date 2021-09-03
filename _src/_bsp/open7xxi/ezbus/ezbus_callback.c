#include <ezbus_callback.h>
#include <ezbus.h>
#include <ezbus_flip.h>
#include <ezbus_port.h>
#include <hw_pin.h>
#include <hw_gpio.h>

#if !defined(AFX_DEBUG_EZBUS_GPIO)
    #define AFX_DEBUG_EZBUS_GPIO
#endif

#if !defined(AFX_TIMING_TX_PORT) 
    #error "AFX_TIMING_TX_PORT not defined"
#endif

#if !defined(AFX_TIMING_TX_UART)
    #error "AFX_TIMING_TX_UART not defined"
#endif

#if !defined(AFX_TIMING_TX_PIN)
    #error "AFX_TIMING_TX_PIN not defined"
#endif

#if defined(EZBUS_USE_FLOW_CALLBACK)

extern void ezbus_callback_setup( ezbus_port_t* port )
{
    ezbus_port_init_struct( port );

    ezbus_platform_port_set_name(port,EZBUS_USART_NO);
    ezbus_platform_port_set_handle(port,NULL);
    ezbus_platform_port_set_dir_gpio(port,&gpio_rs485_dir,NULL);
}

extern bool ezbus_platform_set_tx( ezbus_platform_port_t* port, bool enable )
{
    if ( enable )
    {
        caribou_gpio_set( ezbus_platform_port_get_dir_gpio_tx(port) );
    }
    else
    {
        ezbus_platform_drain(port);
        caribou_gpio_reset( ezbus_platform_port_get_dir_gpio_tx(port) );
    }
    return enable;
}

#endif

extern bool ezbus_pause_callback( ezbus_mac_t* mac )
{
    // fprintf( stderr, " %d ", ezbus_mac_arbiter_get_state( mac ) );
    switch( ezbus_mac_pause_get_state( mac ) )
    {
        case ezbus_pause_state_start:

            // switch TXD pin to GPIO
            #if defined(AFX_DEBUG_EZBUS_GPIO)
                hw_gpio_set(gpio_led0);
            #endif
            hw_gpio_set( gpio_rs485_dir );
            hw_gpio_reset(gpio_rs485_tx);
            hw_pin_set_mode	( AFX_TIMING_TX_PORT, AFX_TIMING_TX_PIN, GPIO_Mode_OUT);
            hw_pin_set_afn	( AFX_TIMING_TX_PORT, AFX_TIMING_TX_PIN, GPIO_AF_GPIO); 
            #if defined(AFX_DEBUG_EZBUS_GPIO)
                for(volatile int x=0; x <100; x++);
                hw_gpio_reset(gpio_led0);
            #endif
            break;

        case ezbus_pause_state_half_duration_timeout:  

            // output GPIO a short low pulse for a few microseconds
            #if defined(AFX_DEBUG_EZBUS_GPIO)
                hw_gpio_set(gpio_led1);
            #endif
            hw_gpio_set( gpio_rs485_tx );
            for(volatile int x=0; x <15; x++);
            hw_gpio_reset( gpio_rs485_tx );
            #if defined(AFX_DEBUG_EZBUS_GPIO)
                hw_gpio_reset( gpio_led1 );
            #endif
            break;
        
        case ezbus_pause_state_duration_timeout:

            // switch from GPIO to TXD pin mode.
            #if defined(AFX_DEBUG_EZBUS_GPIO)
                hw_gpio_set(gpio_led0);
            #endif
            hw_pin_set_mode	( AFX_TIMING_TX_PORT, AFX_TIMING_TX_PIN, GPIO_Mode_AF);
            hw_pin_set_afn	( AFX_TIMING_TX_PORT, AFX_TIMING_TX_PIN, AFX_TIMING_TX_UART);
            hw_gpio_reset( gpio_rs485_dir );
            #if defined(AFX_DEBUG_EZBUS_GPIO)
                for(volatile int x=0; x <15; x++);
                hw_gpio_reset(gpio_led0);
            #endif
            break;
        
        case ezbus_pause_state_finish:

            // timer is finished, clean up
            break;

        default:
            break;
    }
    return true;
}
