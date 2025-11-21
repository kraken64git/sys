#include "kernel.h"

void MainKernel()
{
    char buffer[255];
    const char* shell = "shell@os> ";

    InitGdt();
    InitIdt();
    InitTss();

    InitTimer();

    InitConsole();
    InitKeyboard();

    writeln("Starting terminal...");

    const char* str = "Hi!\n";
    while (*str) {
        sleep(1);
        putChar(*str++);
    }
    
    while(1) {
        write(shell);
        memset(buffer, 0, sizeof(buffer));
        getstrBound(buffer, strlen(shell));
        if (strlen(buffer) == 0) {
            continue;
        } if (strcmp(buffer, "help") == 0) {
            writeln("Tiny OS Terminal");
        } else {
            writeln("invalid command");
        }
    }
}
