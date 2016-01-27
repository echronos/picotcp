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

#define dbg printf

#define pico_zalloc(x) calloc(x, 1)
#define pico_free(x) free(x)

static inline uint32_t PICO_TIME(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
  #ifdef TIME_PRESCALE
    return (prescale_time < 0) ? (uint32_t)(t.tv_sec / 1000 << (-prescale_time)) : \
           (uint32_t)(t.tv_sec / 1000 >> prescale_time);
  #else
    return (uint32_t)t.tv_sec;
  #endif
}

static inline uint32_t PICO_TIME_MS(void)
{
    struct timeval t;
    gettimeofday(&t, NULL);
  #ifdef TIME_PRESCALER
    uint32_t tmp = ((t.tv_sec * 1000) + (t.tv_usec / 1000));
    return (prescale_time < 0) ? (uint32_t)(tmp / 1000 << (-prescale_time)) : \
           (uint32_t)(tmp / 1000 >> prescale_time);
  #else
    return (uint32_t)((t.tv_sec * 1000) + (t.tv_usec / 1000));
  #endif
}

static inline void PICO_IDLE(void)
{
    usleep(5000);
}

#endif  /* PICO_SUPPORT_ECHRONOSRTOS */
