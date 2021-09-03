#include <ezbus_app_setup.h>
#include <ezbus_port.h>


extern bool ezbus_app_setup( ezbus_app_state_t* ezbus_app_state, uint32_t speed )
{
    memset( ezbus_app_state, 0, sizeof(ezbus_app_state_t) );
    // ezbus_callback_setup( &ezbus_app_state->port );
    if ( ezbus_port_open( &ezbus_app_state->port ) == EZBUS_ERR_OKAY )
    {
        ezbus_init( &ezbus_app_state->ezbus, &ezbus_app_state->port );
        ezbus_app_state->mac = ezbus_mac( &ezbus_app_state->ezbus );
        return true;
    }
    return false;
}

