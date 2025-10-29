#include "gdt.h"

GDTEntry_t gdt[NO_GDT_DESCRIPTORS];
GDTPtr_t gdtPtr;

void setEntryGDT(int index, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    GDTEntry_t *this = &gdt[index];

    this->segmentLimit = (limit & 0xFFFF);
    this->baseLow = (base & 0xFFFF);
    this->baseMiddle = (base >> 16) & 0xFF;
    this->access = access;

    this->granularity = (limit >> 16) & 0x0F;
    this->granularity |= gran & 0xF0;

    this->baseHigh = (base >> 24) & 0xFF;
}

void InitGDT()
{
    gdtPtr.limit = sizeof(gdt) - 1;
    gdtPtr.base = (uint32_t) gdt;

    setEntryGDT(0, 0, 0, 0, 0);
    setEntryGDT(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    setEntryGDT(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    setEntryGDT(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    setEntryGDT(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    loadGDT((uint32_t) &gdtPtr);
}
