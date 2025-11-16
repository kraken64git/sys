#ifndef CPU_IDT_H
#define CPU_IDT_H

#include "stdint.h"
#include "cpu/isr.h"
#include "cpu/8259pic.h"

#define NO_IDT_DESCRIPTORS 256

typedef struct {
    uint16_t baseLow;
    uint16_t selector;
    uint8_t zero;
    uint8_t type;
    uint16_t baseHigh;
} __attribute__((packed)) IdtEntry_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) IdtPtr_t;

extern void loadIdt(uint32_t ptr);

void setEntryIdt(int index, uint32_t base, uint16_t sel, uint8_t flags);
void InitIdt();

#endif
