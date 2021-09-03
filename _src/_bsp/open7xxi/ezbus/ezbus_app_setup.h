#ifndef _EZBUS_APP_SETUP_H_
#define _EZBUS_APP_SETUP_H_

#include <ezbus.h>

typedef struct _ezbus_app_state_t
{
    ezbus_port_t        port;
    ezbus_t             ezbus;
    ezbus_mac_t*        mac;
} ezbus_app_state_t;


extern bool ezbus_app_setup( ezbus_app_state_t* ezbus_app_state, uint32_t speed );

#endif

