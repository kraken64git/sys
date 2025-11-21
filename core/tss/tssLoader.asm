section .text
global loadTss
global getEip

loadTss:
    mov ax, 0x2B
    ltr ax
    ret

getEip:
    pop eax
    jmp eax
