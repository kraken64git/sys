section .text
extern isrExceptionHandler

exceptionHandler:
    pusha
    mov ax, ds
    push eax
    
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isrExceptionHandler

    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa
    add esp, 0x8

    sti
    iret

%macro ERR_CODE 1
  global exception_%1
  exception_%1:
    cli
    push byte 0
    push %1
    jmp exceptionHandler
%endmacro

%macro NO_ERR_CODE 1
  global exception_%1
  exception_%1:
    cli
    push %1
    jmp exceptionHandler
%endmacro

ERR_CODE 0
ERR_CODE 1
ERR_CODE 2
ERR_CODE 3
ERR_CODE 4
ERR_CODE 5
ERR_CODE 6
ERR_CODE 7
ERR_CODE 9
ERR_CODE 15
ERR_CODE 16
ERR_CODE 17
ERR_CODE 18
ERR_CODE 19
ERR_CODE 20
ERR_CODE 21
ERR_CODE 22
ERR_CODE 23
ERR_CODE 24
ERR_CODE 25
ERR_CODE 26
ERR_CODE 27
ERR_CODE 28
ERR_CODE 29
ERR_CODE 30
ERR_CODE 31
ERR_CODE 128

NO_ERR_CODE 8
NO_ERR_CODE 10
NO_ERR_CODE 11
NO_ERR_CODE 12
NO_ERR_CODE 13
NO_ERR_CODE 14
