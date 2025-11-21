#ifndef KERNEL_H
#define KERNEL_H

#include "stdint.h"
#include "gdt/gdt.h"
#include "cpu/idt.h"
#include "cpu/timer.h"
#include "tss/tss.h"
#include "drivers/console.h"
#include "drivers/keyboard.h"

void MainKernel();

#endif
