#include "cpu/isr.h"

Isr handlers[NO_INTERRUPT_HANDLERS];

char *exceptionMsgs[32] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "BOUND Range Exceeded",
    "Invalid Opcode",
    "Device Not Available (No Math Coprocessor)",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection",
    "Page Fault",
    "Unknown Interrupt (intel reserved)",
    "x87 FPU Floating-Point Error (Math Fault)",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

void isrRegisterInterruptHandler(int num, Isr handler)
{
    writeln("IRQ registered");
    if (num < NO_INTERRUPT_HANDLERS)
        handlers[num] = handler;
}

void isrEndInterrupt(int num) { pic8259_eoi(num); }

void isrIrqHandler(REGISTERS_t *reg)
{
    if (handlers[reg->intNo] != NULL) {
        Isr handler = handlers[reg->intNo];
        handler(reg);
    }
    pic8259_eoi(reg->intNo);
}

void isrExceptionHandler(REGISTERS_t reg)
{
    if (reg.intNo < 32) {
        write(exceptionMsgs[reg.intNo]);
        asm volatile("\thlt");
    }
    if (handlers[reg.intNo] != NULL) {
        Isr handler = handlers[reg.intNo];
        handler(&reg);
    }
}
