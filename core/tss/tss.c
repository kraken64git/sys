#include "tss/tss.h"

extern uint32_t getEip();

Tss tss;

static void setTssEntry(int index, uint16_t ss0, uint32_t esp0)
{
    uint32_t eip = getEip();
    uint32_t base = (uint32_t) &tss;
    uint32_t limit = base + sizeof(tss);

    setEntryGdt(index, base, limit, 0xE9, 0x00);
    memset(&tss, 0x0, sizeof(Tss));

    tss.ss0 = ss0;
    tss.esp0 = esp0;
    tss.eip = eip;
    tss.cs = 0x0b;
    tss.ss = 0x13;
    tss.ds = 0x13;
    tss.es = 0x13;
    tss.fs = 0x13;
    tss.gs = 0x13;
    tss.iomapBase = sizeof(Tss);
}

void setStackTss(uint32_t esp0) { tss.esp0 = esp0; }

void InitTss()
{
    setTssEntry(5, 0x10, 0x0100000);
    loadTss();
}
