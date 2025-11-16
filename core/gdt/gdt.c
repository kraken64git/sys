#include "gdt/gdt.h"

GdtEntry_t gdt[NO_GDT_DESCRIPTORS];
GdtPtr_t gdtPtr;

void setEntryGdt(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    GdtEntry_t *this = &gdt[index];

    this->segmentLimit = (limit & 0xFFFF);
    this->baseLow = (base & 0xFFFF);
    this->baseMiddle = (base >> 16) & 0xFF;
    this->access = access;

    this->granularity = (limit >> 16) & 0x0F;
    this->granularity |= gran & 0xF0;

    this->baseHigh = (base >> 24) & 0xFF;
}

void InitGdt()
{
    gdtPtr.limit = sizeof(gdt) - 1;
    gdtPtr.base = (uint32_t) gdt;

    setEntryGdt(0, 0, 0, 0, 0);
    setEntryGdt(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    setEntryGdt(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    setEntryGdt(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    setEntryGdt(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    loadGdt((uint32_t) &gdtPtr);
}
