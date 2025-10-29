#ifndef CONSOLE_H
#define CONSOLE_H

#include "stdint.h"

#define VIDMEM_ADRESS 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

void write(const char* str);
void putChar(char ch);
void InitConsole();

#endif
