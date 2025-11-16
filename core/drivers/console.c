#include "drivers/console.h"

volatile uint8_t* buffer = (uint8_t*) VIDMEM_ADRESS;
uint16_t index;

void putChar(char ch)
{
    switch (ch) {
        case '\n':
            index += SCREEN_WIDTH - (index % SCREEN_WIDTH);
            return;
    }
    
    uint16_t byteIndex = index++ * 2;
    buffer[byteIndex] = (uint8_t) ch;
    buffer[++byteIndex] = 0x07;
}

void write(const char* str)
{
    while (*str) { 
        putChar(*str++);
    }
    putChar('\n');
}

void clearScr()
{
    for (index = 0; index < SCREEN_WIDTH * SCREEN_HEIGHT;) {
        putChar(' ');
    }
    index = 0;
}

void InitConsole()
{
    clearScr();
}
