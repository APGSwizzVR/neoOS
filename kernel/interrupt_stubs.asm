BITS 32
section .text
global keyboard_stub
extern keyboard_handler
keyboard_stub:
    pusha
    call keyboard_handler
    popa
    iretd
