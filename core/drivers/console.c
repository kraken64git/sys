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
}

void writeln(const char* str)
{
    write(str);
    putChar('\n');
}

void clearScr()
{
    for (index = 0; index < SCREEN_WIDTH * SCREEN_HEIGHT;) {
        putChar(' ');
    }
    index = 0;
}

void getstrBound(char *buffer, uint8_t bound) {
    if (!buffer) return;
    while(1) {
        char ch = kbGetChar();
        if (ch == '\n') {
            putChar('\n');
            return ;
        } else {
            *buffer++ = ch;
            putChar(ch);
        }
    }
}

void InitConsole()
{
    clearScr();
}
