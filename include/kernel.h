#ifndef KERNEL_H
#define KERNEL_H

#include "stdint.h"
#include "gdt/gdt.h"
#include "cpu/idt.h"
#include "drivers/console.h"

void MainKernel();

#endif
