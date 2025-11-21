#ifndef DRIVERS_CONSOLE_H
#define DRIVERS_CONSOLE_H

#include "stdint.h"
#include "kernel.h"

#define VIDMEM_ADRESS 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void write(const char* str);
void writeln(const char* str);
void putChar(char ch);
void clearScr();
void getstrBound(char *buffer, uint8_t bound);
void InitConsole();

#endif
