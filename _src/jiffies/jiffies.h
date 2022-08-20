/*****************************************************************************
*          ___  _     _ _                  _                 _               *
*         / _ \| |   (_) |                | |               | |              *
*        | (_) | |__  _| |_ __ _  ___  ___| | __  _ __   ___| |_             *
*         > _ <| '_ \| | __/ _` |/ _ \/ _ \ |/ / | '_ \ / _ \ __|            *
*        | (_) | |_) | | || (_| |  __/  __/   < _| | | |  __/ |_             *
*         \___/|_.__/|_|\__\__, |\___|\___|_|\_(_)_| |_|\___|\__|            *
*                           __/ |                                            *
*                          |___/                                             *
*                                                                            *
*     Copyright © 2021 8bitgeek.net                                          *
*     Author: Mike Sharkey <mike@8bitgeek.net>                               *
*                                                                            *
*****************************************************************************/
#ifndef __JIFFIES_H__
#define __JIFFIES_H__

#include <board.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define jiffies_t caribou_tick_t
/** @note jiffies() should always return milliseconds time */
#define jiffies()  (caribou_state.jiffies)
#define jiffies_timeout(start,timeout) ((jiffies()-(start)) > (timeout))

#ifdef __cplusplus
}
#endif

#endif
