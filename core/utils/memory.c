#include "utils/memory.h"

void* memset(void* dest, uint8_t value, uint32_t size) {
    uint8_t* ptr = (uint8_t*) dest;
    for (; size != 0; size--) *ptr++ = value;
    return dest;
}

void *memcpy(void *dest, const void* src, uint32_t size) {
    uint8_t* ret = dest;
    uint8_t *p = dest;
    const uint8_t *q = src;
    while (size--)
        *p++ = *q++;
    return ret;
}
