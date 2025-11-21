#ifndef UTILS_MEMORY_H
#define UTILS_MEMORY_H

#include "stdint.h"

void* memset(void* dest, uint8_t value, uint32_t size);
void* memcpy(void* dest, const void* src, uint32_t size);

#endif
