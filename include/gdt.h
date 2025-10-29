#ifndef GDT_H
#define GDT_H

#include "stdint.h"

#define NO_GDT_DESCRIPTORS 8

typedef struct {
    uint16_t segmentLimit;
    uint16_t baseLow;
    uint8_t  baseMiddle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  baseHigh;
} __attribute__((packed)) GDTEntry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) GDTPtr_t;

extern void loadGDT(uint32_t ptr);

void setEntryGDT(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void InitGDT();

#endif
