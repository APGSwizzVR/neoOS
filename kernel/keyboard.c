#include <stdint.h>
#include "keyboard.h"
static inline uint8_t inb(uint16_t p){uint8_t v;__asm__ volatile("inb %1,%0":"=a"(v):"Nd"(p));return v;}
static inline void outb(uint16_t p,uint8_t v){__asm__ volatile("outb %0,%1"::"a"(v),"Nd"(p));}
void keyboard_init(void){}
void keyboard_handler(void){if(inb(0x64)&1)(void)inb(0x60);outb(0x20,0x20);}
