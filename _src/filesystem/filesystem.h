#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include <board.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef void (*filesystem_callback_t)(void); 

void filesystem_setup(filesystem_callback_t callback);
bool filesystem_is_media(void);
bool filesystem_is_mounted(void);
void filesystem_service(void);

#ifdef __cplusplus
}
#endif

#endif
