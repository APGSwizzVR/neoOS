BITS 32
section .text
global keyboard_stub
global mouse_stub
extern keyboard_handler
extern mouse_handler

keyboard_stub:
    pusha
    call keyboard_handler
    popa
    iretd

mouse_stub:
    pusha
    call mouse_handler
    popa
    iretd
