bits 32

section .text
global start
extern MainKernel

start:
    cli

    mov esp, stack_top

    call MainKernel

    hlt
loop:
    jmp loop

section .bss
resb 512

stack_bottom:
    resb 16384
stack_top:
