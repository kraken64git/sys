#include "cpu/idt.h"

IdtEntry_t idt[NO_IDT_DESCRIPTORS];
IdtPtr_t idtPtr;

void setEntryIdt(int index, uint32_t base, uint16_t sel, uint8_t flags)
{
    IdtEntry_t *this = &idt[index];

    this->baseLow = base & 0xFFFF;
    this->selector = sel;
    this->zero = 0;
    this->type = flags | 0x60;
    this->baseHigh = (base >> 16) & 0xFFFF;
}

void InitIdt()
{
    idtPtr.base = (uint32_t) idt;
    idtPtr.limit = sizeof(idt) - 1;
    Init_8259pic();

    setEntryIdt(0, (uint32_t) exception_0, 0x08, 0x8E);
    setEntryIdt(1, (uint32_t) exception_1, 0x08, 0x8E);
    setEntryIdt(2, (uint32_t) exception_2, 0x08, 0x8E);
    setEntryIdt(3, (uint32_t) exception_3, 0x08, 0x8E);
    setEntryIdt(4, (uint32_t) exception_4, 0x08, 0x8E);
    setEntryIdt(5, (uint32_t) exception_5, 0x08, 0x8E);
    setEntryIdt(6, (uint32_t) exception_6, 0x08, 0x8E);
    setEntryIdt(7, (uint32_t) exception_7, 0x08, 0x8E);
    setEntryIdt(8, (uint32_t) exception_8, 0x08, 0x8E);
    setEntryIdt(9, (uint32_t) exception_9, 0x08, 0x8E);
    setEntryIdt(10, (uint32_t) exception_10, 0x08, 0x8E);
    setEntryIdt(11, (uint32_t) exception_11, 0x08, 0x8E);
    setEntryIdt(12, (uint32_t) exception_12, 0x08, 0x8E);
    setEntryIdt(13, (uint32_t) exception_13, 0x08, 0x8E);
    setEntryIdt(14, (uint32_t) exception_14, 0x08, 0x8E);
    setEntryIdt(15, (uint32_t) exception_15, 0x08, 0x8E);
    setEntryIdt(16, (uint32_t) exception_16, 0x08, 0x8E);
    setEntryIdt(17, (uint32_t) exception_17, 0x08, 0x8E);
    setEntryIdt(18, (uint32_t) exception_18, 0x08, 0x8E);
    setEntryIdt(19, (uint32_t) exception_19, 0x08, 0x8E);
    setEntryIdt(20, (uint32_t) exception_20, 0x08, 0x8E);
    setEntryIdt(21, (uint32_t) exception_21, 0x08, 0x8E);
    setEntryIdt(22, (uint32_t) exception_22, 0x08, 0x8E);
    setEntryIdt(23, (uint32_t) exception_23, 0x08, 0x8E);
    setEntryIdt(24, (uint32_t) exception_24, 0x08, 0x8E);
    setEntryIdt(25, (uint32_t) exception_25, 0x08, 0x8E);
    setEntryIdt(26, (uint32_t) exception_26, 0x08, 0x8E);
    setEntryIdt(27, (uint32_t) exception_27, 0x08, 0x8E);
    setEntryIdt(28, (uint32_t) exception_28, 0x08, 0x8E);
    setEntryIdt(29, (uint32_t) exception_29, 0x08, 0x8E);
    setEntryIdt(30, (uint32_t) exception_30, 0x08, 0x8E);
    setEntryIdt(31, (uint32_t) exception_31, 0x08, 0x8E);
    setEntryIdt(32, (uint32_t) irq_0, 0x08, 0x8E);
    setEntryIdt(33, (uint32_t) irq_1, 0x08, 0x8E);
    setEntryIdt(34, (uint32_t) irq_2, 0x08, 0x8E);
    setEntryIdt(35, (uint32_t) irq_3, 0x08, 0x8E);
    setEntryIdt(36, (uint32_t) irq_4, 0x08, 0x8E);
    setEntryIdt(37, (uint32_t) irq_5, 0x08, 0x8E);
    setEntryIdt(38, (uint32_t) irq_6, 0x08, 0x8E);
    setEntryIdt(39, (uint32_t) irq_7, 0x08, 0x8E);
    setEntryIdt(40, (uint32_t) irq_8, 0x08, 0x8E);
    setEntryIdt(41, (uint32_t) irq_9, 0x08, 0x8E);
    setEntryIdt(42, (uint32_t) irq_10, 0x08, 0x8E);
    setEntryIdt(43, (uint32_t) irq_11, 0x08, 0x8E);
    setEntryIdt(44, (uint32_t) irq_12, 0x08, 0x8E);
    setEntryIdt(45, (uint32_t) irq_13, 0x08, 0x8E);
    setEntryIdt(46, (uint32_t) irq_14, 0x08, 0x8E);
    setEntryIdt(47, (uint32_t) irq_15, 0x08, 0x8E);
    setEntryIdt(128, (uint32_t) exception_128, 0x08, 0x8E);

    loadIdt((uint32_t) &idtPtr);
    asm volatile("sti");
}

