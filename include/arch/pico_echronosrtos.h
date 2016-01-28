/*********************************************************************
   PicoTCP. Copyright (c) 2012-2015 Altran Intelligent Systems. Some rights reserved.
   See LICENSE and COPYING for usage.
 *********************************************************************/

#ifndef PICO_SUPPORT_ECHRONOSRTOS
#define PICO_SUPPORT_ECHRONOSRTOS

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "rtos-rigel.h"

#define dbg printf

#define pico_zalloc(x) calloc(x, 1)
#define pico_free(x) free(x)

static inline uint32_t PICO_TIME(void)
{
    const uint32_t time = (rtos_timer_current_ticks / 10);
    /* printf("pico time: %d\n", time); */
    return time;
}

static inline uint32_t PICO_TIME_MS(void)
{
    const uint32_t time = (rtos_timer_current_ticks * 100);
    /* printf("pico time ms: %d\n", time); */
    return time;
}

static inline void PICO_IDLE(void)
{
    /* printf("pico idle\n"); */
    rtos_sleep(1);
}

#endif  /* PICO_SUPPORT_ECHRONOSRTOS */
