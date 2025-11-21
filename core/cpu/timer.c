#include "cpu/timer.h"

uint32_t ticks = 0;
uint16_t frequencyHz = 0;
TFManager_t manager;

void setTimerFrequency(uint16_t freq)
{
    frequencyHz = freq;
    uint16_t divisor = TIMER_INPUT_CLOCK_FREQUENCY / freq;
    outportb(TIMER_COMMAND_PORT, 0b00110110);
    outportb(TIMER_CHANNEL_0_DATA_PORT, divisor & 0xFF);
    outportb(TIMER_CHANNEL_0_DATA_PORT, (divisor >> 8) & 0xFF);
}

void timerHandler(REGISTERS_t* regs)
{
    uint32_t i;
    TFArgs_t *args = NULL;
    ticks++;

    for (i = 0; i < MAXIMUM_TIMER_FUNCTIONS; i++) {
        args = &manager.args[i];
        if (args->timeout == 0)
            continue;
        if ((ticks % args->timeout) == 0) {
            manager.funcs[i](args);
        }
    }
}

void TFRegister(TimerFunc_t func, TFArgs_t *args)
{
    uint32_t index = 0;
    if (func == NULL || args == NULL) {
        writeln("ERROR: failed to register timer function");
        return;
    }
    index = (++manager.index) % MAXIMUM_TIMER_FUNCTIONS;
    manager.index = index;
    manager.funcs[index] = func;
    memcpy(&manager.args[index], args, sizeof(TFArgs_t));
}

void sleep(int sec)
{
    uint32_t end = ticks + sec * frequencyHz;
    while (ticks < end);
}

void InitTimer()
{
    setTimerFrequency(100);
    isrRegisterInterruptHandler(IRQ_BASE, timerHandler);
}
