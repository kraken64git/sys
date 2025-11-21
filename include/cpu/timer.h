#ifndef CPU_TIMER_H
#define CPU_TIMER_H

#include "stdint.h"
#include "cpu/isr.h"
#include "utils/memory.h"

#define TIMER_INPUT_CLOCK_FREQUENCY 1193180
#define TIMER_CHANNEL_0_DATA_PORT 0x40
#define TIMER_CHANNEL_1_DATA_PORT 0x41
#define TIMER_CHANNEL_2_DATA_PORT 0x42
#define TIMER_COMMAND_PORT 0x43

typedef struct {
    uint32_t timeout;
    void *user;
} TFArgs_t;

typedef void (*TimerFunc_t)(TFArgs_t *);

#define MAXIMUM_TIMER_FUNCTIONS 32

typedef struct {
    uint32_t index;
    TimerFunc_t funcs[MAXIMUM_TIMER_FUNCTIONS];
    TFArgs_t args[MAXIMUM_TIMER_FUNCTIONS];
} TFManager_t;

void InitTimer();
void sleep(int sec);
void TFRegister(TimerFunc_t func, TFArgs_t *args);

#endif
