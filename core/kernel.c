#include "kernel.h"

void MainKernel()
{
    InitGdt();
    InitIdt();
    InitConsole();
}
