#include "kernel.h"

void MainKernel(void)
{
    InitGDT();
    InitConsole();
    write("GDT Initialized Successfully.");
    write("Console Initialized Successfully.");

    while(1);
}
