#ifndef GDT_GDT_H
#define GDT_GDT_H

#include "stdint.h"

#define NO_GDT_DESCRIPTORS 8

typedef struct {
    uint16_t segmentLimit;
    uint16_t baseLow;
    uint8_t  baseMiddle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  baseHigh;
} __attribute__((packed)) GdtEntry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) GdtPtr_t;

extern void loadGdt(uint32_t ptr);

void setEntryGdt(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void InitGdt();

#endif
